#include "GameObjectManager.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
bool compAlphaBlendObject(const std::shared_ptr<BaseGameObject>& aObject1, const std::shared_ptr<BaseGameObject>& aObject2);

//-------------------------------------------------------------------------------------------------
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameObjectManager::GameObjectManager()
	: mWorldGameObjectList()
	, mWorldGameObjectListAlpha()
	, mBackgroundGameObjectList()
	, mCanvasGameObjectList()
	, mCamera(nullptr)
{
	mWorldGameObjectList.clear();
	mWorldGameObjectListAlpha.clear();
	mBackgroundGameObjectList.clear();
	mCanvasGameObjectList.clear();
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
GameObjectManager::~GameObjectManager()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameObjectManager::update()
{
	if (!mCamera) {
		return;
	}

	// 背景
	for (const auto layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->setCameraTransform(mCamera->transform());
				obj->update();
			}
		}
	}

	// ワールド
	for (const auto layer : mWorldGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->setCameraTransform(mCamera->transform());
				obj->update();
			}
		}
	}
	for (const auto layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->setCameraTransform(mCamera->transform());
				obj->update();
			}
		}
	}

	// キャンバス
	for (const auto layer : mCanvasGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->setCameraTransform(mCamera->transform());
				obj->update();
			}
		}
	}

	// カメラ
	mCamera->update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameObjectManager::draw()
{
	if (!mCamera) {
		return;
	}

	// 背景
	D3D11->setZBuffer(false);
	for (const auto layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// ワールド
	D3D11->setZBuffer(true);
	D3D11->setBlendMode(Direct3D11::BlendList::None);
	for (const auto layer : mWorldGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}
	for (auto layer : mWorldGameObjectListAlpha) {
		layer.second.sort(compAlphaBlendObject);
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// キャンバス
	D3D11->setZBuffer(false);
	for (const auto layer : mCanvasGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// カメラ
	mCamera->draw();
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトをリストに追加（ワールド空間）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
/// @param aAlphaBlend アルファブレンドを適用するか
void GameObjectManager::setGameObjectListToWorld(const std::shared_ptr<BaseGameObject>& aObject, const int& aLayer, const bool& aAlphaBlend)
{
	if (aAlphaBlend) {
		mWorldGameObjectListAlpha[aLayer].emplace_back(aObject);
	} else {
		mWorldGameObjectList[aLayer].emplace_back(aObject);
	}
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトをリストに追加（背景）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
void GameObjectManager::setGameObjectListToBackground(const std::shared_ptr<BaseGameObject>& aObject, const int& aLayer)
{
	mBackgroundGameObjectList[aLayer].emplace_back(aObject);
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトをリストに追加（キャンバス）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
void GameObjectManager::setGameObjectListToCanvas(const std::shared_ptr<BaseGameObject>& aObject, const int& aLayer)
{
	mCanvasGameObjectList[aLayer].emplace_back(aObject);
}

//-------------------------------------------------------------------------------------------------
/// カメラを設定する
/// @param aObject カメラオブジェクト
void GameObjectManager::setCameraObject(const std::shared_ptr<Camera>& aObject)
{
	mCamera = aObject;
}

//-------------------------------------------------------------------------------------------------
/// アルファブレンドが適用されているオブジェクトの描画順をカメラからの距離が遠い順にソートする
bool compAlphaBlendObject(const std::shared_ptr<BaseGameObject>& aObject1, const std::shared_ptr<BaseGameObject>& aObject2)
{
	float length1 = (aObject1->cameraTransform().pos - aObject1->transform().pos).SqrMagnitude();
	float length2 = (aObject2->cameraTransform().pos - aObject2->transform().pos).SqrMagnitude();

	if (length1 > length2) {
		return true;
	}

	return false;
}

} // namespace
// EOF
