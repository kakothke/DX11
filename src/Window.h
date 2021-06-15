#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// Window�̍쐬���s���N���X
class Window : public Singleton<Window>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Window();
	~Window();
	//@}

	/// @name ����������
	//@{
	bool initialize(const LPCTSTR aWindowName, const USHORT& aWidth, const USHORT& aHeight);
	//@}

	/// @name ����֐�
	//@{
	/// �E�B���h�E�T�C�Y��ݒ肷��
	void setSize(const USHORT& aWidth, const USHORT& aHeight, const bool& aCenter = true);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �쐬�����E�B���h�E�n���h����Ԃ�
	const HWND hWnd() const;
	/// �E�B���h�E����Ԃ�
	const LPCTSTR windowName() const;
	/// �E�B���h�E���T�C�Y��Ԃ�
	const USHORT& windowWidth() const;
	/// �E�B���h�E�c�T�C�Y��Ԃ�
	const USHORT& windowHeight() const;
	//@}

private:
	/// @name �������֐�
	//@{
	/// ���d�N�����`�F�b�N����
	bool checkMultiple();
	/// �E�B���h�E���쐬����
	bool createWindow(const USHORT& aWidth, const USHORT& aHeight);
	/// �E�B���h�E�N���X��o�^����
	bool registerClass();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �E�B���h�E�n���h��
	HWND mHWnd;
	/// �~���[�e�b�N�X
	HANDLE mMutex;
	/// �E�B���h�E��
	LPCTSTR mWindowName;
	/// �E�B���h�E���T�C�Y
	USHORT mWindowWidth;
	/// �E�B���h�E�c�T�C�Y
	USHORT mWindowHeight;
	//@}

};

} // namespace
// EOF
