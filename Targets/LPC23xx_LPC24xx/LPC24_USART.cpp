// Copyright Microsoft Corporation
// Copyright GHI Electronics, LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <algorithm>
#include "LPC24.h"

#define USART_EVENT_POST_DEBOUNCE_TICKS (10 * 10000) // 10ms between each events

void LPC24_Uart_EventCallback(const TinyCLR_Task_Manager* self, const TinyCLR_Api_Manager* apiManager, TinyCLR_Task_Reference task, void* arg);

static const uint32_t uartTxDefaultBuffersSize[] = LPC24_UART_DEFAULT_TX_BUFFER_SIZE;
static const uint32_t uartRxDefaultBuffersSize[] = LPC24_UART_DEFAULT_RX_BUFFER_SIZE;

struct UartState {
    int32_t controllerIndex;

    uint8_t                             *txBuffer;
    uint8_t                             *rxBuffer;
    size_t                              txBufferCount;
    size_t                              txBufferIn;
    size_t                              txBufferOut;
    size_t                              txBufferSize;

    size_t                              rxBufferCount;
    size_t                              rxBufferIn;
    size_t                              rxBufferOut;
    size_t                              rxBufferSize;

    bool                                handshaking;
    bool                                enable;

    TinyCLR_Uart_ErrorReceivedHandler   errorEventHandler;
    TinyCLR_Uart_DataReceivedHandler    dataReceivedEventHandler;
    TinyCLR_Uart_ClearToSendChangedHandler cleartosendEventHandler;

    TinyCLR_Task_Reference dataReceivedCallbackTaskReference;
    TinyCLR_Task_Reference errorCallbackTaskReference;

    const TinyCLR_Task_Manager* taskManager;

    const TinyCLR_Uart_Controller* controller;

    bool tableInitialized;

    uint16_t initializeCount;

    size_t lastEventRxBufferCount;
    uint64_t lastRxTime;

    uint8_t errorEvent;
};

#define SET_BITS(Var,Shift,Mask,fieldsMask) {Var = setFieldValue(Var,Shift,Mask,fieldsMask);}

uint32_t setFieldValue(volatile uint32_t oldVal, uint32_t shift, uint32_t mask, uint32_t val) {
    volatile uint32_t temp = oldVal;

    temp &= ~mask;
    temp |= val << shift;
    return temp;
}

static UartState uartStates[TOTAL_UART_CONTROLLERS];
static TinyCLR_Uart_Controller uartControllers[TOTAL_UART_CONTROLLERS];
static TinyCLR_Api_Info uartApi[TOTAL_UART_CONTROLLERS];

const char* uartApiNames[] = {
#if TOTAL_UART_CONTROLLERS > 0
"GHIElectronics.TinyCLR.NativeApis.LPC24.UartController\\0",
#if TOTAL_UART_CONTROLLERS > 1
"GHIElectronics.TinyCLR.NativeApis.LPC24.UartController\\1",
#if TOTAL_UART_CONTROLLERS > 2
"GHIElectronics.TinyCLR.NativeApis.LPC24.UartController\\2",
#if TOTAL_UART_CONTROLLERS > 3
"GHIElectronics.TinyCLR.NativeApis.LPC24.UartController\\3",
#if TOTAL_UART_CONTROLLERS > 4
"GHIElectronics.TinyCLR.NativeApis.LPC24.UartController\\4",
#endif
#endif
#endif
#endif
#endif
};

void LPC24_Uart_EnsureTableInitialized() {
    for (int32_t i = 0; i < TOTAL_UART_CONTROLLERS; i++) {
        if (uartStates[i].tableInitialized)
            continue;

        uartControllers[i].ApiInfo = &uartApi[i];
        uartControllers[i].Acquire = &LPC24_Uart_Acquire;
        uartControllers[i].Release = &LPC24_Uart_Release;
        uartControllers[i].Enable = &LPC24_Uart_Enable;
        uartControllers[i].Disable = &LPC24_Uart_Disable;
        uartControllers[i].SetActiveSettings = &LPC24_Uart_SetActiveSettings;
        uartControllers[i].Flush = &LPC24_Uart_Flush;
        uartControllers[i].Read = &LPC24_Uart_Read;
        uartControllers[i].Write = &LPC24_Uart_Write;
        uartControllers[i].SetErrorReceivedHandler = &LPC24_Uart_SetErrorReceivedHandler;
        uartControllers[i].SetDataReceivedHandler = &LPC24_Uart_SetDataReceivedHandler;
        uartControllers[i].GetClearToSendState = &LPC24_Uart_GetClearToSendState;
        uartControllers[i].SetClearToSendChangedHandler = &LPC24_Uart_SetClearToSendChangedHandler;
        uartControllers[i].GetIsRequestToSendEnabled = &LPC24_Uart_GetIsRequestToSendEnabled;
        uartControllers[i].SetIsRequestToSendEnabled = &LPC24_Uart_SetIsRequestToSendEnabled;
        uartControllers[i].GetReadBufferSize = &LPC24_Uart_GetReadBufferSize;
        uartControllers[i].SetReadBufferSize = &LPC24_Uart_SetReadBufferSize;
        uartControllers[i].GetWriteBufferSize = &LPC24_Uart_GetWriteBufferSize;
        uartControllers[i].SetWriteBufferSize = &LPC24_Uart_SetWriteBufferSize;
        uartControllers[i].GetBytesToRead = &LPC24_Uart_GetBytesToRead;
        uartControllers[i].GetBytesToWrite = &LPC24_Uart_GetBytesToWrite;
        uartControllers[i].ClearReadBuffer = &LPC24_Uart_ClearReadBuffer;
        uartControllers[i].ClearWriteBuffer = &LPC24_Uart_ClearWriteBuffer;

        uartApi[i].Author = "GHI Electronics, LLC";
        uartApi[i].Name = uartApiNames[i];
        uartApi[i].Type = TinyCLR_Api_Type::UartController;
        uartApi[i].Version = 0;
        uartApi[i].Implementation = &uartControllers[i];
        uartApi[i].State = &uartStates[i];

        uartStates[i].controllerIndex = i;
        uartStates[i].initializeCount = 0;
        uartStates[i].txBuffer = nullptr;
        uartStates[i].txBuffer = nullptr;

        uartStates[i].tableInitialized = true;
    }
}

