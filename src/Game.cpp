#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Fps.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto RESOURCE = ResourceManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Game::Game()
	: mSceneManager()
{
}

//-------------------------------------------------------------------------------------------------
/// ����������
bool Game::initialize()
{
	// ���\�[�X������	
	RESOURCE->initialize();

	// �ŏ��ɓǂݍ��ރV�[�����Z�b�g
	mSceneManager.changeScene(SceneList::Game);

	// fps�ݒ�
	FPS->setFpsCount(Define::Fps);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// �A�v���P�[�V�����̃��C�����[�v
/// @return ���C�����[�v�𔲂��ăA�v���P�[�V�������I������(false)
bool Game::mainLoop()
{
	// ���͏�
	INPUT_MANAGER->update();

	// �Q�[������
	D3D11->drawStart(Define::ClearColor);
	mSceneManager.update();
	mSceneManager.draw();
	D3D11->drawEnd();

	// fps����
	FPS->update();

	return true;
}

} // namespace
// EOF
