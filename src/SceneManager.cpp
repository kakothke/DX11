#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Direct3D11.h"
#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SceneManager::SceneManager()
	: mSceneStack()
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
SceneManager::~SceneManager()
{
	// �V�[���̃X�^�b�N��S���|�b�v����
	while (!mSceneStack.empty()) {
		mSceneStack.pop();
	}
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void SceneManager::update()
{
	if (!mSceneStack.empty()) {
		mSceneStack.top()->update();
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
void SceneManager::draw()
{
	if (!mSceneStack.empty()) {
		const static auto d3d11 = Direct3D11::getInst();
		d3d11->zBufferOff();
		mSceneStack.top()->drawBackground();
		d3d11->zBufferOn();
		mSceneStack.top()->draw();
		d3d11->zBufferOff();
		mSceneStack.top()->draw2D();
	}
}

//-------------------------------------------------------------------------------------------------
/// �V�[���J��
/// @param aSceneList �؂�ւ���V�[�����w�肷��\����
void SceneManager::changeScene(const SceneList aSceneList)
{
	switch (aSceneList) {
	case SceneList::POP:
		// ���݂̃V�[�����|�b�v����
		mSceneStack.pop();
		break;
	case SceneList::Game:
		mSceneStack.push(std::make_shared<GameScene>(this));
		break;
	default:
		// �G���[���b�Z�[�W
		MessageBox(nullptr, TEXT("�ǂݍ������Ƃ����V�[�������݂��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
