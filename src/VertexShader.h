#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseShader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ���_�V�F�[�_�[
class VertexShader : public BaseShader
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	VertexShader();
	~VertexShader();
	//@}

	/// @name ���_�V�F�[�_�[���쐬����
	//@{
	bool create(const char* aFileName) override;
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �C���^�[�t�F�[�X��Ԃ�
	const ID3D11VertexShader* shaderInterface() const;
	/// ���̓��C�A�E�g��Ԃ�
	const ID3D11InputLayout* inputLayout() const;
	//@}

private:
	/// @name ���̓��C�A�E�g���쐬����
	//@{
	bool createInputLayout();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �C���^�[�t�F�[�X
	ID3D11VertexShader* mInterface;
	/// ���̓��C�A�E�g
	ID3D11InputLayout* mInputLayout;
	//@}

};

} // namespace
// EOF
