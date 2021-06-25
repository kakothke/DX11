#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
    /// 0~1の範囲に変換する
    DirectX::XMFLOAT4 RGBA01() const;
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

    /// @name const static メンバ変数
    //@{
    /// RGBA(0, 0, 0, 0)
    const static Color clear;
    /// 黒色。RGBAは(0, 0, 0, 255)
    const static Color black;
    /// 白色。RGBAは(255, 255, 255, 255)
    const static Color white;
    /// 赤色。RGBAは(255, 0, 0, 255)
    const static Color red;
    /// ソリッドグリーン。RGBAは(0, 255, 0, 255)
    const static Color green;
    /// 青色。RGBAは(0, 0, 255, 255)
    const static Color blue;
    /// シアン。RGBAは(0, 255, 255, 255)
    const static Color cyan;
    /// マゼンタ。RGBAは(255, 0, 255, 255)
    const static Color magenta;
    /// 黄色。RGBAは(255, 235, 5, 255)
    const static Color yellow;
    /// 灰色。RGBAは(128, 128, 128, 255)
    const static Color gray;
    /// grayと一緒
    const static Color grey;
    //@}

};

} // namespace
// EOF
