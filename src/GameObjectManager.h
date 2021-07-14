#pragma once

//-------------------------------------------------------------------------------------------------
#include "ISetGameObjectList.h"

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <list>
#include <map>
#include "BaseGameObject.h"
#include "GameObjectTag.h"
#include "Camera.h"

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
	void setCameraObject(Camera* aObject);
	BaseGameObject* findGameObject(const GameObjectTag& aTag) override;
	std::vector<BaseGameObject*> findGameObjects(const GameObjectTag& aTag) override;
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
	/// カメラ
	Camera* mCamera;
	//@}

};

} // namespace
// EOF