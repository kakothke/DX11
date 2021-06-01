#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �e�N�X�`���[�ǂݍ��݃N���X
class TextureLoader
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	TextureLoader();
	~TextureLoader();
	//@}

	/// @name �V�F�[�_�[���쐬����
	//@{
	bool load(const char* const aFileName);
	void release(const char* const aFileName);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �e�N�X�`���[���擾����
	ID3D11ShaderResourceView* getTexture(const char* const aFileName);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �e�N�X�`���[
	std::unordered_map<std::string, ID3D11ShaderResourceView*> mTexture;
	//@}

};

} // namespace
// EOF
