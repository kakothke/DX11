#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Input.h"
#include "InputManager.h"
#include "Resource.h"
#include "Sound.h"

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
	if (!Sound::getInst()->initialize()) {
		return false;
	}
	Sound::getInst()->load("res/bgm/test.wav");
	Sound::getInst()->load("res/se/test.wav");
	Sound::getInst()->load("res/se/test.wav");
	Sound::getInst()->play(0);

	// �ŏ��ɓǂݍ��ރV�[�����Z�b�g
	mSceneManager.changeScene(SceneList::Test);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �A�v���P�[�V�����̃��C�����[�v
/// @return ���C�����[�v�𔲂��ăA�v���P�[�V�������I������(false)
bool Game::mainLoop()
{
	// ���͏�
	Input::getInst()->update();
	InputManager::getInst()->update();

	if (Input::getInst()->getKeyDown(DIK_Z)) {
		Sound::getInst()->playOneShot(1, false);
	}
	if (Input::getInst()->getKeyDown(DIK_A)) {
		Sound::getInst()->playOneShot(1, true);
	}
	if (Input::getInst()->getKeyDown(DIK_X)) {
		Sound::getInst()->pause(1);
	}
	if (Input::getInst()->getKeyDown(DIK_S)) {
		Sound::getInst()->stop(1);
	}

	// �Q�[������
	Direct3D11::getInst()->drawStart();
	mSceneManager.update();
	mSceneManager.draw();
	Direct3D11::getInst()->drawEnd();

	// fps����
	mFps.update();
	mFps.wait();
	mFps.draw();

	return true;
}

} // namespace
// EOF
