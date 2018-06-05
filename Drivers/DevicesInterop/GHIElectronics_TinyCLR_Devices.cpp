#include "GHIElectronics_TinyCLR_Devices.h"
#include "GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Interop.h"

static const TinyCLR_Interop_MethodHandler methods[] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::get_ChannelMode___GHIElectronicsTinyCLRDevicesAdcProviderProviderAdcChannelMode,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::set_ChannelMode___VOID__GHIElectronicsTinyCLRDevicesAdcProviderProviderAdcChannelMode,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::get_ChannelCount___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::get_MaxValue___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::get_MinValue___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::get_ResolutionInBits___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::IsChannelModeSupported___BOOLEAN__GHIElectronicsTinyCLRDevicesAdcProviderProviderAdcChannelMode,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::AcquireChannel___VOID__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::ReleaseChannel___VOID__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::ReadValue___I4__I4,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::AcquireNative___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_DefaultAdcControllerProvider::ReleaseNative___VOID,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::Reset___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::ReadMessages___I4__SZARRAY_GHIElectronicsTinyCLRDevicesCanCanMessage__I4__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::WriteMessages___I4__SZARRAY_GHIElectronicsTinyCLRDevicesCanCanMessage__I4__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::SetBitTiming___VOID__GHIElectronicsTinyCLRDevicesCanCanBitTiming,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::SetExplicitFilters___VOID__SZARRAY_U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::SetGroupFilters___VOID__SZARRAY_U4__SZARRAY_U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::ClearReadBuffer___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::ClearWriteBuffer___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::get_UnreadMessageCount___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::get_UnwrittenMessageCount___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::get_IsWritingAllowed___BOOLEAN,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::get_ReadErrorCount___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::get_WriteErrorCount___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::get_SourceClock___U4,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::NativeAcquire___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::NativeRelease___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::get_ReadBufferSize___U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::set_ReadBufferSize___VOID__U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::get_WriteBufferSize___U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Can_Provider_DefaultCanControllerProvider::set_WriteBufferSize___VOID__U4,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Dac_Provider_DefaultDacControllerProvider::get_ChannelCount___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Dac_Provider_DefaultDacControllerProvider::get_MaxValue___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Dac_Provider_DefaultDacControllerProvider::get_MinValue___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Dac_Provider_DefaultDacControllerProvider::get_ResolutionInBits___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Dac_Provider_DefaultDacControllerProvider::AcquireChannel___VOID__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Dac_Provider_DefaultDacControllerProvider::ReleaseChannel___VOID__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Dac_Provider_DefaultDacControllerProvider::WriteValue___VOID__I4__I4,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Dac_Provider_DefaultDacControllerProvider::AcquireNative___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Dac_Provider_DefaultDacControllerProvider::ReleaseNative___VOID,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Display_Provider_DefaultDisplayControllerProvider::get_Interface___GHIElectronicsTinyCLRDevicesDisplayDisplayInterface,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Display_Provider_DefaultDisplayControllerProvider::get_SupportedDataFormats___SZARRAY_GHIElectronicsTinyCLRDevicesDisplayDisplayDataFormat,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Display_Provider_DefaultDisplayControllerProvider::WriteString___VOID__STRING,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Display_Provider_DefaultDisplayControllerProvider::SetParallelConfiguration___BOOLEAN__U4__U4__GHIElectronicsTinyCLRDevicesDisplayDisplayDataFormat__BOOLEAN__BOOLEAN__BOOLEAN__U4__BOOLEAN__U4__U4__U4__BOOLEAN__U4__U4__U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Display_Provider_DefaultDisplayControllerProvider::SetSpiConfiguration___BOOLEAN__U4__U4__GHIElectronicsTinyCLRDevicesDisplayDisplayDataFormat__STRING,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioChangeReader::NativeRead___STATIC___I4__U4__BYREF_BOOLEAN__SZARRAY_U4__I4__I4__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioChangeReader::NativeRead___STATIC___I4__U4__BOOLEAN__SZARRAY_U4__I4__I4__I4,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioChangeWriter::NativeConstructor___BOOLEAN__BOOLEAN,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioChangeWriter::NativeDispose___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioChangeWriter::NativeIsActive___BOOLEAN,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioChangeWriter::NativeSet___VOID__BOOLEAN,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioChangeWriter::NativeSet___BOOLEAN__BOOLEAN__SZARRAY_U4__I4__I4__BOOLEAN,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioChangeWriter::NativeSet___VOID__BOOLEAN__SZARRAY_U4__I4__I4__U4__BOOLEAN__U4,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioPulseReaderWriter::NativeReadDrainTime___I8,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioPulseReaderWriter::NativeReadEcho___I8__BOOLEAN,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_GpioPulseReaderWriter::NativeFinalize___VOID,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioControllerProvider::get_PinCount___I4,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioControllerProvider::AcquireNative___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioControllerProvider::ReleaseNative___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioControllerProvider::AcquireNative___VOID__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioControllerProvider::ReleaseNative___VOID__I4,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioPinProvider::get_DebounceTimeout___mscorlibSystemTimeSpan,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioPinProvider::set_DebounceTimeout___VOID__mscorlibSystemTimeSpan,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioPinProvider::Read___GHIElectronicsTinyCLRDevicesGpioProviderProviderGpioPinValue,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioPinProvider::Write___VOID__GHIElectronicsTinyCLRDevicesGpioProviderProviderGpioPinValue,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Gpio_Provider_DefaultGpioPinProvider::SetDriveModeInternal___VOID__GHIElectronicsTinyCLRDevicesGpioProviderProviderGpioPinDriveMode,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_I2c_I2cNativeSoftwareDeviceProvider::NativeWriteRead___STATIC___BOOLEAN__I4__I4__U1__BOOLEAN__SZARRAY_U1__I4__I4__SZARRAY_U1__I4__I4__BYREF_U4__BYREF_U4,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_I2c_Provider_DefaultI2cControllerProvider::AcquireNative___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_I2c_Provider_DefaultI2cControllerProvider::ReleaseNative___VOID,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_I2c_Provider_DefaultI2cDeviceProvider::ReadInternal___VOID__SZARRAY_U1__I4__I4__BYREF_U4__BYREF_GHIElectronicsTinyCLRDevicesI2cProviderProviderI2cTransferStatus,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_I2c_Provider_DefaultI2cDeviceProvider::WriteInternal___VOID__SZARRAY_U1__I4__I4__BYREF_U4__BYREF_GHIElectronicsTinyCLRDevicesI2cProviderProviderI2cTransferStatus,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_I2c_Provider_DefaultI2cDeviceProvider::WriteReadInternal___VOID__SZARRAY_U1__I4__I4__SZARRAY_U1__I4__I4__BYREF_U4__BYREF_GHIElectronicsTinyCLRDevicesI2cProviderProviderI2cTransferStatus,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::get_MaxFrequency___R8,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::get_MinFrequency___R8,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::get_PinCount___I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::DisablePin___VOID__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::EnablePin___VOID__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::AcquirePin___VOID__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::ReleasePin___VOID__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::SetDesiredFrequency___R8__R8,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::SetPulseParameters___VOID__I4__R8__BOOLEAN,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::AcquireNative___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Pwm_Provider_DefaultPwmControllerProvider::ReleaseNative___VOID,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Rtc_Provider_RtcControllerProvider::get_Now___mscorlibSystemDateTime,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Rtc_Provider_RtcControllerProvider::set_Now___VOID__mscorlibSystemDateTime,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Rtc_Provider_RtcControllerProvider::Acquire___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Rtc_Provider_RtcControllerProvider::Release___VOID,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Spi_Provider_DefaultSpiControllerProvider::AcquireNative___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Spi_Provider_DefaultSpiControllerProvider::ReleaseNative___VOID,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Spi_Provider_DefaultSpiDeviceProvider::ReadInternal___VOID__SZARRAY_U1__I4__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Spi_Provider_DefaultSpiDeviceProvider::WriteInternal___VOID__SZARRAY_U1__I4__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Spi_Provider_DefaultSpiDeviceProvider::TransferFullDuplexInternal___VOID__SZARRAY_U1__I4__SZARRAY_U1__I4__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Spi_Provider_DefaultSpiDeviceProvider::TransferSequentialInternal___VOID__SZARRAY_U1__I4__I4__SZARRAY_U1__I4__I4,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Spi_SpiBusInfo::ctor___VOID__I,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::get_ReadBufferSize___U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::set_ReadBufferSize___VOID__U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::get_WriteBufferSize___U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::set_WriteBufferSize___VOID__U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::get_UnreadCount___U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::get_UnwrittenCount___U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::ClearReadBuffer___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::ClearWriteBuffer___VOID,
    nullptr,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::NativeOpen___VOID__U4__U4__U4__U4__U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::NativeClose___VOID__U4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::NativeFlush___VOID,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::NativeRead___I4__SZARRAY_U1__I4__I4__I4,
    Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_SerialCommunication_SerialDevice__Stream::NativeWrite___I4__SZARRAY_U1__I4__I4__I4,
    nullptr,
    nullptr,
};

const TinyCLR_Interop_Assembly Interop_GHIElectronics_TinyCLR_Devices = {
    "GHIElectronics.TinyCLR.Devices",
    0xC8A0D70B,
    methods
};

