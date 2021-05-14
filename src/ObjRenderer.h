#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "ObjLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// .obj�t�@�C���`��N���X
class ObjRenderer
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ObjRenderer();
	~ObjRenderer();
	//@}

	void render(const Transform& aTransform);
	void setObjAndShaderData(const ObjList& aObjList, const ShaderList& aShaderList);

private:
	ObjData* mObjData;
	ShaderData* mShaderData;

};

} // namespace
// EOF
