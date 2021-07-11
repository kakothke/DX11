#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "Transform.h"
#include "Vector2.h"
#include "Color.h"
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
	void draw(Transform aTransform);
	//@}

	/// @name 描画設定
	//@{
	/// 文字列を設定する
	void setString(const LPCTSTR aString);
	/// シェーダーを設定する
	void setShader(const LPCSTR aFileName);
	/// フォントを変更する
	void setFont(const LPCTSTR aFontName);
	/// カラーを設定する 
	void setColor(const Color& aColor);
	/// 描画原点を設定する
	void setPivot(float aX, float aY);
	/// 描画開始位置を設定する
	void setAnchor(float aX, float aY);
	//@}

private:
	/// @name 内部構造体
	//@{
	/// 頂点データ構造体
	struct VertexData
	{
		float pos[3];
		float uv[2];
		float nor[3];
	};

	/// テクスチャーデータ
	struct TextureData
	{
		/// テクスチャー
		ID3D11ShaderResourceView* texture;
		/// 頂点バッファ(Shader送信用)
		ID3D11Buffer* vertexBuffer;
		/// テクスチャーサイズ
		Vector2 texSize;
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
	bool createVertexBuffer(const int& aLineCount, const int& aIndexNum);
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
	Color mColor;
	/// 描画原点
	Vector2 mPivot;
	/// 描画開始位置
	Vector2 mAnchor;
	/// 文字と文字の間

	//@}

};

} // namespace
// EOF
