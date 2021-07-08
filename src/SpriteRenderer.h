#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "Transform.h"
#include "Vector2.h"
#include "Color.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// スプライト描画クラス
class SpriteRenderer
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	SpriteRenderer();
	~SpriteRenderer();
	//@}

	/// @name 描画
	//@{
	void render(Transform aTransform);
	//@}

	/// @name 描画設定
	//@{
	/// テクスチャーをセットする
	void setTexture(const LPCSTR aFileName);
	/// シェーダーを設定する
	void setShader(const LPCSTR aFileName);
	/// カラーを設定する 
	void setColor(const Color& aColor);
	/// 描画原点を設定する
	void setPivot(float aX, float aY);
	/// 描画開始位置を設定する
	void setAnchor(float aX, float aY);
	/// UV分割数を設定する
	void setSplit(const UINT& aX, const UINT& aY);
	//@}

private:
	/// @name 内部実装
	//@{
	/// 頂点バッファを作成する
	bool createVertexBuffer();
	//@}

	/// @name 内部構造体
	//@{
	/// 頂点データ
	struct VertexData
	{
		float pos[3];
		float uv[2];
		float nor[3];
	};
	//@}

	/// プライベートメンバ変数
	//@{
	/// 頂点バッファー
	ID3D11Buffer* mVertexBuffer;
	/// テクスチャー名
	LPCSTR mTextureName;
	/// テクスチャーサイズ
	Vector2 mTextureSize;
	/// シェーダーデータ
	ShaderLoader::ShaderData* mShaderData;
	/// カラー
	Color mColor;
	/// 描画原点
	Vector2 mPivot;
	/// 描画開始位置
	Vector2 mAnchor;
	/// UV分割数
	Vector2 mSplit;
	//@}

};

} // namespace
// EOF
