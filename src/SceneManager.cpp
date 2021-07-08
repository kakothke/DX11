#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
#include "GameScene.h"
#include "BossTestScene.h"
#include "DebugScene.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SceneManager::SceneManager()
	: mSceneStack()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
SceneManager::~SceneManager()
{
	// シーンのスタックを全部ポップする
	while (!mSceneStack.empty()) {
		mSceneStack.pop();
	}
}

//-------------------------------------------------------------------------------------------------
/// 更新
void SceneManager::update()
{
	if (!mSceneStack.empty()) {
		mSceneStack.top()->update();
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
void SceneManager::draw()
{
	if (!mSceneStack.empty()) {
		// 背景
		D3D11->setZBufferMode(0);
		D3D11->setBlendMode(BlendList::Normal);
		mSceneStack.top()->drawBackground();

		// ワールド
		D3D11->setZBufferMode(1);
		D3D11->setBlendMode(BlendList::None);
		mSceneStack.top()->draw();

		// スクリーン
		D3D11->setZBufferMode(0);
		D3D11->setBlendMode(BlendList::Normal);
		mSceneStack.top()->draw2D();
	}
}

//-------------------------------------------------------------------------------------------------
/// シーン遷移
/// @param aSceneList 切り替えるシーンを指定する構造体
void SceneManager::changeScene(const SceneList aSceneList)
{
	switch (aSceneList) {
	case SceneList::POP:
		// 現在のシーンをポップする
		mSceneStack.pop();
		break;
	case SceneList::Game:
		mSceneStack.push(std::make_shared<GameScene>(this));
		break;
	case SceneList::BossTest:
		mSceneStack.push(std::make_shared<BossTestScene>(this));
		break;
	case SceneList::Debug:
		mSceneStack.push(std::make_shared<DebugScene>(this));
		break;
	default:
		// エラーメッセージ
		MessageBox(nullptr, TEXT("読み込もうとしたシーンが存在しません。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
