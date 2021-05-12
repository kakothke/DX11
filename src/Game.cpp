#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "ObjLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Game::Game()
	: mSceneManager()
	, mFps()
{
	// Singleton�N���X���p�����Ă���N���X�̎��̉�
	ObjLoader::getInst();
	ShaderLoader::getInst();
}

//-------------------------------------------------------------------------------------------------
/// �A�v���P�[�V�����̃��C�����[�v
/// @return ���C�����[�v�𔲂��ăA�v���P�[�V�������I������(false)
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
