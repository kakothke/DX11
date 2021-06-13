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

/// Inputクラス
class Input : public Singleton<Input>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Input();
	~Input();
	//@}

	/// @name 初期化/更新
	//@{
	bool initialize();
	void update();
	//@}

	/// @name キーボード情報
	//@{
	bool getKey(const int& aCord) const;
	bool getKeyDown(const int& aCord) const;
	bool getKeyUp(const int& aCord) const;
	//@}

	/// @マウス情報
	//@{
	bool getMouseButton(const int& aCord) const;
	bool getMouseButtonDown(const int& aCord) const;
	bool getMouseButtonUp(const int& aCord) const;
	const Vector2& getMousePos() const;
	const Vector2& getMouseVelocity() const;
	const int& getMouseWheel() const;
	//@}

	/// @ゲームパッド情報
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
	/// @name 内部実装関数
	//@{
	bool initializeKey();
	bool initializeMouse();
	
	void updateKey();
	void updateMouse();
	void updatePad();
	//@}

	/// @name 内部定数
	//@{
	/// キー総数
	const static int KEY_NUM = 256;
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// DirectInputのインターフェース
	LPDIRECTINPUT8 mInterface;
	/// DitectInputのデバイス（キーボード）
	LPDIRECTINPUTDEVICE8 mKeyDevice;
	/// DitectInputのデバイス（マウス）
	LPDIRECTINPUTDEVICE8 mMouseDevice;

	/// キーボードの入力状況
	BYTE mKeyState[KEY_NUM];
	/// キーボードの入力状況
	BYTE mPrevKeyState[KEY_NUM];

	/// マウスの入力状態
	DIMOUSESTATE mMouseState;
	/// 前フレームのマウスの入力状況
	DIMOUSESTATE mPrevMouseState;
	/// マウス座標
	Vector2 mMousePos;
	/// マウス座標の前フレームからの移動量
	Vector2 mMouseVelocity;
	/// マウスのホイール量
	int mMouseWheel;

	/// ゲームパッド（XInput）の入力状態
	XINPUT_STATE mXInputState;
	/// 前フレームのゲームパッド（XInput）の入力状況
	XINPUT_STATE mPrevXInputState;
	/// ゲームパッド（XInput）のスティックの入力状況
	Vector2 mXInputThumbL;
	Vector2 mXInputThumbR;
	//@}

};

} // namespcae
// EOF
