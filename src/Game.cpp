#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Input.h"
#include "Resource.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Game::Game()
	: mSceneManager()
	, mFps()
{
}

//-------------------------------------------------------------------------------------------------
/// ����������
bool Game::initialize()
{
	if (!Input::getInst()->initialize()) {
		return false;
	}
	if (!Resource::getInst()->initialize()) {
		return false;
	}

	// �ŏ��ɓǂݍ��ރV�[�����Z�b�g
	mSceneManager.changeScene(SceneList::Test);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �A�v���P�[�V�����̃��C�����[�v
/// @return ���C�����[�v�𔲂��ăA�v���P�[�V�������I������(false)
bool Game::mainLoop()
{
	Input::getInst()->update();

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
