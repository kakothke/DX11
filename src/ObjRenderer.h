#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "Transform.h"
#include "OBJLoader.h"
#include "ShaderLoader.h"
#include "Color.h"

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
	void render(const Transform& aTransform);
	//@}

	/// @name �`��ݒ�
	//@{
	/// OBJ��ݒ肷��
	void setOBJ(const LPCSTR aFileName);
	/// �V�F�[�_�[��ݒ肷��
	void setShader(const LPCSTR aFileName);
	/// �J���[��ݒ肷�� 
	void setColor(const Color& aColor);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// OBJ�f�[�^
	OBJLoader::OBJData* mOBJData;
	/// �V�F�[�_�[�f�[�^
	ShaderLoader::ShaderData* mShaderData;
	/// �J���[
	Color mColor;
	//@}

};

} // namespace
// EOF
