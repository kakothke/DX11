#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
    /// �A�C�R����
    const static LPCTSTR IconName;
    //@}

    /// @name �Q�[���ݒ�
    //@{
    /// ��ʃN���A�F
    const static float ClearColor[4];
    //@}

    /// @name �Q�[���ݒ�
    //@{
    /// �Œ肷��fps
    const static byte Fps = 60;
    //@}

};

} // namespace
// EOF
