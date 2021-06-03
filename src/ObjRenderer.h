#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Resource.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// .obj�t�@�C���`��N���X
class OBJRenderer
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	OBJRenderer();
	~OBJRenderer();
	//@}

	bool render(const DirectX::XMFLOAT3X3& aTransform);
	void setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName);

private:
	OBJData* mOBJData;
	ShaderData* mShaderData;

};

} // namespace
// EOF
