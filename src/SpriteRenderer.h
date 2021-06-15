#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Resource.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �X�v���C�g�`��N���X
class SpriteRenderer
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
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
