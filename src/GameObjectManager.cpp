#include "GameObjectManager.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
bool compAlphaBlendObject(BaseGameObject* aObject1, BaseGameObject* aObject2);

//-------------------------------------------------------------------------------------------------
static Vector3 gCameraPos = Vector3();

//-------------------------------------------------------------------------------------------------
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameObjectManager::GameObjectManager()
	: mWorldGameObjectList()
	, mWorldGameObjectListAlpha()
	, mBackgroundGameObjectList()
	, mCanvasGameObjectList()
	, mCameraGameObjectList()
{
	mWorldGameObjectList.clear();
	mWorldGameObjectListAlpha.clear();
	mBackgroundGameObjectList.clear();
	mCanvasGameObjectList.clear();
	mCameraGameObjectList.clear();
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
	for (const auto& layer : mCameraGameObjectList) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mCameraGameObjectList.clear();
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameObjectManager::update()
{
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
	for (auto& layer : mCameraGameObjectList) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// 更新
			if ((*itr)->activeSelf()) {
				(*itr)->update();
				(*itr)->updateConstantBuffer();
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
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameObjectManager::draw()
{
	// カメラがセットされていなければ描画しない
	if (mCameraGameObjectList.empty()) {
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
		// カメラから遠い順にソート
		gCameraPos = mCameraGameObjectList[0].front()->transform().pos + mCameraGameObjectList[0].front()->transform().localPos;
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
	for (const auto& layer : mCameraGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトを生成する（ワールド空間）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
/// @param aAlphaBlend アルファブレンドを適用するか
void GameObjectManager::instanceToWorld(BaseGameObject* aObject, const int& aLayer)
{
	mWorldGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトを生成する（ワールド空間/アルファブレンド）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
/// @param aAlphaBlend アルファブレンドを適用するか
void GameObjectManager::instanceToWorldAlpha(BaseGameObject* aObject, const int& aLayer)
{
	mWorldGameObjectListAlpha[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトを生成する（背景）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
void GameObjectManager::instanceToBackground(BaseGameObject* aObject, const int& aLayer)
{
	mBackgroundGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトを生成する（キャンバス）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
void GameObjectManager::instanceToCanvas(BaseGameObject* aObject, const int& aLayer)
{
	mCanvasGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// ゲームオブジェクトを生成する（カメラ）
/// @param aObject 追加するゲームオブジェクト
/// @param aLayer 処理順を決めるレイヤー
void GameObjectManager::instanceToCamera(BaseCamera* aObject, const int& aLayer)
{
	mCameraGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// タグからゲームオブジェクトをひとつ検索する（ワールド空間）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
BaseGameObject* GameObjectManager::findWorldGameObject(const GameObjectTag& aTag)
{
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}	
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// タグからゲームオブジェクトをひとつ検索する（ワールド空間/アルファブレンド）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
BaseGameObject* GameObjectManager::findWorldGameObjectAlpha(const GameObjectTag& aTag)
{
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	return nullptr;
}


//-------------------------------------------------------------------------------------------------
/// タグからゲームオブジェクトをひとつ検索する（背景）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
BaseGameObject* GameObjectManager::findBackgroundGameObject(const GameObjectTag& aTag)
{
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// タグからゲームオブジェクトをひとつ検索する（キャンバス）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
BaseGameObject* GameObjectManager::findCanvasGameObject(const GameObjectTag& aTag)
{
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
/// タグからゲームオブジェクトをひとつ検索する（カメラ）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
BaseCamera* GameObjectManager::findCameraGameObject(const GameObjectTag& aTag)
{
	for (const auto& layer : mCameraGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// タグからゲームオブジェクトを複数検索する（ワールド空間）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
std::vector<BaseGameObject*> GameObjectManager::findWorldGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// タグからゲームオブジェクトを複数検索する（ワールド空間/アルファブレンド）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
std::vector<BaseGameObject*> GameObjectManager::findWorldGameObjectsAlpha(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// タグからゲームオブジェクトを複数検索する（背景）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
std::vector<BaseGameObject*> GameObjectManager::findBackgroundGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// タグからゲームオブジェクトを複数検索する（キャンバス）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
std::vector<BaseGameObject*> GameObjectManager::findCanvasGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
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
/// タグからゲームオブジェクトを複数検索する（カメラ）
/// @param aTag 検索したいゲームオブジェクトのタグ
/// @return 見つかったゲームオブジェクト
std::vector<BaseCamera*> GameObjectManager::findCameraGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseCamera*> out = {};
	for (const auto& layer : mCameraGameObjectList) {
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
	Vector3 objPos1 = aObject1->transform().pos + aObject1->transform().localPos;
	Vector3 objPos2 = aObject2->transform().pos + aObject2->transform().localPos;
	float length1 = (gCameraPos - objPos1).SqrMagnitude();
	float length2 = (gCameraPos - objPos2).SqrMagnitude();

	// カメラからの距離が遠い順にソート
	if (length1 > length2) {
		return true;
	}

	return false;
}

} // namespace
// EOF
