#pragma once

//-------------------------------------------------------------------------------------------------
#include "IChangeScene.h"

//-------------------------------------------------------------------------------------------------
#include <stack>
#include <memory>
#include "SceneList.h"
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK{

/// �V�[���Ǘ�
class SceneManager : public IChangeScene
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	SceneManager();
	~SceneManager();
	//@}

	/// @name �X�V/�`��
	//@{
	void update();
	void draw();
	//@}

	/// @name �V�[���J��
	//@{
	void changeScene(const SceneList aSceneList) override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�[���̃X�^�b�N
	std::stack<std::shared_ptr<AbstractScene>> mSceneStack;
	//@}

};

} // namespace
// EOF
