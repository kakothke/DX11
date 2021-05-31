#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "SpriteLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// スプライト描画クラス
class SpriteRenderer
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	SpriteRenderer();
	~SpriteRenderer();
	//@}

	bool render(const Transform& aTransform);
	void setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName);

private:
	SpriteData* mSpriteData;
	ShaderData* mShaderData;

};

} // namespace
// EOF
