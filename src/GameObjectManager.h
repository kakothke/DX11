#pragma once

//-------------------------------------------------------------------------------------------------
#include <memory>
#include <list>
#include <unordered_map>
#include "BaseGameObject.h"
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ゲームオブジェクトマネージャー
class GameObjectManager
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

	/// @name ゲームオブジェクトをリストに追加する
	//@{
	void setGameObjectListToWorld(const std::shared_ptr<BaseGameObject>& aObject, const int& aLayer = 0, const bool& aAlphaBlend = false);
	void setGameObjectListToBackground(const std::shared_ptr<BaseGameObject>&, const int& aLayer = 0);
	void setGameObjectListToCanvas(const std::shared_ptr<BaseGameObject>&, const int& aLayer = 0);
	void setCameraObject(const std::shared_ptr<Camera>& aObject);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// ワールド空間リスト
	std::unordered_map<int, std::list<std::shared_ptr<BaseGameObject>>> mWorldGameObjectList;
	/// 透過有りワールド空間リスト
	std::unordered_map<int, std::list<std::shared_ptr<BaseGameObject>>> mWorldGameObjectListAlpha;
	/// 背景リスト
	std::unordered_map<int, std::list<std::shared_ptr<BaseGameObject>>> mBackgroundGameObjectList;
	/// キャンバスリスト
	std::unordered_map<int, std::list<std::shared_ptr<BaseGameObject>>> mCanvasGameObjectList;
	/// カメラリスト
	std::shared_ptr<Camera> mCamera;
	//@}

};

} // namespace
// EOF