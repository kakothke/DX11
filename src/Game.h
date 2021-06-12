#pragma once

//-------------------------------------------------------------------------------------------------
#include "SceneManager.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	Fps mFps;
	//@}

};

} // namespace
// EOF
