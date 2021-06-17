#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Game::Game()
	: mSceneManager()
	, mFps()
{
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
bool Game::initialize()
{
	// リソース初期化
	const auto resource = ResourceManager::getInst();
	resource->initialize();

	// 最初に読み込むシーンをセット
	mSceneManager.changeScene(SceneList::Test);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// アプリケーションのメインループ
/// @return メインループを抜けてアプリケーションが終了する(false)
bool Game::mainLoop()
{
	// 入力状況
	const static auto inputManager = InputManager::getInst();
	inputManager->update();

	// ゲーム内部
	const static auto d3d11 = Direct3D11::getInst();
	d3d11->drawStart(Define::ClearColor);
	mSceneManager.update();
	mSceneManager.draw();
	d3d11->drawEnd();

	// fps制御
	mFps.update();
	mFps.wait();
	mFps.draw();

	return true;
}

} // namespace
// EOF
