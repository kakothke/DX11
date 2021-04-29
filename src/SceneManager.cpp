#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SceneManager::SceneManager()
	: mSceneStack()
{
	// テストシーンをプッシュ
	mSceneStack.push(std::make_shared<TestScene>(this));
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
SceneManager::~SceneManager()
{
	// スタックを全部ポップする(スタックを空にする)
	while (!mSceneStack.empty()) {
		mSceneStack.pop();
	}
}

//-------------------------------------------------------------------------------------------------
/// 動作
void SceneManager::run()
{
	if (!mSceneStack.empty()) {
		mSceneStack.top()->update();
		mSceneStack.top()->draw();
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
	case SceneList::Test:
		mSceneStack.push(std::make_shared<TestScene>(this));
		break;
	case SceneList::Title:
		//mSceneStack.push(std::make_shared<TitleScene>(this));
		break;
	case SceneList::Game:
		//mSceneStack.push(std::make_shared<GameScene>(this));
		break;
	default:
		// エラーメッセージ
		MessageBox(nullptr, TEXT("読み込もうとしたシーンが存在しません。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
