#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "SpriteLoader.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

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
	void setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName);
	/// カラーを設定する 
	void setColor(const DirectX::XMFLOAT4& aColor);
	/// 描画中心位置を設定する
	void setPivot(const DirectX::XMFLOAT2& aPivot);
	/// 描画開始位置を設定する
	void setAnchor(const DirectX::XMFLOAT2& aAnchor);
	/// UV分割数を設定する
	void setSplit(const DirectX::XMINT2& aSplit);
	//@}

private:
	/// プライベートメンバ変数
	//@{
	/// Direct3D11
	Direct3D11* mD3D11;
	/// TextureLoader
	TextureLoader* mTex;
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
