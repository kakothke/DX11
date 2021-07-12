#include "GameObjectManager.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
bool compAlphaBlendObject(BaseGameObject* aObject1, BaseGameObject* aObject2);

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
	for (const auto& layer : mWorldGameObjectList) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mWorldGameObjectList.clear();
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mWorldGameObjectListAlpha.clear();
	for (const auto& layer : mBackgroundGameObjectList) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mBackgroundGameObjectList.clear();
	for (const auto& layer : mCanvasGameObjectList) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mCanvasGameObjectList.clear();

	delete mCamera;
	mCamera = nullptr;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameObjectManager::update()
{
	if (!mCamera) {
		return;
	}

	// 背景
	for (auto& layer : mBackgroundGameObjectList) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// 更新
			if ((*itr)->activeSelf()) {
				(*itr)->update();
			}
			// 消去
			if ((*itr)->destroyFlag()) {
				delete (*itr);
				(*itr) = nullptr;
				itr = layer.second.erase(itr);
				continue;
			}
			itr++;
		}
	}

	// ワールド
	// アルファブレンド無し
	for (auto& layer : mWorldGameObjectList) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// 更新
			if ((*itr)->activeSelf()) {
				(*itr)->update();
			}
			// 消去
			if ((*itr)->destroyFlag()) {
				delete (*itr);
				(*itr) = nullptr;
				itr = layer.second.erase(itr);
				continue;
			}
			itr++;
		}
	}
	// アルファブレンド有り
	for (auto& layer : mWorldGameObjectListAlpha) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// 更新
			if ((*itr)->activeSelf()) {
				(*itr)->update();
			}
			// 消去
			if ((*itr)->destroyFlag()) {
				delete (*itr);
				(*itr) = nullptr;
				itr = layer.second.erase(itr);
				continue;
			}
			itr++;
		}
	}

	// キャンバス
	for (auto& layer : mCanvasGameObjectList) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// 更新
			if ((*itr)->activeSelf()) {
				(*itr)->update();
			}
			// 消去
			if ((*itr)->destroyFlag()) {
				delete (*itr);
				(*itr) = nullptr;
				itr = layer.second.erase(itr);
				continue;
			}
			itr++;
		}
	}

	// カメラ
	mCamera->update();
	mCamera->updateConstantBuffer();
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
	D3D11->setBlendMode(Direct3D11::BlendList::Normal);
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// ワールド
	// アルファブレンド無し
	D3D11->setZBuffer(true);
	D3D11->setBlendMode(Direct3D11::BlendList::None);
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}
	// アルファブレンド有り
	D3D11->setBlendMode(Direct3D11::BlendList::Normal);
	for (auto& layer : mWorldGameObjectListAlpha) {
		// ソート
		layer.second.sort(compAlphaBlendObject);
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// キャンバス
	D3D11->setZBuffer(false);
	D3D11->setBlendMode(Direct3D11::BlendList::Normal);
	for (const auto& layer : mCanvasGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// カメラ
	D3D11->setZBuffer(true);
	D3D11->setBlendMode(Direct3D11::BlendList::None);
	mCamera->draw();
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトをリストに追加（ワールド空間）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
/// @param aAlphaBlend アルファブレンドを適用するか
void GameObjectManager::setGameObjectListToWorld(BaseGameObject* aObject, const int& aLayer, const bool& aAlphaBlend)
{
	if (!aAlphaBlend) {
		// アルファブレンド無し
		mWorldGameObjectList[aLayer].emplace_back(aObject);
	} else {
		// アルファブレンド有り
		mWorldGameObjectListAlpha[aLayer].emplace_back(aObject);
	}
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトをリストに追加（背景）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
void GameObjectManager::setGameObjectListToBackground(BaseGameObject* aObject, const int& aLayer)
{
	mBackgroundGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトをリストに追加（キャンバス）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
void GameObjectManager::setGameObjectListToCanvas(BaseGameObject* aObject, const int& aLayer)
{
	mCanvasGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// カメラを設定する
/// @param aObject カメラオブジェクト
void GameObjectManager::setCameraObject(Camera* aObject)
{
	mCamera = aObject;
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトを検索する（単体）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return ゲームオブジェクト
BaseGameObject* GameObjectManager::findGameObject(const GameObjectTag& aTag)
{
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	for (const auto& layer : mCanvasGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトを検索する（複数）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return ゲームオブジェクト
std::vector<BaseGameObject*> GameObjectManager::findGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	for (const auto& layer : mCanvasGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// アルファブレンドが適用されているオブジェクトの描画順をカメラからの距離が遠い順にソートする
bool compAlphaBlendObject(BaseGameObject* aObject1, BaseGameObject* aObject2)
{
	// カメラからの距離を計算
	Vector3 cameraPos = Vector3(0.0f, 0.0f, -30.0f);
	Vector3 objPos1 = aObject1->transform().pos - aObject1->transform().localPos;
	Vector3 objPos2 = aObject2->transform().pos - aObject2->transform().localPos;
	float length1 = (cameraPos - objPos1).SqrMagnitude();
	float length2 = (cameraPos - objPos2).SqrMagnitude();

	// カメラからの距離が遠い順にソート
	if (length1 > length2) {
		return true;
	}

	return false;
}

} // namespace
// EOF
