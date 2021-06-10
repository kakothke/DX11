#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Game::Game()
	: mSceneManager()
	, mFps()
{
}

//-------------------------------------------------------------------------------------------------
/// アプリケーションのメインループ
/// @return メインループを抜けてアプリケーションが終了する(false)
bool Game::mainLoop()
{
	Direct3D11::getInst()->drawStart();
	mSceneManager.update();
	mSceneManager.draw();
	Direct3D11::getInst()->drawEnd();

	mFps.update();
	mFps.wait();
	mFps.draw();

	return true;
}

} // namespace
// EOF
