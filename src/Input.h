#pragma once

//-------------------------------------------------------------------------------------------------
#include <dinput.h>
#include <Xinput.h>
#include "Singleton.h"
#include "Vector2.h"

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "xinput.lib")

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	bool getKey(const int& aCord) const;
	bool getKeyDown(const int& aCord) const;
	bool getKeyUp(const int& aCord) const;
	//@}

	/// @�}�E�X���
	//@{
	bool getMouseButton(const int& aCord) const;
	bool getMouseButtonDown(const int& aCord) const;
	bool getMouseButtonUp(const int& aCord) const;
	const Vector2& getMousePos() const;
	const Vector2& getMouseVelocity() const;
	const int& getMouseWheel() const;
	//@}

	/// @�Q�[���p�b�h���
	//@{
	bool getXInputButton(const int& aCord) const;
	bool getXInputButtonDown(const int& aCord) const;
	bool getXInputButtonUp(const int& aCord) const;
	bool getXInputTrigger(const int& aLR) const;
	bool getXInputTriggerDown(const int& aLR) const;
	bool getXInputTriggerUp(const int& aLR) const;
	const Vector2& getThumb(const int& aLR) const;
	//@}

private:
	/// @name ���������֐�
	//@{
	bool initializeKey();
	bool initializeMouse();
	
	void updateKey();
	void updateMouse();
	void updatePad();
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

	/// �L�[�{�[�h�̓��͏�
	BYTE mKeyState[KEY_NUM];
	/// �L�[�{�[�h�̓��͏�
	BYTE mPrevKeyState[KEY_NUM];

	/// �}�E�X�̓��͏��
	DIMOUSESTATE mMouseState;
	/// �O�t���[���̃}�E�X�̓��͏�
	DIMOUSESTATE mPrevMouseState;
	/// �}�E�X���W
	Vector2 mMousePos;
	/// �}�E�X���W�̑O�t���[������̈ړ���
	Vector2 mMouseVelocity;
	/// �}�E�X�̃z�C�[����
	int mMouseWheel;

	/// �Q�[���p�b�h�iXInput�j�̓��͏��
	XINPUT_STATE mXInputState;
	/// �O�t���[���̃Q�[���p�b�h�iXInput�j�̓��͏�
	XINPUT_STATE mPrevXInputState;
	/// �Q�[���p�b�h�iXInput�j�̃X�e�B�b�N�̓��͏�
	Vector2 mXInputThumbL;
	Vector2 mXInputThumbR;
	//@}

};

} // namespcae
// EOF
