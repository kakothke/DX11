#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// Windowの作成を行うクラス
class Window : public Singleton<Window>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Window();
	~Window();
	//@}

	/// @name 初期化処理
	//@{
	bool initialize(const LPCTSTR aWindowName, const USHORT& aWidth, const USHORT& aHeight);
	//@}

	/// @name 制御関数
	//@{
	/// ウィンドウサイズを設定する
	void setSize(const USHORT& aWidth, const USHORT& aHeight, const bool& aCenter = true);
	//@}

	/// @name アクセサ
	//@{
	/// 作成したウィンドウハンドルを返す
	const HWND hWnd() const;
	/// ウィンドウ名を返す
	const LPCTSTR windowName() const;
	/// ウィンドウ横サイズを返す
	const USHORT& windowWidth() const;
	/// ウィンドウ縦サイズを返す
	const USHORT& windowHeight() const;
	//@}

private:
	/// @name 初期化関数
	//@{
	/// 多重起動をチェックする
	bool checkMultiple();
	/// ウィンドウを作成する
	bool createWindow(const USHORT& aWidth, const USHORT& aHeight);
	/// ウィンドウクラスを登録する
	bool registerClass();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// ウィンドウハンドル
	HWND mHWnd;
	/// ミューテックス
	HANDLE mMutex;
	/// ウィンドウ名
	LPCTSTR mWindowName;
	/// ウィンドウ横サイズ
	USHORT mWindowWidth;
	/// ウィンドウ縦サイズ
	USHORT mWindowHeight;
	//@}

};

} // namespace
// EOF
