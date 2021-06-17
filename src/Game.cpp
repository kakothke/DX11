#include "Game.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Define.h"

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
	// ���\�[�X������
	const auto resource = ResourceManager::getInst();
	resource->initialize();

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
	const static auto inputManager = InputManager::getInst();
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
