#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
//#include "Mesh.h"
//#include "DebugFont.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Game::Game()
	: mSceneManager()
	, mFps()
{
	// シングルトンクラスを生成
	//Mesh::getInst();
	//DebugFont::getInst();
}

//-------------------------------------------------------------------------------------------------
/// アプリケーションのメインループ
/// @return falseを返すとメインループを抜けてアプリケーションが終了する
bool Game::mainLoop()
{
	Direct3D11::getInst()->drawStart();

	mFps.update();
	mSceneManager.run();
	mFps.wait();
	mFps.draw();

	Direct3D11::getInst()->drawEnd();

	return true;
}

} // namespace
// EOF
