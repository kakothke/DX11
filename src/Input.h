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

/// マウスの入力情報取得用構造体
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
	bool getKey(DWORD aCord) const;
	bool getKeyDown(DWORD aCord) const;
	bool getKeyUp(DWORD aCord) const;
	//@}

	/// @マウス情報
	//@{
	bool getMouseButton(MouseCord aCord) const;
	bool getMouseButtonDown(MouseCord aCord) const;
	bool getMouseButtonUp(MouseCord aCord) const;
	const Vector2& getMousePos() const;
	const Vector2& getMouseVelocity() const;
	const int& getMouseWheel() const;
	//@}

private:
	/// @name 内部実装関数
	//@{
	void updateKey();
	void updateMouse();
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

	/// キーボードの入力状態
	BYTE mKeyState[KEY_NUM];
	/// キーボードの入力状態
	BYTE mPrevKeyState[KEY_NUM];

	/// マウスの入力状態
	DIMOUSESTATE mMouseState;
	/// 前フレームのマウスの入力状態
	DIMOUSESTATE mPrevMouseState;
	/// マウス座標
	Vector2 mMousePos;
	//@}

};

} // namespcae
// EOF