const TinyCLR_Api_Info* LPC24_Uart_GetRequiredApi() {
    LPC24_Uart_EnsureTableInitialized();

    return &uartApi[UART_DEBUGGER_INDEX];
}

void LPC24_Uart_AddApi(const TinyCLR_Api_Manager* apiManager) {
    LPC24_Uart_EnsureTableInitialized();

    for (int32_t i = 0; i < TOTAL_UART_CONTROLLERS; i++) {
        apiManager->Add(apiManager, &uartApi[i]);
    }
}

size_t LPC24_Uart_GetReadBufferSize(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    return state->rxBufferSize;
}

TinyCLR_Result LPC24_Uart_SetReadBufferSize(const TinyCLR_Uart_Controller* self, size_t size) {
    auto memoryProvider = (const TinyCLR_Memory_Manager*)apiManager->FindDefault(apiManager, TinyCLR_Api_Type::MemoryManager);

    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    if (size <= 0)
        return TinyCLR_Result::ArgumentInvalid;

    if (state->rxBuffer) {
        memoryProvider->Free(memoryProvider, state->rxBuffer);
    }

    state->rxBufferSize = 0;

    state->rxBuffer = (uint8_t*)memoryProvider->Allocate(memoryProvider, size);

    if (state->rxBuffer == nullptr) {
        return TinyCLR_Result::OutOfMemory;
    }

    state->rxBufferSize = size;

    return TinyCLR_Result::Success;
}

size_t LPC24_Uart_GetWriteBufferSize(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    return state->txBufferSize;
}

