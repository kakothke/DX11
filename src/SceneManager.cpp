#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Direct3D11.h"
#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
		Direct3D11::getInst()->zBufferOff();
		mSceneStack.top()->drawBackground();
		Direct3D11::getInst()->zBufferOn();
		mSceneStack.top()->draw();
		Direct3D11::getInst()->zBufferOff();
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
