#ifndef __CGFX_AGS_H__
#define __CGFX_AGS_H__

#include "cd3d12/d3dx12.h"
#include "cd3d12/amd/c_ags_sdk.h"

namespace ags
{
    HRESULT CreateDevice(IDXGIAdapter* pAdapter, D3D_FEATURE_LEVEL minimumFeatureLevel, REFIID riid, void** ppDevice);
    void ReleaseDevice(ID3D12Device* pDevice);

    void BeginEvent(ID3D12GraphicsCommandList* pCommandList, const char* event);
    void EndEvent(ID3D12GraphicsCommandList* pCommandList);
}
#endif
