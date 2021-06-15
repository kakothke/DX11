#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Resource.h"

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

	bool render(const DirectX::XMFLOAT3X3& aTransform);
	void setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName);
	void setColor(const DirectX::XMFLOAT4& aColor);
	void setPivot(const DirectX::XMFLOAT2& aPivot);
	void setAnchor(const DirectX::XMFLOAT2& aAnchor);
	void setSplit(const DirectX::XMINT2& aSplit);

private:
	SpriteData* mSpriteData;
	ShaderData* mShaderData;
	DirectX::XMFLOAT4 mColor;
	DirectX::XMFLOAT2 mPivot;
	DirectX::XMFLOAT2 mAnchor;
	DirectX::XMINT2 mSplit;

};

} // namespace
// EOF
