#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �V�F�[�_���N���X
class BaseShader
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	BaseShader();
	virtual ~BaseShader();
	//@}

	/// @name �쐬�֐�
	//@{
	/// �V�F�[�_���쐬����
	virtual bool create(const char* aFileName) = 0;
	//@}

protected:
	/// @name �f�[�^�ǂݍ���
	//@{
	bool load(const char* aFileName);
	//@}

	/// @name �v���e�N�e�b�h�����o�ϐ�
	//@{
	/// �V�F�[�_�f�[�^(�o�C�i��)
	char* mData;
	/// �f�[�^�̃T�C�Y
	long mSize;
	//@}

};

} // namespace
// EOF
