#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <d3dcompiler.h>
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "d3dcompiler.lib")

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �V�F�[�_�[�\����
struct ShaderData
{
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;
	ID3D11InputLayout* inputLayout;
	~ShaderData()
	{
		if (vs) {
			vs->Release();
			vs = nullptr;
		}
		if (ps) {
			ps->Release();
			ps = nullptr;
		}
		if (inputLayout) {
			inputLayout->Release();
			inputLayout = nullptr;
		}
	}
};

/// �V�F�[�_�[�f�[�^�ǂݍ��݃N���X
class ShaderLoader
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ShaderLoader();
	~ShaderLoader();
	//@}

	/// @name �V�F�[�_�[���쐬����
	//@{
	bool load(const char* const aFileName);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �V�F�[�_�[�f�[�^���擾����
	ShaderData* getShaderData(const char* const aFileName);
	//@}

private:
	bool createVertexShader(const char* const aFileName);
	bool createInputLayout(const char* const aFileName);
	DXGI_FORMAT getDxgiFormat(D3D11_SIGNATURE_PARAMETER_DESC aParamDesc);
	bool createPixelShader(const char* const aFileName);

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�F�[�_�[�\����
	std::unordered_map<const char*, ShaderData> mShaderData;
	//@}

};

} // namespace
// EOF
