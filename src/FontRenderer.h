#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "FontLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// フォント描画
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
		DirectX::XMFLOAT3X3 aTransform = { 0,0,0,0,0,0,1,1,1 });
	//@}

	/// @name 描画設定
	//@{
	/// シェーダーを設定する
	void setShader(const LPCSTR aFileName);
	/// フォントを変更する
	void setFont(const LPCTSTR aFontName);
	/// カラーを設定する 
	void setColor(DirectX::XMFLOAT4& aColor);
	/// 描画原点を設定する
	void setPivot(float aX, float aY);
	/// 描画開始位置を設定する
	void setAnchor(float aX, float aY);
	//@}

private:
	/// @name 内部構造体
	//@{
	/// 頂点データ構造体
	struct FontVertex
	{
		float pos[3] = {};
		float uv[2] = {};
	};
	/// テクスチャーデータ
	struct TextureData
	{
		/// テクスチャー
		ID3D11ShaderResourceView* texture;
		/// 頂点バッファ(Shader送信用)
		ID3D11Buffer* vertexBuffer;
		/// 次の描画位置
		float nextPos;
		/// 改行位置
		float newLine;
		/// 描画しないフラグ
		bool hideFlag;
	};
	//@}

	/// @name 内部実装
	//@{
	/// フォントメッシュを作成する
	bool cretaeFontMesh();
	/// フォントテクスチャーを作成する
	bool createFontTexture(const UINT& aCode, const int& aLineCount);
	/// 頂点バッファを作成する
	bool createVertexBuffer(const int& aIndexNum, const int& aLineCount);
	/// メッシュを作成する
	void createMesh(FontVertex* aVertexes, const int& aIndexNum, const int& aLineCount);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// 表示文字
	LPCTSTR mString;
	/// フォント名
	LPCTSTR mFontName;
	/// テクスチャー
	std::vector<std::vector<TextureData>> mTextures;
	/// シェーダーデータ
	ShaderLoader::ShaderData* mShaderData;
	/// カラー
	DirectX::XMFLOAT4 mColor;
	/// 描画原点
	DirectX::XMFLOAT2 mPivot;
	/// 描画開始位置
	DirectX::XMFLOAT2 mAnchor;
	/// 文字と文字の間

	//@}

};

} // namespace
// EOF
