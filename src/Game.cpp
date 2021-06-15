#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Input.h"
#include "InputManager.h"
#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
	if (!ResourceManager::getInst()->initialize()) {
		return false;
	}
	if (!Sound::getInst()->initialize()) {
		return false;
	}
	Sound::getInst()->load("res/bgm/music_0.wav");
	Sound::getInst()->load("res/se/test.wav");
	Sound::getInst()->load("res/se/test.wav");
	Sound::getInst()->setLoop(0, true, 2);
	Sound::getInst()->setLoopPos(0, 855273, 2565818);
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

	static float vol = 1;

	if (Input::getInst()->getKeyDown(DIK_Z)) {
		Sound::getInst()->playOneShot(1);
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
	if (Input::getInst()->getKeyDown(DIK_C)) {
		Sound::getInst()->setLoop(1, false);
	}
	if (Input::getInst()->getKeyDown(DIK_UP)) {
		vol += 0.05f;
		Sound::getInst()->setVolume(1,vol);
	}
	if (Input::getInst()->getKeyDown(DIK_DOWN)) {
		vol -= 0.05f;
		Sound::getInst()->setVolume(1, vol);
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
