#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Input.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Define.h"
#include "Sound.h"
#include "FontRenderer.h"

#include "Window.h"

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
	const auto input = Input::getInst();
	if (!input->initialize()) {
		return false;
	}
	const auto sound = Sound::getInst();
	if (!sound->initialize()) {
		return false;
	}
	const auto resource = ResourceManager::getInst();
	if (!resource->initialize()) {
		return false;
	}

	// 最初に読み込むシーンをセット
	mSceneManager.changeScene(SceneList::Test);

	// テストサウンド
	sound->load("res/bgm/music_0.wav");
	sound->setLoop(0, true, 2);
	sound->setLoopPos(0, 855273, 2565818);
	sound->play(0);

	// フォントテスト
	const auto font = FontLoader::getInst();
	// TEXT("あんずもじ湛"),TEXT("res/font/APJapanesefontF.ttf")
	if (!font->load(TEXT("ＭＳ Ｐ明朝"))) {
		return false;
	}
	FontRenderer tset;
	tset.draw(TEXT("あ"));

	return true;
}

//-------------------------------------------------------------------------------------------------
/// アプリケーションのメインループ
/// @return メインループを抜けてアプリケーションが終了する(false)
bool Game::mainLoop()
{
	// 入力状況
	const static auto input = Input::getInst();
	const static auto inputManager = InputManager::getInst();
	input->update();
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
