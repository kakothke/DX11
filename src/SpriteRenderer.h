#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "Transform.h"
#include "Vector2.h"
#include "Color.h"
#include "SpriteLoader.h"
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
	void render(const Transform& aTransform);
	//@}

	/// @name 描画設定
	//@{
	/// スプライトを設定する
	void setSprite(const LPCSTR aFileName);
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
	/// プライベートメンバ変数
	//@{
	/// スプライトデータ
	SpriteLoader::SpriteData* mSpriteData;
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
