#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <unordered_map>
#include "Singleton.h"
#include "VertexShader.h"
#include "PixelShader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �V�F�[�_�[�\����
struct ShaderData
{
	VertexShader vs;
	PixelShader ps;
};

/// �V�F�[�_�[�f�[�^�ǂݍ��݃N���X
class ShaderLoader : public Singleton<ShaderLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ShaderLoader();
	~ShaderLoader();
	//@}

	/// @name �V�F�[�_�[���쐬����
	//@{
	bool load(const char* aFileName);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �V�F�[�_�[�f�[�^���擾����
	ShaderData* getShaderData(const char* aFileName);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�F�[�_�[�\����
	std::unordered_map<const char*, ShaderData> mShaderData;
	//@}

};

} // namespace
// EOF
