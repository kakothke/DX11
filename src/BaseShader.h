#pragma once
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

	/// @name �A�N�Z�T
	//@{
	/// �V�F�[�_�̃f�[�^�i�o�C�i���j��Ԃ�
	const char* data() const;
	/// �V�F�[�_�̃f�[�^�T�C�Y��Ԃ�
	const long size() const;
	//@}

protected:
	/// @name �ǂݍ���
	//@{
	bool Load(const char* file_name);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�F�[�_�f�[�^(�o�C�i��)
	char* mData;
	/// �f�[�^�̃T�C�Y
	long mSize;
	//@}

};

} // namespace
// EOF
