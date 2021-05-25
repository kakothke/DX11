#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Game.h"
#include "OBJLoader.h"
#include "OBJFileName.h"
#include "ShaderLoader.h"
#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
SystemMain::SystemMain()
	: mWindow()
{
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
/// @return 初期化結果 成功(true)
bool SystemMain::initialize()
{
	// ウィンドウ初期化
	if (!mWindow.initialize()) {
		return false;
	}
	// Direct3D11初期化
	if (!Direct3D11::getInst()->initialize()) {
		return false;
	}

	// Singletonクラスを継承しているクラスの実体化
	OBJLoader::getInst();
	ShaderLoader::getInst();

	// リソースの読み込み
	OBJLoader::getInst()->load(OBJFileName::fileName(OBJList::Cube));
	OBJLoader::getInst()->load(OBJFileName::fileName(OBJList::Sphere));
	OBJLoader::getInst()->load(OBJFileName::fileName(OBJList::TestObj));
	ShaderLoader::getInst()->load(ShaderFileName::fileName(ShaderList::Unlit));
	ShaderLoader::getInst()->load(ShaderFileName::fileName(ShaderList::Standard));

	// ウィンドウを表示
	ShowWindow(mWindow.hWnd(), SW_SHOW);
	UpdateWindow(mWindow.hWnd());

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
