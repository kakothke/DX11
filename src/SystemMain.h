#pragma once

//-------------------------------------------------------------------------------------------------
#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �V�X�e���Ǘ��N���X
class SystemMain
{
public:
	/// @name �R���X�g���N�^
	//@{
	SystemMain();
	//@}

	/// @name WinMain����Ăяo�����֐�
	//@{
	/// ����������
	bool initialize();
	/// ���b�Z�[�W���[�v
	void msgLoop();
	//@}

private:
	// @name �v���C�x�[�g�����o�ϐ�
	//@{
	Window mWindow;
	//@}

};

} // namespace
// EOF
