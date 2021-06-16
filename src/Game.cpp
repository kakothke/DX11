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
	auto input = Input::getInst();
	if (!input->initialize()) {
		return false;
	}
	auto sound = Sound::getInst();
	if (!sound->initialize()) {
		return false;
	}
	auto resource = ResourceManager::getInst();
	if (!resource->initialize()) {
		return false;
	}

	// フォントテスト
	auto font = FontLoader::getInst();
	// あんずもじ湛(res/font/APJapanesefontF.ttf)
	if (!font->load(TEXT("ＭＳ Ｐ明朝"))) {
		return false;
	}
	FontRenderer tset;
	tset.draw(TEXT("あ"));

	// テストサウンド
	sound->load("res/bgm/music_0.wav");
	sound->setLoop(0, true, 2);
	sound->setLoopPos(0, 855273, 2565818);
	sound->play(0);

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
	static auto input = Input::getInst();
	static auto inputManager = InputManager::getInst();
	input->update();
	inputManager->update();

	// ゲーム内部
	static auto d3d11 = Direct3D11::getInst();
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
