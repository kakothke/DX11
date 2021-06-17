#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <d3dcompiler.h>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "d3dcompiler.lib")

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
class ShaderLoader : public Singleton<ShaderLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ShaderLoader();
	~ShaderLoader();
	//@}

	/// @name �V�F�[�_�[��ǂݍ���
	//@{
	bool load(const char* const aFileName);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �V�F�[�_�[�f�[�^���擾����
	ShaderData* getShaderData(const char* const aFileName);
	//@}

private:
	/// @name ��������
	//@{
	/// ���_�V�F�[�_�[���쐬����
	bool createVertexShader(const char* const aFileName);
	/// ���̓��C�A�E�g���쐬����
	bool createInputLayout(const char* const aFileName);
	/// ���t���N�V��������DXGIFormat����������
	DXGI_FORMAT getDxgiFormat(D3D11_SIGNATURE_PARAMETER_DESC aParamDesc);
	/// �s�N�Z���V�F�[�_�[���쐬����
	bool createPixelShader(const char* const aFileName);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�F�[�_�[�\����
	std::unordered_map<const char*, ShaderData> mShaderData;
	//@}

};

} // namespace
// EOF
