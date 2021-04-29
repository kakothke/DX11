#include "Window.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	: m_hWnd(nullptr)
	, m_hMutex(nullptr)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Window::~Window()
{
	// ウィンドウの破棄
	if (m_hWnd) {
		DestroyWindow(m_hWnd);
		UnregisterClass(Define::WindowName, GetModuleHandle(NULL));
	}
	// ミューテックスの開放
	if (m_hMutex) {
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
	}
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
bool Window::initialize()
{
	// 多重起動をチェックする
	if (!checkMultiple()) {
		// 既に起動されているアプリケーションを前面に表示して終了
		return false;
	}
	// ウィンドウを作成する
	if (!createWindow()) {
		MessageBox(nullptr, TEXT("ウィンドウの作成に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 作成したウィンドウハンドルを返す
const HWND Window::hWnd() const
{
	return m_hWnd;
}

//-------------------------------------------------------------------------------------------------
/// 多重起動をチェックする
bool Window::checkMultiple()
{
	m_hMutex = CreateMutex(nullptr, FALSE, Define::WindowName);
	DWORD theErr = GetLastError();
	if (theErr == ERROR_ALREADY_EXISTS) {
		// 既に起動されているウィンドウを取得
		HWND hWnd = FindWindow(Define::WindowName, nullptr);
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
bool Window::createWindow()
{
	// ウィンドウクラスを登録する
	if (!registerClass()) {
		return false;
	}

	// ウィンドウ作成
	m_hWnd =
		CreateWindow(
			Define::WindowName,
			Define::WindowName,
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
	if (!m_hWnd) {
		return false;
	}

	// ウィンドウのサイズを調整する
	resizeWindow();

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウクラスを登録する
bool Window::registerClass()
{
	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = Define::WindowName;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	// ウィンドウクラスを登録
	if (RegisterClassEx(&wc) == 0) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ウィンドウのサイズを調整する
void Window::resizeWindow()
{
	// 非クライアント領域を加算したウィンドウサイズを計算
	RECT wndRect, cltRect;
	GetWindowRect(m_hWnd, &wndRect);
	GetClientRect(m_hWnd, &cltRect);
	int resizeW = ((wndRect.right - wndRect.left) - (cltRect.right - cltRect.left)) + Define::WindowWidth;
	int resizeH = ((wndRect.bottom - wndRect.top) - (cltRect.bottom - cltRect.top)) + Define::WindowHeight;

	// 作成したウィンドウの位置とサイズを変更
	SetWindowPos(
		m_hWnd,
		nullptr,
		(GetSystemMetrics(SM_CXSCREEN) - resizeW) / 2, // モニターの中央に表示
		(GetSystemMetrics(SM_CYSCREEN) - resizeH) / 2, // モニターの中央に表示
		resizeW,
		resizeH,
		SWP_NOZORDER | SWP_NOOWNERZORDER
	);
}

} // namespace
// EOF
