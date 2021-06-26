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
    Color(float RGBA);
    Color(float R, float G, float B, float A);
    //@}

    /// @name Color作成関数
    //@{
    /// 0~255の値でColorを作成する
    static Color Color32(int R, int G, int B, int A);
    //@}

    /// @name 変換関数
    //@{
    /// XMFLOAT4型に変換して返す
    DirectX::XMFLOAT4 XMFLOAT4() const;
    //@}

    /// @ name 演算子オーバーロード
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

    /// @name メンバ変数
    //@{
    float r;
    float g;
    float b;
    float a;
    //@}

    /// @name const static メンバ変数
    //@{
    /// RGBA(0, 0, 0, 0)
    const static Color clear;
    /// 黒色。RGBAは(0, 0, 0, 1)
    const static Color black;
    /// 白色。RGBAは(1, 1, 1, 1)
    const static Color white;
    /// 赤色。RGBAは(1, 0, 0, 1)
    const static Color red;
    /// ソリッドグリーン。RGBAは(0, 1, 0, 1)
    const static Color green;
    /// 青色。RGBAは(0, 0, 1, 1)
    const static Color blue;
    /// シアン。RGBAは(0, 1, 1, 1)
    const static Color cyan;
    /// マゼンタ。RGBAは(1, 0, 1, 1)
    const static Color magenta;
    /// 黄色。RGBAは(1, 0.92, 0.016, 1)
    const static Color yellow;
    /// 灰色。RGBAは(0.5, 0.5, 0.5, 1)
    const static Color gray;
    /// grayと一緒
    const static Color grey;
    //@}

};

} // namespace
// EOF
