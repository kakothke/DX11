#pragma once

//-------------------------------------------------------------------------------------------------
#include <dinput.h>
#include "Singleton.h"
#include "Vector2.h"

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �}�E�X�̓��͏��擾�p�\����
enum class MouseCord
{
	Left,
	Right,
	Center,

	Button4,
	Button5,
	Button6,
	Button7,
	Button8,

	TERM,
};

/// Input�N���X
class Input : public Singleton<Input>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Input();
	~Input();
	//@}

	/// @name ������/�X�V
	//@{
	bool initialize();
	void update();
	//@}

	/// @name �L�[�{�[�h���
	//@{
	bool getKey(DWORD aCord) const;
	bool getKeyDown(DWORD aCord) const;
	bool getKeyUp(DWORD aCord) const;
	//@}

	/// @�}�E�X���
	//@{
	bool getMouseButton(MouseCord aCord) const;
	bool getMouseButtonDown(MouseCord aCord) const;
	bool getMouseButtonUp(MouseCord aCord) const;
	const Vector2& getMousePos() const;
	const Vector2& getMouseVelocity() const;
	const int& getMouseWheel() const;
	//@}

private:
	/// @name ���������֐�
	//@{
	void updateKey();
	void updateMouse();
	//@}

	/// @name �����萔
	//@{
	/// �L�[����
	const static int KEY_NUM = 256;
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// DirectInput�̃C���^�[�t�F�[�X
	LPDIRECTINPUT8 mInterface;
	/// DitectInput�̃f�o�C�X�i�L�[�{�[�h�j
	LPDIRECTINPUTDEVICE8 mKeyDevice;
	/// DitectInput�̃f�o�C�X�i�}�E�X�j
	LPDIRECTINPUTDEVICE8 mMouseDevice;

	/// �L�[�{�[�h�̓��͏��
	BYTE mKeyState[KEY_NUM];
	/// �L�[�{�[�h�̓��͏��
	BYTE mPrevKeyState[KEY_NUM];

	/// �}�E�X�̓��͏��
	DIMOUSESTATE mMouseState;
	/// �O�t���[���̃}�E�X�̓��͏��
	DIMOUSESTATE mPrevMouseState;
	/// �}�E�X���W
	Vector2 mMousePos;
	//@}

};

} // namespcae
// EOF
