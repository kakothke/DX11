#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// Window�̍쐬���s���N���X
class Window
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Window();
	~Window();
	//@}

	/// @name ����������
	//@{
	bool initialize();
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �쐬�����E�B���h�E�n���h����Ԃ�
	const HWND hWnd() const;
	//@}

private:
	/// @name �������֐�
	//@{
	/// ���d�N�����`�F�b�N����
	bool checkMultiple();
	/// �E�B���h�E���쐬����
	bool createWindow();
	/// �E�B���h�E�N���X��o�^����
	bool registerClass();
	/// �E�B���h�E�̃T�C�Y�𒲐�����
	void resizeWindow();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �E�B���h�E�n���h��
	HWND mWindowHandle;
	/// �~���[�e�b�N�X
	HANDLE mMutex;
	//@}

};

} // namespace
// EOF
