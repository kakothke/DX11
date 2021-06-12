#include "Input.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
Input::Input()
	: mInterface(nullptr)
	, mKeyDevice(nullptr)
	, mMouseDevice(nullptr)
	, mMouseState()
	, mPrevMouseState()
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
		return false;
	}

	// デバイスを作成する
	hr = mInterface->CreateDevice(GUID_SysKeyboard, &mKeyDevice, NULL);
	if (FAILED(hr)) {
		return false;
	}
	hr = mInterface->CreateDevice(GUID_SysMouse, &mMouseDevice, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// デバイスのフォーマットを設定する
	hr = mKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		return false;
	}
	hr = mMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		return false;
	}

	// 協調モードの設定をする
	HWND hWnd = FindWindow(Define::WindowName, nullptr);
	hr = mKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		return false;
	}
	hr = mMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		return false;
	}

	// デバイスの取得開始
	hr = mKeyDevice->Acquire();
	if (FAILED(hr)) {
		return false;
	}
	hr = mMouseDevice->Acquire();
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void Input::update()
{
	updateKey();
	updateMouse();
}

//-------------------------------------------------------------------------------------------------
void Input::updateKey()
{
	HRESULT	hr;

	// 更新前に最新キーボード情報を保存する
	memcpy(mPrevKeyState, mKeyState, sizeof(mKeyState));

	// キーボードの状態を取得
	hr = mKeyDevice->GetDeviceState(KEY_NUM, &mKeyState);
	if (FAILED(hr)) {
		mKeyDevice->Acquire();
		return;
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
		return;
	}

	// マウス座標(スクリーン座標)を取得する
	POINT mousePos;
	GetCursorPos(&mousePos);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindow(Define::WindowName, nullptr), &mousePos);

	// 変換した座標を保存
	mMousePos.x = (float)mousePos.x;
	mMousePos.y = (float)mousePos.y;
}

//-------------------------------------------------------------------------------------------------
bool Input::getKey(DWORD aCord) const
{
	if (mKeyState[aCord] & 0x80) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getKeyDown(DWORD aCord) const
{
	if (mKeyState[aCord] & 0x80 && !(mPrevKeyState[aCord] & 0x80)) {
		return true;
	}
	return false;
}


//-------------------------------------------------------------------------------------------------
bool Input::getKeyUp(DWORD aCord) const
{
	if (!(mKeyState[aCord] & 0x80) && mPrevKeyState[aCord] & 0x80) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getMouseButton(MouseCord aCord) const
{
	if (mMouseState.rgbButtons[(int)aCord] == 0x80) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getMouseButtonDown(MouseCord aCord) const
{
	if (mMouseState.rgbButtons[(int)aCord] & 0x80 && !(mPrevMouseState.rgbButtons[(int)aCord] & 0x80)) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool Input::getMouseButtonUp(MouseCord aCord) const
{
	if (!(mMouseState.rgbButtons[(int)aCord] & 0x80) && mPrevMouseState.rgbButtons[(int)aCord] & 0x80) {
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
	return {
		(float)mMouseState.lX,
		(float)mMouseState.lY
	};
}

//-------------------------------------------------------------------------------------------------
const int& Input::getMouseWheel() const
{
	return (int)mMouseState.lZ;
}

} // namespace
// EOF
