#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "SpriteLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �X�v���C�g�`��N���X
class SpriteRenderer
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
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
