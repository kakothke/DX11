#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <d3d9.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 定義
class Define
{
public:
    /// @name ウィンドウ設定
    //@{
    /// ウィンドウサイズ横
    const static USHORT WindowWidth = 1280;
    /// ウィンドウサイズ縦
    const static USHORT WindowHeight = 720;
    /// ウィンドウ名
    const static LPCTSTR WindowName;
    //@}

    /// @name DirectX設定
    //@{
    /// ウィンドウモードにするか
    const static bool WindowModeFlag = true;
    /// 画面クリア色
    const static float ClearColor[4];
    /// 視野角
    const static float Zoom;
    //@}

    /// @name ゲーム設定
    //@{
    /// 固定するfps
    const static byte Fps = 60;
    //@}

};

} // namespace
// EOF
