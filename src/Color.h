#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// カラー
class Color
{
public:
    /// @name コンストラクタ
    //@{
    Color();
    Color(int RGBA);
    Color(int R, int G, int B, int A);
    //@}

    /// @name 変換関数
    //@{
    /// XMFLOAT4型に変換して値を返す
    DirectX::XMFLOAT4 XMFLOAT4() const;
    //@}

    /// @ name 演算子オーバーロード
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

    /// @name メンバ変数
    //@{
    int r;
    int g;
    int b;
    int a;
    //@}

};

} // namespace
// EOF
