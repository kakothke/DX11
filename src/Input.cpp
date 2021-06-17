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

	// インターフェースを作成する
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mInterface, NULL);
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("DirectInputの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// キーボード初期化
	if (!initializeKey()) {
		MessageBox(nullptr, TEXT("InputKeyの初期化に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}
	// マウス初期化
	if (!initializeMouse()) {
		MessageBox(nullptr, TEXT("InputMouseの初期化に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
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

	// デバイスを作成する
	hr = mInterface->CreateDevice(GUID_SysKeyboard, &mKeyDevice, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// デバイスのフォーマットを設定する
	hr = mKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		return false;
	}

	// 協調モードの設定をする
	const auto hWnd = Window::getInst()->hWnd();
	hr = mKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		return false;
	}

	// デバイスの取得開始
	mKeyDevice->Acquire();

	return true;
}

//-------------------------------------------------------------------------------------------------
bool Input::initializeMouse()
{
	HRESULT hr;

	// デバイスを作成する
	hr = mInterface->CreateDevice(GUID_SysMouse, &mMouseDevice, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// デバイスのフォーマットを設定する
	hr = mMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		return false;
	}

	// 協調モードの設定をする
	const auto hWnd = Window::getInst()->hWnd();
	hr = mMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		return false;
	}

	// デバイスの取得開始
	mMouseDevice->Acquire();

	return true;
}

//-------------------------------------------------------------------------------------------------
void Input::updateKey()
{
	HRESULT hr;

	// 更新前に最新キーボード情報を保存する
	memcpy(mPrevKeyState, mKeyState, sizeof(mKeyState));

	// キーボードの状態を取得
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

	// 更新前に最新マウス情報を保存する
	mPrevMouseState = mMouseState;

	// マウスの状態を取得
	hr = mMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mMouseState);
	if (FAILED(hr)) {
		mMouseDevice->Acquire();
		mMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mMouseState);
	}

	// マウス座標(スクリーン座標)を取得する
	POINT mousePos;
	GetCursorPos(&mousePos);

	// スクリーン座標をクライアント座標に変換する
	const static auto hWnd = Window::getInst()->hWnd();
	ScreenToClient(hWnd, &mousePos);

	// 変換した座標を保存
	mMousePos.x = (float)mousePos.x;
	mMousePos.y = (float)mousePos.y;

	// 前フレームからの移動量
	mMouseVelocity.x = (float)mMouseState.lX;
	mMouseVelocity.y = (float)mMouseState.lY;

	// マウスのホイール量
	mMouseWheel = (int)mMouseState.lZ;
}

//-------------------------------------------------------------------------------------------------
void Input::updatePad()
{
	// 更新前に最新ゲームパッド情報を保存する
	mPrevXInputState = mXInputState;

	// ゲームパッドの状態を取得
	XInputGetState(0, &mXInputState);

	// スティックのデッドゾーン内の入力を0に丸める
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

	// スティック情報を更新する
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
