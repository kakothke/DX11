#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <memory>
#include <list>
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 前方宣言
class BaseGameObject;

/// ゲームオブジェクトセットインターフェース
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
