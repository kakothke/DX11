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
    Color(float RGBA);
    Color(float R, float G, float B, float A);
    //@}

    /// @name Color�쐬�֐�
    //@{
    /// 0~255�̒l��Color���쐬����
    static Color Color32(int R, int G, int B, int A);
    //@}

    /// @name �ϊ��֐�
    //@{
    /// XMFLOAT4�^�ɕϊ����ĕԂ�
    DirectX::XMFLOAT4 XMFLOAT4() const;
    //@}

    /// @ name ���Z�q�I�[�o�[���[�h
    //@{
    Color operator +(float aValue) const;
    Color operator -(float aValue) const;
    Color operator *(float aValue) const;
    Color operator /(float aValue) const;
    Color operator +(const Color& aColor) const;
    Color operator -(const Color& aColor) const;
    Color operator *(const Color& aColor) const;
    Color operator /(const Color& aColor) const;
    
    bool operator ==(const Color& aColor) const;
    bool operator !=(const Color& aColor) const;

    void operator =(float aValue);
    void operator +=(float aValue);
    void operator -=(float aValue);
    void operator *=(float aValue);
    void operator /=(float aValue);
    void operator +=(const Color& aColor);
    void operator -=(const Color& aColor);
    void operator *=(const Color& aColor);
    void operator /=(const Color& aColor);
    //@}

    /// @name �����o�ϐ�
    //@{
    float r;
    float g;
    float b;
    float a;
    //@}

    /// @name const static �����o�ϐ�
    //@{
    /// RGBA(0, 0, 0, 0)
    const static Color clear;
    /// ���F�BRGBA��(0, 0, 0, 1)
    const static Color black;
    /// ���F�BRGBA��(1, 1, 1, 1)
    const static Color white;
    /// �ԐF�BRGBA��(1, 0, 0, 1)
    const static Color red;
    /// �\���b�h�O���[���BRGBA��(0, 1, 0, 1)
    const static Color green;
    /// �F�BRGBA��(0, 0, 1, 1)
    const static Color blue;
    /// �V�A���BRGBA��(0, 1, 1, 1)
    const static Color cyan;
    /// �}�[���^�BRGBA��(1, 0, 1, 1)
    const static Color magenta;
    /// ���F�BRGBA��(1, 0.92, 0.016, 1)
    const static Color yellow;
    /// �D�F�BRGBA��(0.5, 0.5, 0.5, 1)
    const static Color gray;
    /// gray�ƈꏏ
    const static Color grey;
    //@}

};

} // namespace
// EOF
