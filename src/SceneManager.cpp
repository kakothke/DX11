#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SceneManager::SceneManager()
	: mSceneStack()
{
	// 最初に読み込むシーンをプッシュ
	mSceneStack.push(std::make_shared<TestScene>(this));
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
	default:
		// エラーメッセージ
		MessageBox(nullptr, TEXT("読み込もうとしたシーンが存在しません。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
