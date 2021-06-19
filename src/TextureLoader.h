#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <unordered_map>
#include <DirectXMath.h>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �e�N�X�`���[�ǂݍ��݃N���X
class TextureLoader : public Singleton<TextureLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	TextureLoader();
	~TextureLoader();
	//@}

	/// @name �V�F�[�_�[���쐬����
	//@{
	bool load(const LPCSTR aFileName);
	void release(const LPCSTR aFileName);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �e�N�X�`���[���擾����
	ID3D11ShaderResourceView* getTexture(const LPCSTR aFileName) const;
	/// �e�N�X�`���[�̃T�C�Y���擾����
	const DirectX::XMFLOAT2 getTextureSize(const LPCSTR aFileName) const;
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
