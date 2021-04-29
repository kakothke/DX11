#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d9.h>

//-------------------------------------------------------------------------------------------------
/// DirectXオブジェクトを開放する
/// @param aD3DObject 開放するオブジェクト
#define SAFE_RELEASE(aD3DObject) \
    if (aD3DObject) { \
	    aD3DObject->Release(); \
	    aD3DObject = nullptr; \
    } 

//-------------------------------------------------------------------------------------------------
/// 配列を破棄する
/// @param aArray 破棄する配列
#define SAFE_DELETE_ARRAY(aArray) \
	if (aArray) { \
		delete[] (aArray); \
		aArray = nullptr; \
	}

// EOF
