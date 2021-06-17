#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "FontLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 頂点データ構造体
struct FontVertex
{
	float pos[3] = {};
	float uv[2] = {};
};

class FontRenderer
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	FontRenderer();
	~FontRenderer();
	//@}

	/// @name 描画
	//@{
	void draw(
		const LPCTSTR aString,
		const DirectX::XMFLOAT3X3& aTransform = { 0,0,0,0,0,0,1,1,1 },
		const LPCTSTR aFontName = NULL);
	//@}

	/// @name 描画設定
	//@{
	/// シェーダーを設定する
	void setShaderData(const char* const aShaderFileName);
	/// カラーを設定する 
	void setColor(const DirectX::XMFLOAT4& aColor);
	/// 描画中心位置を設定する
	void setPivot(const DirectX::XMFLOAT2& aPivot);
	/// 描画開始位置を設定する
	void setAnchor(const DirectX::XMFLOAT2& aAnchor);
	//@}

private:
	/// @name 内部実装
	//@{
	/// ビットマップ作成
	bool cretaeTexture();
	bool createVertexBuffer();
	void createMesh(FontVertex* aVertexes);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// 表示文字
	LPCTSTR mString;
	/// フォント名
	LPCTSTR mFontName;
	/// 頂点バッファ(Shader送信用)
	ID3D11Buffer* mVertexBuffer;
	/// テクスチャー
	ID3D11ShaderResourceView* mTexture;
	/// シェーダーデータ
	ShaderData* mShaderData;
	/// カラー
	DirectX::XMFLOAT4 mColor;
	/// 描画中心位置
	DirectX::XMFLOAT2 mPivot;
	/// 描画開始位置
	DirectX::XMFLOAT2 mAnchor;
	//@}

};

} // namespace
// EOF
