#include "Input.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
Input::Input()
	: mInterface(nullptr)
	, mKeyDevice(nullptr)
	, mMouseDevice(nullptr)
	, mKeyState()
	, mPrevKeyState()
	, mMouseState()
	, mPrevMouseState()
	, mMousePos()
	, mMouseVelocity()
	, mMouseWheel(0)
	, mXInputState()
	, mPrevXInputState()
	, mXInputThumbL()
	, mXInputThumbR()
{
}

//-------------------------------------------------------------------------------------------------
Input::~Input()
{
	if (mKeyDevice) {
		mKeyDevice->Unacquire();
		mKeyDevice->Release();
		mKeyDevice = nullptr;
	}
	if (mMouseDevice) {
		mMouseDevice->Unacquire();
		mMouseDevice->Release();
		mMouseDevice = nullptr;
	}
	if (mInterface) {
		mInterface->Release();
		mInterface = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
bool Input::initialize()
{
	HRESULT hr;

	// �C���^�[�t�F�[�X���쐬����
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mInterface, NULL);
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("DirectInput�̍쐬�Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �L�[�{�[�h������
	if (!initializeKey()) {
		MessageBox(nullptr, TEXT("InputKey�̏������Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// �}�E�X������
	if (!initializeMouse()) {
		MessageBox(nullptr, TEXT("InputMouse�̏������Ɏ��s���܂����B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void Input::update()
{
	updateKey();
	updateMouse();
	updatePad();
}

//-------------------------------------------------------------------------------------------------
bool Input::initializeKey()
{
	HRESULT hr;

	// �f�o�C�X���쐬����
	hr = mInterface->CreateDevice(GUID_SysKeyboard, &mKeyDevice, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// �f�o�C�X�̃t�H�[�}�b�g��ݒ肷��
	hr = mKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		return false;
	}

	// �������[�h�̐ݒ������
	const auto hWnd = Window::getInst()->hWnd();
	hr = mKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		return false;
	}

	// �f�o�C�X�̎擾�J�n
	mKeyDevice->Acquire();

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Input::initializeMouse()
{
	HRESULT hr;

	// �f�o�C�X���쐬����
	hr = mInterface->CreateDevice(GUID_SysMouse, &mMouseDevice, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// �f�o�C�X�̃t�H�[�}�b�g��ݒ肷��
	hr = mMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		return false;
	}

	// �������[�h�̐ݒ������
	const auto hWnd = Window::getInst()->hWnd();
	hr = mMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		return false;
	}

	// �f�o�C�X�̎擾�J�n
	mMouseDevice->Acquire();

	return true;
}

//-------------------------------------------------------------------------------------------------
void Input::updateKey()
{
	HRESULT hr;

	// �X�V�O�ɍŐV�L�[�{�[�h����ۑ�����
	memcpy(mPrevKeyState, mKeyState, sizeof(mKeyState));

	// �L�[�{�[�h�̏�Ԃ��擾
	hr = mKeyDevice->GetDeviceState(KEY_NUM, &mKeyState);
	if (FAILED(hr)) {
		mKeyDevice->Acquire();
		mKeyDevice->GetDeviceState(KEY_NUM, &mKeyState);
	}
}

//-------------------------------------------------------------------------------------------------
void Input::updateMouse()
{
	HRESULT	hr;

	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	mPrevMouseState = mMouseState;

	// �}�E�X�̏�Ԃ��擾
	hr = mMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mMouseState);
	if (FAILED(hr)) {
		mMouseDevice->Acquire();
		mMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mMouseState);
	}

	// �}�E�X���W(�X�N���[�����W)���擾����
	POINT mousePos;
	GetCursorPos(&mousePos);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	const static auto hWnd = Window::getInst()->hWnd();
	ScreenToClient(hWnd, &mousePos);

	// �ϊ��������W��ۑ�
	mMousePos.x = (float)mousePos.x;
	mMousePos.y = (float)mousePos.y;

	// �O�t���[������̈ړ���
	mMouseVelocity.x = (float)mMouseState.lX;
	mMouseVelocity.y = (float)mMouseState.lY;

	// �}�E�X�̃z�C�[����
	mMouseWheel = (int)mMouseState.lZ;
}

//-------------------------------------------------------------------------------------------------
void Input::updatePad()
{
	// �X�V�O�ɍŐV�Q�[���p�b�h����ۑ�����
	mPrevXInputState = mXInputState;

	// �Q�[���p�b�h�̏�Ԃ��擾
	XInputGetState(0, &mXInputState);

	// �X�e�B�b�N�̃f�b�h�]�[�����̓��͂�0�Ɋۂ߂�
	if (mXInputState.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && mXInputState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		mXInputState.Gamepad.sThumbLX = 0;
	}
	if (mXInputState.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && mXInputState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		mXInputState.Gamepad.sThumbLY = 0;
	}
	if (mXInputState.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && mXInputState.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		mXInputState.Gamepad.sThumbRX = 0;
	}
	if (mXInputState.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && mXInputState.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		mXInputState.Gamepad.sThumbRY = 0;
	}

	// �X�e�B�b�N�����X�V����
	mXInputThumbL.x = (float)mXInputState.Gamepad.sThumbLX;
	mXInputThumbL.y = (float)mXInputState.Gamepad.sThumbLY;
	mXInputThumbR.x = (float)mXInputState.Gamepad.sThumbRX;
	mXInputThumbR.y = (float)mXInputState.Gamepad.sThumbRY;
}

//-------------------------------------------------------------------------------------------------
bool Input::getKey(const int& aCode) const
{
	if (mKeyState[aCode] & 0x80) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getKeyDown(const int& aCode) const
{
	if ((mKeyState[aCode] & 0x80) && !(mPrevKeyState[aCode] & 0x80)) {
		return true;
	}
	return false;
}


//-------------------------------------------------------------------------------------------------
bool Input::getKeyUp(const int& aCode) const
{
	if (!(mKeyState[aCode] & 0x80) && (mPrevKeyState[aCode] & 0x80)) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getMouseButton(const int& aCode) const
{
	if (mMouseState.rgbButtons[aCode] == 0x80) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getMouseButtonDown(const int& aCode) const
{
	if ((mMouseState.rgbButtons[aCode] & 0x80) && !(mPrevMouseState.rgbButtons[aCode] & 0x80)) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getMouseButtonUp(const int& aCode) const
{
	if (!(mMouseState.rgbButtons[aCode] & 0x80) && (mPrevMouseState.rgbButtons[aCode] & 0x80)) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
const Vector2& Input::getMousePos() const
{
	return mMousePos;
}

//-------------------------------------------------------------------------------------------------
const Vector2& Input::getMouseVelocity() const
{
	return mMouseVelocity;
}

//-------------------------------------------------------------------------------------------------
const int& Input::getMouseWheel() const
{
	return mMouseWheel;
}

//-------------------------------------------------------------------------------------------------
bool Input::getXInputButton(const int& aCode) const
{
	if (mXInputState.Gamepad.wButtons & aCode) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getXInputButtonDown(const int& aCode) const
{
	if ((mXInputState.Gamepad.wButtons & aCode) && !(mPrevXInputState.Gamepad.wButtons & aCode)) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getXInputButtonUp(const int& aCode) const
{
	if (!(mXInputState.Gamepad.wButtons & aCode) && (mPrevXInputState.Gamepad.wButtons & aCode)) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getXInputTrigger(const int& aLR) const
{
	switch (aLR) {
	case 0:
		if (mXInputState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			return true;
		}
		break;
	case 1:
		if (mXInputState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			return true;
		}
		break;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getXInputTriggerDown(const int& aLR) const
{
	switch (aLR) {
	case 0:
		if ((mXInputState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) &&
			!(mPrevXInputState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) {
			return true;
		}
		break;
	case 1:
		if ((mXInputState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) &&
			!(mPrevXInputState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) {
			return true;
		}
		break;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getXInputTriggerUp(const int& aLR) const
{
	switch (aLR) {
	case 0:
		if (!(mXInputState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) &&
			(mPrevXInputState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) {
			return true;
		}
		break;
	case 1:
		if (!(mXInputState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) &&
			(mPrevXInputState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) {
			return true;
		}
		break;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
const Vector2& Input::getXInputThumb(const int& aLR) const
{
	switch (aLR) {
	case 0:
		return mXInputThumbL;
		break;
	case 1:
		return mXInputThumbR;
		break;
	}
	return mXInputThumbL;
}

} // namespace
// EOF
