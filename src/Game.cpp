#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "ObjLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Game::Game()
	: mSceneManager()
	, mFps()
{
	// Singletonクラスを継承しているクラスの実体化
	ObjLoader::getInst();
	ShaderLoader::getInst();
}

//-------------------------------------------------------------------------------------------------
/// アプリケーションのメインループ
/// @return メインループを抜けてアプリケーションが終了する(false)
bool Game::mainLoop()
{
	Direct3D11::getInst()->drawStart();

	mFps.update();
	mSceneManager.update();
	mSceneManager.draw();
	mFps.wait();
	mFps.draw();

	Direct3D11::getInst()->drawEnd();

	return true;
}

} // namespace
// EOF
