#include "GHIElectronics_TinyCLR_Devices.h"
#include "GHIElectronics_TinyCLR_InteropUtil.h"

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::get_ChannelCount___I4(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);    
    auto ret = TinyCLR_Interop_GetReturn(md);

    ret.Data.Numeric->I4 = (int32_t)provider->GetChannelCount(provider);

    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::get_ResolutionInBits___I4(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);
    auto ret = TinyCLR_Interop_GetReturn(md);

    ret.Data.Numeric->I4 = provider->GetResolutionInBits(provider);

    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::get_MinValue___I4(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);
    auto ret = TinyCLR_Interop_GetReturn(md);

    ret.Data.Numeric->I4 = provider->GetMinValue(provider);

    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::get_MaxValue___I4(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);
    auto ret = TinyCLR_Interop_GetReturn(md);

    ret.Data.Numeric->I4 = provider->GetMaxValue(provider);

    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::IsChannelModeSupported___BOOLEAN__GHIElectronicsTinyCLRDevicesAdcAdcChannelMode(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);
    auto arg1 = TinyCLR_Interop_GetArguments(md, 1);
    auto ret = TinyCLR_Interop_GetReturn(md);

    ret.Data.Numeric->Boolean = provider->IsChannelModeSupported(provider, (TinyCLR_Adc_ChannelMode)arg1.Data.Numeric->U4) ? true : false;

    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::GetChannelMode___GHIElectronicsTinyCLRDevicesAdcAdcChannelMode(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);
    auto ret = TinyCLR_Interop_GetReturn(md);

    ret.Data.Numeric->I4 = (int32_t)provider->GetChannelMode(provider);

    return TinyCLR_Result::Success;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::SetChannelMode___VOID__GHIElectronicsTinyCLRDevicesAdcAdcChannelMode(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);
    auto arg1 = TinyCLR_Interop_GetArguments(md, 1);

    return provider->SetChannelMode(provider, (TinyCLR_Adc_ChannelMode)arg1.Data.Numeric->U4);
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::OpenChannel___VOID__I4(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);
    auto arg1 = TinyCLR_Interop_GetArguments(md, 1);

    return provider->OpenChannel(provider, arg1.Data.Numeric->U4);
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::CloseChannel___VOID__I4(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);
    auto arg1 = TinyCLR_Interop_GetArguments(md, 1);

    return provider->CloseChannel(provider, arg1.Data.Numeric->U4);
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::Read___I4__I4(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);
    auto arg1 = TinyCLR_Interop_GetArguments(md, 1);
    auto ret = TinyCLR_Interop_GetReturn(md);

    int32_t value = 0;

    auto error = provider->ReadChannel(provider, arg1.Data.Numeric->U4, value);

    ret.Data.Numeric->I4 = value;

    return error;
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::Acquire___VOID(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);

    return provider->Acquire(provider);
}

TinyCLR_Result Interop_GHIElectronics_TinyCLR_Devices_GHIElectronics_TinyCLR_Devices_Adc_Provider_AdcControllerApiWrapper::Release___VOID(const TinyCLR_Interop_MethodData md) {
    auto provider = (const TinyCLR_Adc_Controller*)TinyCLR_Interop_GetManager(md, FIELD___impl___I);

    return provider->Release(provider);
}
