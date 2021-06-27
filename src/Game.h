#pragma once

//-------------------------------------------------------------------------------------------------
#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �Q�[���S��
class Game
{
public:
	/// @name �R���X�g���N�^
	//@{
	Game();
	//@}

	/// @name ����������
	//{
	bool initialize();
	//@}

	/// @name �Q�[���̃��C�����[�v
	//@{
	bool mainLoop();
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�[���Ǘ�
	SceneManager mSceneManager;
	//@}

};

} // namespace
// EOF
