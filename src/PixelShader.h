#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseShader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �s�N�Z���V�F�[�_�[
class PixelShader : public BaseShader
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	PixelShader();
	~PixelShader();
	//@}

	/// @name �V�F�[�_�[���쐬����
	//@{
	bool create(const char* aFileName) override;
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �C���^�[�t�F�[�X��Ԃ�
	ID3D11PixelShader* getInterface() const;
	//@}

protected:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �C���^�[�t�F�[�X
	ID3D11PixelShader* mInterface;
	//@}

};

} // namespace
// EOF
