#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SystemMain::SystemMain()
{
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
bool SystemMain::initialize() const
{
	// ウィンドウ初期化
	if (!Window::getInst()->initialize()) {
		return false;
	}
	// Direct3D11初期化
	if (!Direct3D11::getInst()->initialize()) {
		return false;
	}

	// ウィンドウを表示
	ShowWindow(Window::getInst()->hWnd(), SW_SHOW);
	UpdateWindow(Window::getInst()->hWnd());

	return true;
}

//-------------------------------------------------------------------------------------------------
/// メッセージループ
void SystemMain::msgLoop()
{
	Game game;
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// OSからのメッセージをウィンドウプロシージャーに渡す
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// ゲームのメインループ
			if (!game.mainLoop()) {
				break;
			}
		}
	}
}

} // namespace
// EOF