TinyCLR_Result LPC24_Uart_SetWriteBufferSize(const TinyCLR_Uart_Controller* self, size_t size) {
    auto memoryProvider = (const TinyCLR_Memory_Manager*)apiManager->FindDefault(apiManager, TinyCLR_Api_Type::MemoryManager);

    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    if (size <= 0)
        return TinyCLR_Result::ArgumentInvalid;

    if (state->txBuffer) {
        memoryProvider->Free(memoryProvider, state->txBuffer);
    }

    state->txBufferSize = 0;

    state->txBuffer = (uint8_t*)memoryProvider->Allocate(memoryProvider, size);

    if (state->txBuffer == nullptr) {
        return TinyCLR_Result::OutOfMemory;
    }

    state->txBufferSize = size;

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_PinConfiguration(int controllerIndex, bool enable) {
    DISABLE_INTERRUPTS_SCOPED(irq);

    auto state = &uartStates[controllerIndex];

    int32_t txPin = LPC24_Uart_GetTxPin(controllerIndex);
    int32_t rxPin = LPC24_Uart_GetRxPin(controllerIndex);
    int32_t ctsPin = LPC24_Uart_GetCtsPin(controllerIndex);
    int32_t rtsPin = LPC24_Uart_GetRtsPin(controllerIndex);

    LPC24_Gpio_PinFunction txPinMode = LPC24_Uart_GetTxAlternateFunction(controllerIndex);
    LPC24_Gpio_PinFunction rxPinMode = LPC24_Uart_GetRxAlternateFunction(controllerIndex);
    LPC24_Gpio_PinFunction ctsPinMode = LPC24_Uart_GetCtsAlternateFunction(controllerIndex);
    LPC24_Gpio_PinFunction rtsPinMode = LPC24_Uart_GetRtsAlternateFunction(controllerIndex);

    if (enable) {
        // Connect pin to UART
        LPC24_GpioInternal_ConfigurePin(txPin, LPC24_Gpio_Direction::Input, txPinMode, LPC24_Gpio_PinMode::Inactive);
        // Connect pin to UART
        LPC24_GpioInternal_ConfigurePin(rxPin, LPC24_Gpio_Direction::Input, rxPinMode, LPC24_Gpio_PinMode::Inactive);

        LPC24_Uart_TxBufferEmptyInterruptEnable(controllerIndex, true);

        LPC24_Uart_RxBufferFullInterruptEnable(controllerIndex, true);

        if (state->handshaking) {
            if (ctsPin == PIN_NONE || rtsPin == PIN_NONE)
                return TinyCLR_Result::NotSupported;

            if (!LPC24_GpioInternal_OpenPin(ctsPin)) {
                LPC24_Uart_PinConfiguration(controllerIndex, false);
                return TinyCLR_Result::SharingViolation;
            }

            if (!LPC24_GpioInternal_OpenPin(rtsPin)) {
                LPC24_Uart_PinConfiguration(controllerIndex, false);

                return TinyCLR_Result::SharingViolation;
            }

            LPC24_GpioInternal_ConfigurePin(ctsPin, LPC24_Gpio_Direction::Input, ctsPinMode, LPC24_Gpio_PinMode::Inactive);
            LPC24_GpioInternal_ConfigurePin(rtsPin, LPC24_Gpio_Direction::Input, rtsPinMode, LPC24_Gpio_PinMode::Inactive);
        }

    }
    else {

        LPC24_Uart_TxBufferEmptyInterruptEnable(controllerIndex, false);
        // TODO Add config for uart pin protected state
        LPC24_GpioInternal_ClosePin(txPin);

        LPC24_Uart_RxBufferFullInterruptEnable(controllerIndex, false);
        // TODO Add config for uart pin protected state
        LPC24_GpioInternal_ClosePin(rxPin);

        if (state->handshaking) {
            LPC24_GpioInternal_ClosePin(ctsPin);
            LPC24_GpioInternal_ClosePin(rtsPin);
        }
    }

    return TinyCLR_Result::Success;
}

static inline void LPC24_Uart_ReceiveData(int controllerIndex, uint32_t LSR_Value, uint32_t IIR_Value) {
    DISABLE_INTERRUPTS_SCOPED(irq);

    LPC24XX_USART& USARTC = LPC24XX::UART(controllerIndex);

    auto state = &uartStates[controllerIndex];
    bool error = (LSR_Value & (LPC24XX_USART::UART_LSR_PEI | LPC24XX_USART::UART_LSR_OEI | LPC24XX_USART::UART_LSR_FEI)) != 0;

    // Read data from Rx FIFO
    if ((USARTC.SEL2.IER.UART_IER & (LPC24XX_USART::UART_IER_RDAIE)) || error) {
        if ((LSR_Value & LPC24XX_USART::UART_LSR_RFDR) || (IIR_Value == LPC24XX_USART::UART_IIR_IID_Irpt_RDA) || (IIR_Value == LPC24XX_USART::UART_IIR_IID_Irpt_TOUT) || (error)) {
            do {
                // Still read latest data
                auto data = (uint8_t)USARTC.SEL1.RBR.UART_RBR;

                if ((LSR_Value & LPC24XX_USART::UART_LSR_RFDR) || (IIR_Value == LPC24XX_USART::UART_IIR_IID_Irpt_RDA) || (IIR_Value == LPC24XX_USART::UART_IIR_IID_Irpt_TOUT))
                {

                    state->rxBuffer[state->rxBufferIn++] = data;

                    if (state->rxBufferCount < state->rxBufferSize) {
                        state->rxBufferCount++;
                    }

                    if (state->rxBufferIn == state->rxBufferSize)
                        state->rxBufferIn = 0;

                    if (state->dataReceivedEventHandler != nullptr) {
                        auto now = LPC24_Time_GetSystemTime(nullptr);

                        state->lastEventRxBufferCount++;

                        if (now > (state->lastRxTime + USART_EVENT_POST_DEBOUNCE_TICKS)) {
                            state->dataReceivedEventHandler(state->controller, state->lastEventRxBufferCount, now);
                            state->lastEventRxBufferCount = 0;
                        }

                        state->lastRxTime = now;
                    }
                }

                if (state->rxBufferCount == state->rxBufferSize) {
                    state->errorEvent = 1 << (uint8_t)TinyCLR_Uart_Error::BufferFull;
                }
                else if (LSR_Value & 0x02) {
                    state->errorEvent = 1 << (uint8_t)TinyCLR_Uart_Error::Overrun;
                }
                else if ((LSR_Value & 0x08) || (LSR_Value & 0x80)) {
                    state->errorEvent = 1 << (uint8_t)TinyCLR_Uart_Error::Frame;
                }
                else if (LSR_Value & 0x04) {
                    state->errorEvent = 1 << (uint8_t)TinyCLR_Uart_Error::ReceiveParity;
                }

                // Update next loop
                LSR_Value = USARTC.UART_LSR;
                error = (LSR_Value & (LPC24XX_USART::UART_LSR_PEI | LPC24XX_USART::UART_LSR_OEI | LPC24XX_USART::UART_LSR_FEI));

            } while ((LSR_Value & LPC24XX_USART::UART_LSR_RFDR) || error);
        }
    }
}
void LPC24_Uart_TransmitData(int controllerIndex, uint32_t LSR_Value, uint32_t IIR_Value) {
    DISABLE_INTERRUPTS_SCOPED(irq);

    LPC24XX_USART& USARTC = LPC24XX::UART(controllerIndex);

    auto state = &uartStates[controllerIndex];

    // Send data
    if ((LSR_Value & LPC24XX_USART::UART_LSR_TE) || (IIR_Value == LPC24XX_USART::UART_IIR_IID_Irpt_THRE)) {
        // Check if CTS is high
        if (LPC24_Uart_CanSend(controllerIndex)) {
            if (state->txBufferCount > 0) {
                uint8_t txdata = state->txBuffer[state->txBufferOut++];

                state->txBufferCount--;

                if (state->txBufferOut == state->txBufferSize)
                    state->txBufferOut = 0;

                USARTC.SEL1.THR.UART_THR = txdata; // write TX data

            }
            else {
                LPC24_Uart_TxBufferEmptyInterruptEnable(controllerIndex, false); // Disable interrupt when no more data to send.
            }
        }
        else {
            // Temporary disable tx during cts is high to avoild device lockup
            LPC24_Uart_TxBufferEmptyInterruptEnable(controllerIndex, false);
        }
    }
}

void LPC24_Uart_InterruptHandler(void *param) {
    DISABLE_INTERRUPTS_SCOPED(irq);

    uint32_t controllerIndex = *reinterpret_cast<uint32_t*>(param);

    LPC24XX_USART& USARTC = LPC24XX::UART(controllerIndex);
    volatile uint32_t LSR_Value = USARTC.UART_LSR;                     // Store LSR value since it's Read-to-Clear
    volatile uint32_t IIR_Value = USARTC.SEL3.IIR.UART_IIR & LPC24XX_USART::UART_IIR_IID_mask;

    auto state = &uartStates[controllerIndex];

    LPC24_Uart_ReceiveData(controllerIndex, LSR_Value, IIR_Value);

    LPC24_Uart_TransmitData(controllerIndex, LSR_Value, IIR_Value);

    if (state->handshaking) {
        volatile uint32_t msr = USARTC.UART_MSR; // clear cts interrupt

        if (msr & 0x1) {  // detect cts changed bit
            bool ctsState = true;

            LPC24_Uart_GetClearToSendState(state->controller, ctsState);

            if (state->cleartosendEventHandler != nullptr)
                state->cleartosendEventHandler(state->controller, ctsState, LPC24_Time_GetSystemTime(nullptr));

            // If tx was disable to avoid locked up
            // Need Enable back if detected OK to send
            if (ctsState)
                LPC24_Uart_TxBufferEmptyInterruptEnable(controllerIndex, true);
        }
    }
}


TinyCLR_Result LPC24_Uart_Acquire(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    if (state->initializeCount == 0) {
        auto controllerIndex = state->controllerIndex;

        if (controllerIndex >= TOTAL_UART_CONTROLLERS)
            return TinyCLR_Result::ArgumentInvalid;

        DISABLE_INTERRUPTS_SCOPED(irq);

        int32_t txPin = LPC24_Uart_GetTxPin(controllerIndex);
        int32_t rxPin = LPC24_Uart_GetRxPin(controllerIndex);

        if (!LPC24_GpioInternal_OpenPin(txPin))
            return TinyCLR_Result::SharingViolation;

        if (!LPC24_GpioInternal_OpenPin(rxPin)) {
            LPC24_GpioInternal_ClosePin(txPin);

            return TinyCLR_Result::SharingViolation;
        }

        state->txBufferCount = 0;
        state->txBufferIn = 0;
        state->txBufferOut = 0;

        state->rxBufferCount = 0;
        state->rxBufferIn = 0;
        state->rxBufferOut = 0;

        state->controller = self;
        state->handshaking = false;
        state->enable = false;

        state->lastEventRxBufferCount = 0;
        state->errorEvent = 0;
        state->lastRxTime = 0;

        state->txBuffer = nullptr;
        state->rxBuffer = nullptr;
        state->errorEventHandler = nullptr;
        state->dataReceivedEventHandler = nullptr;
        state->cleartosendEventHandler = nullptr;

        if (LPC24_Uart_SetWriteBufferSize(self, uartTxDefaultBuffersSize[controllerIndex]) != TinyCLR_Result::Success)
            return TinyCLR_Result::OutOfMemory;

        if (LPC24_Uart_SetReadBufferSize(self, uartRxDefaultBuffersSize[controllerIndex]) != TinyCLR_Result::Success)
            return TinyCLR_Result::OutOfMemory;

        switch (controllerIndex) {
        case 0:
            LPC24XX::SYSCON().PCONP |= PCONP_PCUART0;
            break;

        case 1:
            LPC24XX::SYSCON().PCONP |= PCONP_PCUART1;
            break;

        case 2:
            LPC24XX::SYSCON().PCONP |= PCONP_PCUART2;
            break;

        case 3:
            LPC24XX::SYSCON().PCONP |= PCONP_PCUART3;
            break;
        }
    }

    state->initializeCount++;

    return TinyCLR_Result::Success;
}

void LPC24_Uart_SetClock(int32_t controllerIndex, int32_t pclkSel) {
    pclkSel &= 0x03;

    switch (controllerIndex) {
    case 0:

        LPC24XX::SYSCON().PCLKSEL0 &= ~(0x03 << 6);
        LPC24XX::SYSCON().PCLKSEL0 |= (pclkSel << 6);

        break;

    case 1:

        LPC24XX::SYSCON().PCLKSEL0 &= ~(0x03 << 8);
        LPC24XX::SYSCON().PCLKSEL0 |= (pclkSel << 8);

        break;

    case 2:
        LPC24XX::SYSCON().PCLKSEL1 &= ~(0x03 << 16);
        LPC24XX::SYSCON().PCLKSEL1 |= (pclkSel << 16);
        break;

    case 3:
        LPC24XX::SYSCON().PCLKSEL1 &= ~(0x03 << 18);
        LPC24XX::SYSCON().PCLKSEL1 |= (pclkSel << 18);
        break;

    }
}
TinyCLR_Result LPC24_Uart_SetActiveSettings(const TinyCLR_Uart_Controller* self, const TinyCLR_Uart_Settings* settings) {
    uint32_t baudRate = settings->BaudRate;
    uint32_t dataBits = settings->DataBits;
    TinyCLR_Uart_Parity parity = settings->Parity;
    TinyCLR_Uart_StopBitCount stopBits = settings->StopBits;
    TinyCLR_Uart_Handshake handshaking = settings->Handshaking;

    DISABLE_INTERRUPTS_SCOPED(irq);

    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    auto controllerIndex = state->controllerIndex;

    LPC24XX_USART& USARTC = LPC24XX::UART(controllerIndex);

    uint32_t divisor;
    bool   fRet = true;
    uint32_t uart_clock;

    if (baudRate >= 460800) {
        uart_clock = LPC24XX_USART::c_ClockRate;
        LPC24_Uart_SetClock(controllerIndex, 1);
    }
    else {
        uart_clock = LPC24XX_USART::c_ClockRate / 4;
        LPC24_Uart_SetClock(controllerIndex, 0);
    }

    divisor = ((uart_clock / (baudRate * 16)));

    while ((uart_clock / (divisor * 16)) > baudRate) {
        divisor++;
    }

    // CWS: Disable interrupts
    USARTC.UART_LCR = 0; // prepare to Init UART
    USARTC.SEL2.IER.UART_IER &= ~(LPC24XX_USART::UART_IER_INTR_ALL_SET); // Disable all UART interrupts

    /* CWS: Set baud rate to baudRate bps */
    USARTC.UART_LCR |= LPC24XX_USART::UART_LCR_DLAB; // prepare to access Divisor
    USARTC.SEL1.DLL.UART_DLL = divisor & 0xFF; //GET_LSB(divisor);
    USARTC.SEL2.DLM.UART_DLM = (divisor >> 8) & 0xFF; // GET_MSB(divisor);
    USARTC.UART_LCR &= ~LPC24XX_USART::UART_LCR_DLAB; // prepare to access RBR, THR, IER

    // CWS: Set port for 8 bit, 1 stop, no parity
    USARTC.UART_FDR = 0x10; // DIVADDVAL = 0, MULVAL = 1, DLM = 0;

    // DataBit range 5-8
    if (5 <= dataBits && dataBits <= 8) {
        SET_BITS(USARTC.UART_LCR,
            LPC24XX_USART::UART_LCR_WLS_shift,
            LPC24XX_USART::UART_LCR_WLS_mask,
            dataBits - 5);
    }
    else {   // not supported
     // set up 8 data bits incase return value is ignored

        return TinyCLR_Result::NotSupported;
    }

    switch (stopBits) {
    case TinyCLR_Uart_StopBitCount::Two:
        USARTC.UART_LCR |= LPC24XX_USART::UART_LCR_NSB_15_STOPBITS;

        if (dataBits == 5)
            return TinyCLR_Result::NotSupported;

        break;

    case TinyCLR_Uart_StopBitCount::One:
        USARTC.UART_LCR |= LPC24XX_USART::UART_LCR_NSB_1_STOPBITS;

        break;

    case TinyCLR_Uart_StopBitCount::OnePointFive:
        USARTC.UART_LCR |= LPC24XX_USART::UART_LCR_NSB_15_STOPBITS;

        if (dataBits != 5)
            return TinyCLR_Result::NotSupported;

        break;

    default:

        return TinyCLR_Result::NotSupported;
    }

    switch (parity) {

    case TinyCLR_Uart_Parity::Space:
        USARTC.UART_LCR |= LPC24XX_USART::UART_LCR_SPE;

    case TinyCLR_Uart_Parity::Even:
        USARTC.UART_LCR |= (LPC24XX_USART::UART_LCR_EPE | LPC24XX_USART::UART_LCR_PBE);
        break;

    case TinyCLR_Uart_Parity::Mark:
        USARTC.UART_LCR |= LPC24XX_USART::UART_LCR_SPE;

    case  TinyCLR_Uart_Parity::Odd:
        USARTC.UART_LCR |= LPC24XX_USART::UART_LCR_PBE;
        break;

    case TinyCLR_Uart_Parity::None:
        USARTC.UART_LCR &= ~LPC24XX_USART::UART_LCR_PBE;
        break;

    default:

        return TinyCLR_Result::NotSupported;
    }

    if (handshaking != TinyCLR_Uart_Handshake::None && controllerIndex != 1) // Only port 2 support handshaking
        return TinyCLR_Result::NotSupported;


    switch (handshaking) {
    case TinyCLR_Uart_Handshake::RequestToSend:
        USARTC.UART_MCR |= (1 << 6) | (1 << 7);
        USARTC.SEL2.IER.UART_IER |= (1 << 7) | (1 << 3);    // Enable Interrupt CTS
        state->handshaking = true;
        break;

    case TinyCLR_Uart_Handshake::XOnXOff:
    case TinyCLR_Uart_Handshake::RequestToSendXOnXOff:
        return TinyCLR_Result::NotSupported;
    }

    // CWS: Set the RX FIFO trigger level (to 8 bytes), reset RX, TX FIFO
    USARTC.SEL3.FCR.UART_FCR = (LPC24XX_USART::UART_FCR_RFITL_08 << LPC24XX_USART::UART_FCR_RFITL_shift) |
        LPC24XX_USART::UART_FCR_TFR |
        LPC24XX_USART::UART_FCR_RFR |
        LPC24XX_USART::UART_FCR_FME;

    LPC24_InterruptInternal_Activate(LPC24XX_USART::getIntNo(controllerIndex), (uint32_t*)&LPC24_Uart_InterruptHandler, (void*)&state->controllerIndex);

    LPC24_Uart_PinConfiguration(controllerIndex, true);


    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_Release(const TinyCLR_Uart_Controller* self) {
    DISABLE_INTERRUPTS_SCOPED(irq);

    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    if (state->initializeCount == 0) return TinyCLR_Result::InvalidOperation;

    state->initializeCount--;

    if (state->initializeCount == 0) {
        auto controllerIndex = state->controllerIndex;

        LPC24XX_USART& USARTC = LPC24XX::UART(controllerIndex);

        LPC24_InterruptInternal_Deactivate(LPC24XX_USART::getIntNo(controllerIndex));

        if (state->handshaking) {
            USARTC.UART_MCR &= ~((1 << 6) | (1 << 7));
            USARTC.SEL2.IER.UART_IER &= ~((1 << 7) | (1 << 3)); // Disable Interrupt CTS RTS
        }

        // CWS: Disable interrupts
        USARTC.UART_LCR = 0; // prepare to Init UART
        USARTC.SEL2.IER.UART_IER &= ~(LPC24XX_USART::UART_IER_INTR_ALL_SET);         // Disable all UART interrupt

        LPC24_Uart_PinConfiguration(controllerIndex, false);

        state->txBufferCount = 0;
        state->txBufferIn = 0;
        state->txBufferOut = 0;

        state->rxBufferCount = 0;
        state->rxBufferIn = 0;
        state->rxBufferOut = 0;

        state->handshaking = false;

        switch (controllerIndex) {
        case 0:
            LPC24XX::SYSCON().PCONP &= ~PCONP_PCUART0;
            break;

        case 1:
            LPC24XX::SYSCON().PCONP &= ~PCONP_PCUART1;
            break;

        case 2:
            LPC24XX::SYSCON().PCONP &= ~PCONP_PCUART2;
            break;

        case 3:
            LPC24XX::SYSCON().PCONP &= ~PCONP_PCUART3;
            break;
        }

        // Release memory
        if (apiManager != nullptr) {
            auto memoryProvider = (const TinyCLR_Memory_Manager*)apiManager->FindDefault(apiManager, TinyCLR_Api_Type::MemoryManager);

            if (state->txBuffer != nullptr) {
                memoryProvider->Free(memoryProvider, state->txBuffer);

                state->txBuffer = nullptr;
            }

            if (state->rxBuffer != nullptr) {
                memoryProvider->Free(memoryProvider, state->rxBuffer);

                state->rxBuffer = nullptr;
            }
        }

        LPC24_Uart_SetErrorReceivedHandler(self, nullptr);
        LPC24_Uart_SetDataReceivedHandler(self, nullptr);
    }

    return TinyCLR_Result::Success;
}

void LPC24_Uart_TxBufferEmptyInterruptEnable(int controllerIndex, bool enable) {
    DISABLE_INTERRUPTS_SCOPED(irq);

    LPC24XX_USART& USARTC = LPC24XX::UART(controllerIndex);

    if (enable) {
        LPC24XX::VIC().ForceInterrupt(LPC24XX_USART::getIntNo(controllerIndex));// force interrupt as this chip has a bug????
        USARTC.SEL2.IER.UART_IER |= (LPC24XX_USART::UART_IER_THREIE);
    }
    else {
        USARTC.SEL2.IER.UART_IER &= ~(LPC24XX_USART::UART_IER_THREIE);
    }
}

void LPC24_Uart_RxBufferFullInterruptEnable(int controllerIndex, bool enable) {
    DISABLE_INTERRUPTS_SCOPED(irq);

    LPC24XX_USART& USARTC = LPC24XX::UART(controllerIndex);

    if (enable) {
        USARTC.SEL2.IER.UART_IER |= (LPC24XX_USART::UART_IER_RDAIE);
    }
    else {
        USARTC.SEL2.IER.UART_IER &= ~(LPC24XX_USART::UART_IER_RDAIE);
    }
}

bool LPC24_Uart_CanSend(int controllerIndex) {
    auto state = &uartStates[controllerIndex];
    bool value = true;

    LPC24_Uart_GetClearToSendState(state->controller, value);

    return value;
}

TinyCLR_Result LPC24_Uart_Flush(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    if (state->initializeCount && !LPC24_Interrupt_IsDisabled()) {
        LPC24_Uart_TxBufferEmptyInterruptEnable(state->controllerIndex, true);

        while (state->txBufferCount > 0) {
            LPC24_Time_Delay(nullptr, 1);
        }
    }

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_Read(const TinyCLR_Uart_Controller* self, uint8_t* buffer, size_t& length) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    if (state->initializeCount == 0) {
        length = 0; // make sure length is updated

        return TinyCLR_Result::NotAvailable;
    }

    length = std::min(self->GetBytesToRead(self), length);

    size_t i = 0;

    while (i < length) {
        buffer[i++] = state->rxBuffer[state->rxBufferOut++];

        if (state->rxBufferOut == state->rxBufferSize)
            state->rxBufferOut = 0;
    }

    {
        DISABLE_INTERRUPTS_SCOPED(irq);

        state->rxBufferCount -= length;
    }

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_Write(const TinyCLR_Uart_Controller* self, const uint8_t* buffer, size_t& length) {

    int32_t i = 0;

    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    auto controllerIndex = state->controllerIndex;

    if (state->initializeCount == 0) {
        length = 0; // make sure length is updated

        return TinyCLR_Result::NotAvailable;
    }

    length = std::min(state->txBufferSize - state->txBufferCount, length);

    if (length == 0) return TinyCLR_Result::Success; // Return Success with nothing written;

    while (i < length) {

        state->txBuffer[state->txBufferIn++] = buffer[i++];

        if (state->txBufferIn == state->txBufferSize)
            state->txBufferIn = 0;
    }

    {
        DISABLE_INTERRUPTS_SCOPED(irq);

        state->txBufferCount += length;
    }

    if (length > 0) {
        LPC24_Uart_TxBufferEmptyInterruptEnable(controllerIndex, true); // Enable Tx to start transfer
    }

    return TinyCLR_Result::Success;
}

TinyCLR_Uart_Error LPC24_Uart_GetError(uint32_t error) {
    switch (error) {
    case 1:
        return TinyCLR_Uart_Error::Frame;

    case 2:
        return TinyCLR_Uart_Error::Overrun;

    case 8:
        return TinyCLR_Uart_Error::ReceiveParity;

    default:
        return TinyCLR_Uart_Error::BufferFull;
    }
}

void LPC24_Uart_EventCallback(const TinyCLR_Task_Manager* self, const TinyCLR_Api_Manager* apiManager, TinyCLR_Task_Reference task, void* arg) {
    auto state = reinterpret_cast<UartState*>(arg);

    if (task == state->dataReceivedCallbackTaskReference) {
        size_t latestCount = 0;

        {
            DISABLE_INTERRUPTS_SCOPED(irq);
            latestCount = state->lastEventRxBufferCount;
            state->lastEventRxBufferCount = 0;
        }

        if (latestCount > 0 && state->dataReceivedEventHandler != nullptr) {
            state->dataReceivedEventHandler(state->controller, latestCount, LPC24_Time_GetSystemTime(nullptr));
        }

        state->taskManager->Enqueue(state->taskManager, task, LPC24_Time_GetProcessorTicksForTime(nullptr, USART_EVENT_POST_DEBOUNCE_TICKS));
    }
    else if (task == state->errorCallbackTaskReference) {
        uint8_t latestError = 0;

        {
            DISABLE_INTERRUPTS_SCOPED(irq);
            latestError = state->errorEvent;
            state->errorEvent = 0;
        }

        if ((latestError != 0) && state->errorEventHandler != nullptr) {
            state->errorEventHandler(state->controller, LPC24_Uart_GetError(latestError), LPC24_Time_GetSystemTime(nullptr));
        }
        state->taskManager->Enqueue(state->taskManager, task, LPC24_Time_GetProcessorTicksForTime(nullptr, USART_EVENT_POST_DEBOUNCE_TICKS));
    }
}

TinyCLR_Result LPC24_Uart_SetErrorReceivedHandler(const TinyCLR_Uart_Controller* self, TinyCLR_Uart_ErrorReceivedHandler handler) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    if (handler != nullptr) {
        state->errorEventHandler = handler;
        state->taskManager = (const TinyCLR_Task_Manager*)apiManager->FindDefault(apiManager, TinyCLR_Api_Type::TaskManager);
        state->taskManager->Create(state->taskManager, LPC24_Uart_EventCallback, (void*)state, false, state->errorCallbackTaskReference);
        state->taskManager->Enqueue(state->taskManager, state->errorCallbackTaskReference, LPC24_Time_GetProcessorTicksForTime(nullptr, USART_EVENT_POST_DEBOUNCE_TICKS));
    }
    else {
        if (state->errorEventHandler != nullptr && state->taskManager != nullptr && state->errorCallbackTaskReference) {
            state->taskManager->Free(state->taskManager, state->errorCallbackTaskReference);

            state->errorEventHandler = nullptr;
            state->errorCallbackTaskReference = nullptr;
        }

    }

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_SetDataReceivedHandler(const TinyCLR_Uart_Controller* self, TinyCLR_Uart_DataReceivedHandler handler) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    if (handler != nullptr) {
        state->dataReceivedEventHandler = handler;
        state->taskManager = (const TinyCLR_Task_Manager*)apiManager->FindDefault(apiManager, TinyCLR_Api_Type::TaskManager);
        state->taskManager->Create(state->taskManager, LPC24_Uart_EventCallback, (void*)state, false, state->dataReceivedCallbackTaskReference);
        state->taskManager->Enqueue(state->taskManager, state->dataReceivedCallbackTaskReference, LPC24_Time_GetProcessorTicksForTime(nullptr, USART_EVENT_POST_DEBOUNCE_TICKS));
    }

    else {
        if (state->dataReceivedEventHandler != nullptr && state->taskManager != nullptr && state->dataReceivedCallbackTaskReference != nullptr) {
            state->taskManager->Free(state->taskManager, state->dataReceivedCallbackTaskReference);

            state->dataReceivedEventHandler = nullptr;
            state->dataReceivedCallbackTaskReference = nullptr;
        }

    }

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_GetClearToSendState(const TinyCLR_Uart_Controller* self, bool& value) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    value = true;

    if (state->handshaking) {
        auto controllerIndex = state->controllerIndex;
        auto ctsPin = LPC24_Uart_GetCtsPin(controllerIndex);

        // Reading the pin state to protect values from register for inteterupt which is higher priority (some bits are clear once read)
        TinyCLR_Gpio_PinValue pinState;
        LPC24_Gpio_Read(nullptr, ctsPin, pinState);

        value = (pinState == TinyCLR_Gpio_PinValue::High) ? false : true;
    }

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_SetClearToSendChangedHandler(const TinyCLR_Uart_Controller* self, TinyCLR_Uart_ClearToSendChangedHandler handler) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);
    state->cleartosendEventHandler = handler;

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_GetIsRequestToSendEnabled(const TinyCLR_Uart_Controller* self, bool& value) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    value = false;

    if (state->handshaking) {
        auto controllerIndex = state->controllerIndex;
        auto rtsPin = LPC24_Uart_GetRtsPin(controllerIndex);

        // Reading the pin state to protect values from register for inteterupt which is higher priority (some bits are clear once read)
        TinyCLR_Gpio_PinValue pinState;
        LPC24_Gpio_Read(nullptr, rtsPin, pinState);

        value = (pinState == TinyCLR_Gpio_PinValue::High) ? true : false;
    }

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_SetIsRequestToSendEnabled(const TinyCLR_Uart_Controller* self, bool value) {
    // Enable by hardware, no support by software.
    return TinyCLR_Result::NotSupported;
}

size_t LPC24_Uart_GetBytesToRead(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    return  state->rxBufferCount;
}

size_t LPC24_Uart_GetBytesToWrite(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    return state->txBufferCount;
}

TinyCLR_Result LPC24_Uart_ClearReadBuffer(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    state->rxBufferCount = state->rxBufferIn = state->rxBufferOut = state->lastEventRxBufferCount = 0;

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_ClearWriteBuffer(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);

    state->txBufferCount = state->txBufferIn = state->txBufferOut = 0;

    return TinyCLR_Result::Success;
}

void LPC24_Uart_Reset() {
    for (auto i = 0; i < TOTAL_UART_CONTROLLERS; i++) {
        LPC24_Uart_Release(&uartControllers[i]);

        uartStates[i].tableInitialized = false;
        uartStates[i].initializeCount = 0;
        uartStates[i].txBuffer = nullptr;
        uartStates[i].txBuffer = nullptr;
    }
}

TinyCLR_Result LPC24_Uart_Enable(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);
    state->enable = true;

    return TinyCLR_Result::Success;
}

TinyCLR_Result LPC24_Uart_Disable(const TinyCLR_Uart_Controller* self) {
    auto state = reinterpret_cast<UartState*>(self->ApiInfo->State);
    state->enable = false;

    return TinyCLR_Result::Success;
}