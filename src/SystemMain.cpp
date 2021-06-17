#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"
#include "Direct3D11.h"
#include "Game.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SystemMain::SystemMain()
{
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
/// @return 初期化結果 成功(true)
bool SystemMain::initialize()
{
	// ウィンドウ初期化
	const auto window = Window::getInst();
	if (!window->initialize(Define::WindowName, Define::ResolutionWidth, Define::ResolutionHeight)) {
		return false;
	}
	// Direct3D11初期化
	const auto d3d11 = Direct3D11::getInst();
	if (!d3d11->initialize()) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// メッセージループ
void SystemMain::msgLoop()
{
	// ゲーム初期化
	Game game;
	if (!game.initialize()) {
		return;
	}

	// ウィンドウを表示
	{
		const auto hWnd = Window::getInst()->hWnd();
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}

	// メッセージループ
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
