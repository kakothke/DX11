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
	bool load(const LPCSTR aFileName);
	//@}

	/// @name �\����
	//@{
	/// �V�F�[�_�[�\����
	struct ShaderData
	{
		/// ���_�V�F�[�_�[
		ID3D11VertexShader* vs;
		/// �s�N�Z���V�F�[�_�[
		ID3D11PixelShader* ps;
		/// ���̓��C�A�E�g
		ID3D11InputLayout* inputLayout;
		/// �f�X�g���N�^
		~ShaderData();
	};
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �V�F�[�_�[�f�[�^���擾����
	ShaderData* getShaderData(const LPCSTR aFileName);
	//@}

private:
	/// @name ��������
	//@{
	/// ���_�V�F�[�_�[���쐬����
	bool createVertexShader(const LPCSTR aFileName);
	/// ���̓��C�A�E�g���쐬����
	bool createInputLayout(const LPCSTR aFileName);
	/// ���t���N�V��������DXGIFormat����������
	DXGI_FORMAT getDxgiFormat(D3D11_SIGNATURE_PARAMETER_DESC aParamDesc);
	/// �s�N�Z���V�F�[�_�[���쐬����
	bool createPixelShader(const LPCSTR aFileName);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�F�[�_�[�\����
	std::unordered_map<LPCSTR, ShaderData> mShaderData;
	//@}

};

} // namespace
// EOF
