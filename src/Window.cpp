#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN:
		// キーを押した時
		switch ((char)wParam) {
		case VK_ESCAPE:
			// ESC
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		// 閉じるボタンをクリックした時
		PostQuitMessage(0);
		break;
	}
	// 上記以外のメッセージはWindowsへ処理を任せる
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Window::Window()
	: mHWnd(nullptr)
	, mMutex(nullptr)
	, mWindowName(TEXT("NULL"))
	, mIconName(nullptr)
	, mWindowWidth(0)
	, mWindowHeight(0)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Window::~Window()
{
	// ウィンドウの破棄
	if (mHWnd) {
		DestroyWindow(mHWnd);
		UnregisterClass(mWindowName, GetModuleHandle(NULL));
	}
	// ミューテックスの開放
	if (mMutex) {
		ReleaseMutex(mMutex);
		CloseHandle(mMutex);
	}
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
/// @param aWindowName ウィンドウ名
/// @param aWidth ウィンドウ横サイズ
/// @param aHeight ウィンドウ縦サイズ
/// @return 初期化結果 成功(true)
bool Window::initialize(const LPCTSTR aWindowName, const USHORT& aWidth, const USHORT& aHeight, const LPCTSTR aIconName)
{
	/// ウィンドウ名を保存
	mWindowName = aWindowName;
	/// アイコン名を保存
	mIconName = aIconName;

	// 多重起動をチェックする
	if (!checkMultiple()) {
		// 既に起動されているアプリケーションを前面に表示して終了
		return false;
	}
	// ウィンドウを作成する
	if (!createWindow(aWidth, aHeight)) {
		MessageBox(nullptr, TEXT("ウィンドウの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウのサイズを設定する
/// @param aWidth 縦サイズ
/// @param aHeight 横サイズ
/// @param aCenter 中央に表示
void Window::setSize(const USHORT& aWidth, const USHORT& aHeight, const bool& aCenter)
{
	// エラーチェック
	if (mWindowWidth == aWidth && mWindowHeight == aHeight || !mHWnd) {
		return;
	}

	// ウィンドウサイズを保存する
	mWindowWidth = aWidth;
	mWindowHeight = aHeight;

	// 非クライアント領域を加算したウィンドウサイズを計算
	RECT wndRect, cltRect;
	GetWindowRect(mHWnd, &wndRect);
	GetClientRect(mHWnd, &cltRect);
	int resizeW = ((wndRect.right - wndRect.left) - (cltRect.right - cltRect.left)) + mWindowWidth;
	int resizeH = ((wndRect.bottom - wndRect.top) - (cltRect.bottom - cltRect.top)) + mWindowHeight;

	int reposX = 0, reposY = 0;
	if (aCenter) {
		// モニターの中央に表示
		reposX = (GetSystemMetrics(SM_CXSCREEN) - resizeW) / 2;
		reposY = (GetSystemMetrics(SM_CYSCREEN) - resizeH) / 2;
	} else {
		// 現在のウィンドウの中心位置
		reposX = wndRect.left + mWindowWidth / 2;
		reposY = wndRect.top + mWindowHeight / 2;
	}

	// 作成したウィンドウの位置とサイズを変更
	SetWindowPos(
		mHWnd,
		nullptr,
		reposX,
		reposY,
		resizeW,
		resizeH,
		SWP_NOZORDER | SWP_NOOWNERZORDER
	);
}

//-------------------------------------------------------------------------------------------------
/// 作成したウィンドウハンドルを返す
const HWND Window::hWnd() const
{
	return mHWnd;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウ名を返す
const LPCTSTR Window::windowName() const
{
	return mWindowName;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウ横サイズを返す
const USHORT& Window::windowWidth() const
{
	return mWindowWidth;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウ縦サイズを返す
const USHORT& Window::windowHeight() const
{
	return mWindowHeight;
}

//-------------------------------------------------------------------------------------------------
/// 多重起動をチェックする
/// @return チェック結果 既に起動されているウィンドウが存在しない(true)
bool Window::checkMultiple()
{
	mMutex = CreateMutex(nullptr, FALSE, mWindowName);

	DWORD theErr = GetLastError();
	if (theErr == ERROR_ALREADY_EXISTS) {
		// 既に起動されているウィンドウを取得
		HWND hWnd = FindWindow(mWindowName, nullptr);
		if (IsIconic(hWnd)) {
			// 最小化されていれば元に戻す
			ShowWindowAsync(hWnd, SW_RESTORE);
		}
		// 前面表示する
		SetForegroundWindow(hWnd);

		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウを作成する
/// @return 作成結果 成功(true)
bool Window::createWindow(const USHORT& aWidth, const USHORT& aHeight)
{
	// ウィンドウクラスを登録する
	if (!registerClass()) {
		return false;
	}

	// ウィンドウ作成
	mHWnd =
		CreateWindow(
			mWindowName,
			mWindowName,
			// 最大化ボタンとサイズ変更を無効
			WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			GetModuleHandle(NULL),
			nullptr
		);

	// ウィンドウの作成に成功しているかをチェック
	if (!mHWnd) {
		return false;
	}

	// ウィンドウのサイズを調整する
	setSize(aWidth, aHeight);

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウクラスを登録する
/// @return 登録結果 成功(true)
bool Window::registerClass()
{
	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(wc.hInstance, mIconName);
	wc.hCursor = LoadCursor(wc.hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = mWindowName;
	wc.hIconSm = LoadIcon(wc.hInstance, mIconName);

	// ウィンドウクラスを登録
	if (RegisterClassEx(&wc) == 0) {
		return false;
	}

	return true;
}

} // namespace
// EOF
