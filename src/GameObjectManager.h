#pragma once

//-------------------------------------------------------------------------------------------------
#include "ISetGameObjectList.h"

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <list>
#include <map>
#include "BaseGameObject.h"
#include "GameObjectTag.h"
#include "BaseCamera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ゲームオブジェクトマネージャー
class GameObjectManager : public ISetGameObject
{
public:
	/// @name コンストラクタ/デストラクタ 
	//@{
	GameObjectManager();
	~GameObjectManager();
	//@}

	/// @name 更新/描画
	//@{
	void update();
	void draw();
	//@}

	/// @name ゲームオブジェクトリスト操作
	//@{
	void instanceToWorld(BaseGameObject* aObject, const int& aLayer = 0) override;
	void instanceToWorldAlpha(BaseGameObject* aObject, const int& aLayer = 0) override;
	void instanceToBackground(BaseGameObject* aObject, const int& aLayer = 0) override;
	void instanceToCanvas(BaseGameObject* aObject, const int& aLayer = 0) override;
	void instanceToCamera(BaseCamera* aObject, const int& aLayer = 0) override;
	BaseGameObject* findWorldGameObject(const GameObjectTag& aTag) override;
	BaseGameObject* findWorldGameObjectAlpha(const GameObjectTag& aTag) override;
	BaseGameObject* findBackgroundGameObject(const GameObjectTag& aTag) override;
	BaseGameObject* findCanvasGameObject(const GameObjectTag& aTag) override;
	BaseCamera* findCameraGameObject(const GameObjectTag& aTag) override;
	std::vector<BaseGameObject*> findWorldGameObjects(const GameObjectTag& aTag) override;
	std::vector<BaseGameObject*> findWorldGameObjectsAlpha(const GameObjectTag& aTag) override;
	std::vector<BaseGameObject*> findBackgroundGameObjects(const GameObjectTag& aTag) override;
	std::vector<BaseGameObject*> findCanvasGameObjects(const GameObjectTag& aTag) override;
	std::vector<BaseCamera*> findCameraGameObjects(const GameObjectTag& aTag) override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// ワールド空間リスト
	std::map<int, std::list<BaseGameObject*>> mWorldGameObjectList;
	/// 透過有りワールド空間リスト
	std::map<int, std::list<BaseGameObject*>> mWorldGameObjectListAlpha;
	/// 背景リスト
	std::map<int, std::list<BaseGameObject*>> mBackgroundGameObjectList;
	/// キャンバスリスト
	std::map<int, std::list<BaseGameObject*>> mCanvasGameObjectList;
	/// カメラリスト
	std::map<int, std::list<BaseCamera*>> mCameraGameObjectList;
	//@}

};

} // namespace
// EOF