#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Game.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	bool initialize() const;
	/// ���b�Z�[�W���[�v
	void msgLoop();
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	//@}

};

} // namespace
// EOF
