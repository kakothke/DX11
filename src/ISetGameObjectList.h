#pragma once

//-------------------------------------------------------------------------------------------------
#include <vector>
#include "BaseGameObject.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 前方宣言
class BaseGameObject;
class Camera;

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
	virtual void instanceToCamera(Camera* aObject, const int& aLayer = 0) = 0;
	virtual BaseGameObject* findWorldGameObject(const GameObjectTag& aTag) = 0;
	virtual BaseGameObject* findWorldGameObjectAlpha(const GameObjectTag& aTag) = 0;
	virtual BaseGameObject* findBackgroundGameObject(const GameObjectTag& aTag) = 0;
	virtual BaseGameObject* findCanvasGameObject(const GameObjectTag& aTag) = 0;
	virtual Camera* findCameraGameObject(const GameObjectTag& aTag) = 0;
	virtual std::vector<BaseGameObject*> findWorldGameObjects(const GameObjectTag& aTag) = 0;
	virtual std::vector<BaseGameObject*> findWorldGameObjectsAlpha(const GameObjectTag& aTag) = 0;
	virtual std::vector<BaseGameObject*> findBackgroundGameObjects(const GameObjectTag& aTag) = 0;
	virtual std::vector<BaseGameObject*> findCanvasGameObjects(const GameObjectTag& aTag) = 0;
	virtual std::vector<Camera*> findCameraGameObjects(const GameObjectTag& aTag) = 0;

};

} // namespace
// EOF
