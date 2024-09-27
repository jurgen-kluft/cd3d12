#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "cd3d12/amd/c_ags.h"

namespace ags
{
    typedef AGSReturnCode                            (*PFN_agsInitialize)(int agsVersion, const AGSConfiguration* config, AGSContext** context, AGSGPUInfo* gpuInfo);
    typedef AGSReturnCode                            (*PFN_agsDeInitialize)(AGSContext* context);
    typedef AGSReturnCode                            (*PFN_agsDriverExtensionsDX12_CreateDevice)(AGSContext* context, const AGSDX12DeviceCreationParams* creationParams, const AGSDX12ExtensionParams* extensionParams, AGSDX12ReturnedParams* returnedParams);
    typedef AGSReturnCode                            (*PFN_agsDriverExtensionsDX12_DestroyDevice)(AGSContext* context, ID3D12Device* device, unsigned int* deviceReferences);
    typedef AGSReturnCode                            (*PFN_agsDriverExtensionsDX12_PushMarker)(AGSContext* context, ID3D12GraphicsCommandList* commandList, const char* data);
    typedef AGSReturnCode                            (*PFN_agsDriverExtensionsDX12_PopMarker)(AGSContext* context, ID3D12GraphicsCommandList* commandList);

    static PFN_agsInitialize                         Initialize        = nullptr;
    static PFN_agsDeInitialize                       DeInitialize      = nullptr;
    static PFN_agsDriverExtensionsDX12_CreateDevice  DX12CreateDevice  = nullptr;
    static PFN_agsDriverExtensionsDX12_DestroyDevice DX12DestroyDevice = nullptr;
    static PFN_agsDriverExtensionsDX12_PushMarker    DX12PushMarker    = nullptr;
    static PFN_agsDriverExtensionsDX12_PopMarker     DX12PopMarker     = nullptr;

    static AGSContext* s_pContext = nullptr;

    HRESULT CreateDevice(IDXGIAdapter* pAdapter, D3D_FEATURE_LEVEL minimumFeatureLevel, REFIID riid, void** ppDevice)
    {
        HMODULE module = LoadLibrary(L"amd_ags_x64.dll");

        if (module)
        {
            Initialize        = (PFN_agsInitialize)GetProcAddress(module, "agsInitialize");
            DeInitialize      = (PFN_agsDeInitialize)GetProcAddress(module, "agsDeInitialize");
            DX12CreateDevice  = (PFN_agsDriverExtensionsDX12_CreateDevice)GetProcAddress(module, "agsDriverExtensionsDX12_CreateDevice");
            DX12DestroyDevice = (PFN_agsDriverExtensionsDX12_DestroyDevice)GetProcAddress(module, "agsDriverExtensionsDX12_DestroyDevice");
            DX12PushMarker    = (PFN_agsDriverExtensionsDX12_PushMarker)GetProcAddress(module, "agsDriverExtensionsDX12_PushMarker");
            DX12PopMarker     = (PFN_agsDriverExtensionsDX12_PopMarker)GetProcAddress(module, "agsDriverExtensionsDX12_PopMarker");

            int              version = AGS_MAKE_VERSION(AMD_AGS_VERSION_MAJOR, AMD_AGS_VERSION_MINOR, AMD_AGS_VERSION_PATCH);
            AGSConfiguration config  = {};
            if (AGS_SUCCESS != Initialize(version, &config, &s_pContext, nullptr))
            {
                return S_FALSE;
            }

            AGSDX12DeviceCreationParams creationParams;
            creationParams.pAdapter     = pAdapter;
            creationParams.iid          = riid;
            creationParams.FeatureLevel = minimumFeatureLevel;

            AGSDX12ExtensionParams extensionParams = {};
            AGSDX12ReturnedParams  returnedParams  = {};
            AGSReturnCode          code            = DX12CreateDevice(s_pContext, &creationParams, &extensionParams, &returnedParams);

            *ppDevice = returnedParams.pDevice;

            return code == AGS_SUCCESS ? S_OK : S_FALSE;
        }

        return S_FALSE;
    }

    HRESULT ReleaseDevice(ID3D12Device* pDevice)
    {
        if (s_pContext)
        {
            DX12DestroyDevice(s_pContext, pDevice, nullptr);

            DeInitialize(s_pContext);
            s_pContext = nullptr;
            return S_OK;
        }
        return S_FALSE;
    }

    void BeginEvent(ID3D12GraphicsCommandList* pCommandList, const char* event)
    {
        if (s_pContext)
        {
            DX12PushMarker(s_pContext, pCommandList, event);
        }
    }

    void EndEvent(ID3D12GraphicsCommandList* pCommandList)
    {
        if (s_pContext)
        {
            DX12PopMarker(s_pContext, pCommandList);
        }
    }
}  // namespace ags
