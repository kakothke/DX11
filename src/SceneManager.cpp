#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SceneManager::SceneManager()
	: mSceneStack()
{
	// �e�X�g�V�[�����v�b�V��
	mSceneStack.push(std::make_shared<TestScene>(this));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
SceneManager::~SceneManager()
{
	// �X�^�b�N��S���|�b�v����(�X�^�b�N����ɂ���)
	while (!mSceneStack.empty()) {
		mSceneStack.pop();
	}
}

//-------------------------------------------------------------------------------------------------
/// ����
void SceneManager::run()
{
	if (!mSceneStack.empty()) {
		mSceneStack.top()->update();
		mSceneStack.top()->draw();
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
	case SceneList::Test:
		mSceneStack.push(std::make_shared<TestScene>(this));
		break;
	case SceneList::Title:
		//mSceneStack.push(std::make_shared<TitleScene>(this));
		break;
	case SceneList::Game:
		//mSceneStack.push(std::make_shared<GameScene>(this));
		break;
	default:
		// �G���[���b�Z�[�W
		MessageBox(nullptr, TEXT("�ǂݍ������Ƃ����V�[�������݂��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
