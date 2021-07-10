#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"
#include "Direct3D11.h"
#include "Input.h"
#include "Sound.h"
#include "Game.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto WINDOW = Window::getInst();
const static auto D3D11 = Direct3D11::getInst();
const static auto INPUT = Input::getInst();
const static auto SOUND = Sound::getInst();

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
	if (!WINDOW->initialize(Define::WindowName, Define::ResolutionWidth, Define::ResolutionHeight)) {
		return false;
	}
	// Direct3D11初期化	
	if (!D3D11->initialize()) {
		return false;
	}
	// Input初期化
	if (!INPUT->initialize()) {
		return false;
	}
	// Sound初期化
	if (!SOUND->initialize()) {
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
	ShowWindow(WINDOW->hWnd(), SW_SHOW);
	UpdateWindow(WINDOW->hWnd());

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
