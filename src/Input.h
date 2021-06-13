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
	bool getKey(const int& aCode) const;
	bool getKeyDown(const int& aCode) const;
	bool getKeyUp(const int& aCode) const;
	//@}

	/// @�}�E�X���
	//@{
	bool getMouseButton(const int& aCode) const;
	bool getMouseButtonDown(const int& aCode) const;
	bool getMouseButtonUp(const int& aCode) const;
	const Vector2& getMousePos() const;
	const Vector2& getMouseVelocity() const;
	const int& getMouseWheel() const;
	//@}

	/// @�Q�[���p�b�h���
	//@{
	bool getXInputButton(const int& aCode) const;
	bool getXInputButtonDown(const int& aCode) const;
	bool getXInputButtonUp(const int& aCode) const;
	bool getXInputTrigger(const int& aLR) const;
	bool getXInputTriggerDown(const int& aLR) const;
	bool getXInputTriggerUp(const int& aLR) const;
	const Vector2& getXInputThumb(const int& aLR) const;
	//@}

private:
	/// @name ��������
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
