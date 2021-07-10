#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <memory>
#include <list>
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �O���錾
class BaseGameObject;

/// �Q�[���I�u�W�F�N�g�Z�b�g�C���^�[�t�F�[�X
class ISetGameObject
{
public:
	ISetGameObject() = default;
	virtual ~ISetGameObject() = default;

	virtual void setGameObjectListToWorld(BaseGameObject* aObject, const int& aLayer = 0, const bool& aAlphaBlend = false) = 0;
	virtual void setGameObjectListToBackground(BaseGameObject* aObject, const int& aLayer = 0) = 0;
	virtual void setGameObjectListToCanvas(BaseGameObject* aObject, const int& aLayer = 0) = 0;

};

} // namespace
// EOF
