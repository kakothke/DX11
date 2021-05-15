#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <d3d9.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ��`
class Define
{
public:
    /// @name �E�B���h�E�ݒ�
    //@{
    /// �𑜓x��
    const static USHORT ResolutionWidth = 1280;
    /// �𑜓x�c
    const static USHORT ResolutionHeight = 720;
    /// �E�B���h�E��
    const static LPCTSTR WindowName;
    //@}

    /// @name DirectX�ݒ�
    //@{
    /// �E�B���h�E���[�h�ɂ��邩
    const static bool WindowModeFlag = true;
    /// ��ʃN���A�F
    const static float ClearColor[4];
    /// ����p
    const static float Zoom;
    //@}

    /// @name �Q�[���ݒ�
    //@{
    /// �Œ肷��fps
    const static byte Fps = 60;
    //@}

};

} // namespace
// EOF
