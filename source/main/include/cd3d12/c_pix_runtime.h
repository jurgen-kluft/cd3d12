#ifndef __CGFX_PIX_RUNTIME_H__
#define __CGFX_PIX_RUNTIME_H__

#include "cd3d12/d3d12.h"

namespace ncore
{
    namespace ngfx
    {
        namespace pix
        {
            void Init();
            void BeginEvent(ID3D12GraphicsCommandList* pCommandList, const char* event);
            void EndEvent(ID3D12GraphicsCommandList* pCommandList);
        };  // namespace pix
    }  // namespace ngfx
}  // namespace ncore
#endif
