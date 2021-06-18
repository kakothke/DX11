#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
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
	void render(const DirectX::XMFLOAT3X3& aTransform);
	//@}

	/// @name 描画設定
	//@{
	/// スプライトとシェーダーを設定する
	void setSpriteAndShaderData(
		const char* const aSpriteFileName,
		const char* const aShaderFileName);
	/// カラーを設定する 
	void setColor(DirectX::XMFLOAT4& aColor);
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
	SpriteData* mSpriteData;
	/// シェーダーデータ
	ShaderData* mShaderData;
	/// カラー
	DirectX::XMFLOAT4 mColor;
	/// 描画中心位置
	DirectX::XMFLOAT2 mPivot;
	/// 描画開始位置
	DirectX::XMFLOAT2 mAnchor;
	/// UV分割数
	DirectX::XMINT2 mSplit;
	//@}

};

} // namespace
// EOF
