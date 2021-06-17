#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "OBJLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// .obj�t�@�C���`��N���X
class OBJRenderer
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	OBJRenderer();
	~OBJRenderer();
	//@}

	/// @name �`��
	//@{
	void render(const DirectX::XMFLOAT3X3& aTransform);
	//@}

	/// @name OBJ�ƃV�F�[�_�[��ݒ肷��
	//@{
	void setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// OBJ�f�[�^
	OBJData* mOBJData;
	/// �V�F�[�_�[�f�[�^
	ShaderData* mShaderData;
	//@}

};

} // namespace
// EOF
