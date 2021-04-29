#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d9.h>

//-------------------------------------------------------------------------------------------------
/// DirectX�I�u�W�F�N�g���J������
/// @param aD3DObject �J������I�u�W�F�N�g
#define SAFE_RELEASE(aD3DObject) \
    if (aD3DObject) { \
	    aD3DObject->Release(); \
	    aD3DObject = nullptr; \
    } 

//-------------------------------------------------------------------------------------------------
/// �z���j������
/// @param aArray �j������z��
#define SAFE_DELETE_ARRAY(aArray) \
	if (aArray) { \
		delete[] (aArray); \
		aArray = nullptr; \
	}

// EOF
