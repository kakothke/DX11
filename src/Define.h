#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 定義
class Define
{
public:
    /// @name ウィンドウ設定
    //@{
    /// 解像度横
    const static USHORT ResolutionWidth = 1280;
    /// 解像度縦
    const static USHORT ResolutionHeight = 720;
    /// ウィンドウ名
    const static LPCTSTR WindowName;
    /// アイコン名
    const static LPCTSTR IconName;
    //@}

    /// @name ゲーム設定
    //@{
    /// 画面クリア色
    const static float ClearColor[4];
    //@}

    /// @name ゲーム設定
    //@{
    /// 固定するfps
    const static byte Fps = 60;
    //@}

};

} // namespace
// EOF
