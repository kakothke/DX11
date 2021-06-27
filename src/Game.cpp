#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto D3D11 = Direct3D11::getInst();
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto RESOURCE = ResourceManager::getInst();

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
	RESOURCE->initialize();

	// 最初に読み込むシーンをセット
	mSceneManager.changeScene(SceneList::Game);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// アプリケーションのメインループ
/// @return メインループを抜けてアプリケーションが終了する(false)
bool Game::mainLoop()
{
	// 入力状況
	INPUT_MANAGER->update();

	// ゲーム内部
	D3D11->drawStart(Define::ClearColor);
	mSceneManager.update();
	mSceneManager.draw();
	D3D11->drawEnd();

	// fps制御
	mFps.update();
	mFps.wait();
	mFps.draw();

	return true;
}

} // namespace
// EOF
