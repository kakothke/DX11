#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// Windowの作成を行うクラス
class Window
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Window();
	~Window();
	//@}

	/// @name 初期化処理
	//@{
	bool initialize();
	//@}

	/// @name アクセサ
	//@{
	/// 作成したウィンドウハンドルを返す
	const HWND hWnd() const;
	//@}

private:
	/// @name 初期化関数
	//@{
	/// 多重起動をチェックする
	bool checkMultiple();
	/// ウィンドウを作成する
	bool createWindow();
	/// ウィンドウクラスを登録する
	bool registerClass();
	/// ウィンドウのサイズを調整する
	void resizeWindow();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// ウィンドウハンドル
	HWND mWindowHandle;
	/// ミューテックス
	HANDLE mMutex;
	//@}

};

} // namespace
// EOF
