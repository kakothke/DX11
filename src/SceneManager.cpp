#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SceneManager::SceneManager()
	: mSceneStack()
{
	// �ŏ��ɓǂݍ��ރV�[�����v�b�V��
	mSceneStack.push(std::make_shared<TestScene>(this));
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
	default:
		// �G���[���b�Z�[�W
		MessageBox(nullptr, TEXT("�ǂݍ������Ƃ����V�[�������݂��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
