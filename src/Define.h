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
    /// �E�B���h�E�T�C�Y��
    const static USHORT WindowWidth = 1280;
    /// �E�B���h�E�T�C�Y�c
    const static USHORT WindowHeight = 720;
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
