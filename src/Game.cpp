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

	// �ŏ��ɓǂݍ��ރV�[�����Z�b�g
	mSceneManager.changeScene(SceneList::Test);

	// �e�X�g�T�E���h
	sound->load("res/bgm/music_0.wav");
	sound->setLoop(0, true, 2);
	sound->setLoopPos(0, 855273, 2565818);
	sound->play(0);

	// �t�H���g�e�X�g
	const auto font = FontLoader::getInst();
	// TEXT("���񂸂����X"),TEXT("res/font/APJapanesefontF.ttf")
	if (!font->load(TEXT("�l�r �o����"))) {
		return false;
	}
	FontRenderer tset;
	tset.draw(TEXT("��"));

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �A�v���P�[�V�����̃��C�����[�v
/// @return ���C�����[�v�𔲂��ăA�v���P�[�V�������I������(false)
bool Game::mainLoop()
{
	// ���͏�
	const static auto input = Input::getInst();
	const static auto inputManager = InputManager::getInst();
	input->update();
	inputManager->update();

	// �Q�[������
	const static auto d3d11 = Direct3D11::getInst();
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
