#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>
#include "BaseGameObject.h"
#include "GameObjectTag.h"

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

	virtual void instanceToWorld(BaseGameObject* aObject, const int& aLayer = 0) = 0;
	virtual void instanceToWorldAlpha(BaseGameObject* aObject, const int& aLayer = 0) = 0;
	virtual void instanceToBackground(BaseGameObject* aObject, const int& aLayer = 0) = 0;
	virtual void instanceToCanvas(BaseGameObject* aObject, const int& aLayer = 0) = 0;
	virtual BaseGameObject* findGameObject(const GameObjectTag& aTag) = 0;
	virtual std::vector<BaseGameObject*> findGameObjects(const GameObjectTag& aTag) = 0;

};

} // namespace
// EOF
