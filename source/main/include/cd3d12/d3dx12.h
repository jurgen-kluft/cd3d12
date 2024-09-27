//*********************************************************
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License (MIT).
//
//*********************************************************

#ifndef __D3DX12_H__
#define __D3DX12_H__

#include "cd3d12/d3d12.h"

#if defined( __cplusplus )

#include "cd3d12/d3dx12_barriers.h"
#include "cd3d12/d3dx12_core.h"
#include "cd3d12/d3dx12_default.h"
#include "cd3d12/d3dx12_pipeline_state_stream.h"
#include "cd3d12/d3dx12_render_pass.h"
#include "cd3d12/d3dx12_resource_helpers.h"
#include "cd3d12/d3dx12_root_signature.h"
#include "cd3d12/d3dx12_property_format_table.h"

#ifndef D3DX12_NO_STATE_OBJECT_HELPERS
#include "cd3d12/d3dx12_state_object.h"
#endif // !D3DX12_NO_STATE_OBJECT_HELPERS

#ifndef D3DX12_NO_CHECK_FEATURE_SUPPORT_CLASS
#include "cd3d12/d3dx12_check_feature_support.h"
#endif // !D3DX12_NO_CHECK_FEATURE_SUPPORT_CLASS

#endif // defined( __cplusplus )

#endif //__D3DX12_H__

