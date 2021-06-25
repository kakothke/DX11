#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �J���[
class Color
{
public:
    /// @name �R���X�g���N�^
    //@{
    Color();
    Color(int RGBA);
    Color(int R, int G, int B, int A);
    //@}

    /// @name �ϊ��֐�
    //@{
    /// 0~1�͈̔͂ɕϊ�����
    DirectX::XMFLOAT4 RGBA01() const;
    //@}

    /// @ name ���Z�q�I�[�o�[���[�h
    //@{
    Color operator +(int aValue) const;
    Color operator -(int aValue) const;
    Color operator *(int aValue) const;
    Color operator /(int aValue) const;
    Color operator +(const Color& aColor) const;
    Color operator -(const Color& aColor) const;
    Color operator *(const Color& aColor) const;
    Color operator /(const Color& aColor) const;
    
    bool operator ==(const Color& aColor) const;
    bool operator !=(const Color& aColor) const;

    void operator =(int aValue);
    void operator +=(int aValue);
    void operator -=(int aValue);
    void operator *=(int aValue);
    void operator /=(int aValue);
    void operator +=(const Color& aColor);
    void operator -=(const Color& aColor);
    void operator *=(const Color& aColor);
    void operator /=(const Color& aColor);
    //@}

    /// @name �����o�ϐ�
    //@{
    int r;
    int g;
    int b;
    int a;
    //@}

    /// @name const static �����o�ϐ�
    //@{
    /// RGBA(0, 0, 0, 0)
    const static Color clear;
    /// ���F�BRGBA��(0, 0, 0, 255)
    const static Color black;
    /// ���F�BRGBA��(255, 255, 255, 255)
    const static Color white;
    /// �ԐF�BRGBA��(255, 0, 0, 255)
    const static Color red;
    /// �\���b�h�O���[���BRGBA��(0, 255, 0, 255)
    const static Color green;
    /// �F�BRGBA��(0, 0, 255, 255)
    const static Color blue;
    /// �V�A���BRGBA��(0, 255, 255, 255)
    const static Color cyan;
    /// �}�[���^�BRGBA��(255, 0, 255, 255)
    const static Color magenta;
    /// ���F�BRGBA��(255, 235, 5, 255)
    const static Color yellow;
    /// �D�F�BRGBA��(128, 128, 128, 255)
    const static Color gray;
    /// gray�ƈꏏ
    const static Color grey;
    //@}

};

} // namespace
// EOF
