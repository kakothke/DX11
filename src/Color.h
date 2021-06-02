#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
    /// XMFLOAT4�^�ɕϊ����Ēl��Ԃ�
    DirectX::XMFLOAT4 XMFLOAT4() const;
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

};

} // namespace
// EOF
