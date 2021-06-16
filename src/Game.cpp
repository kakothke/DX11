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

	// �t�H���g�e�X�g
	auto font = FontLoader::getInst();
	// ���񂸂����X(res/font/APJapanesefontF.ttf)
	if (!font->load(TEXT("�l�r �o����"))) {
		return false;
	}
	FontRenderer tset;
	tset.draw(TEXT("��"));

	// �e�X�g�T�E���h
	sound->load("res/bgm/music_0.wav");
	sound->setLoop(0, true, 2);
	sound->setLoopPos(0, 855273, 2565818);
	sound->play(0);

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
	static auto input = Input::getInst();
	static auto inputManager = InputManager::getInst();
	input->update();
	inputManager->update();

	// �Q�[������
	static auto d3d11 = Direct3D11::getInst();
	d3d11->drawStart(Define::ClearColor);
	mSceneManager.update();
	mSceneManager.draw();
	d3d11->drawEnd();

	// fps����
	mFps.update();
	mFps.wait();
	mFps.draw();

	return true;
}

} // namespace
// EOF
