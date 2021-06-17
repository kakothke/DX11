#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "SpriteLoader.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �X�v���C�g�`��N���X
class SpriteRenderer
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	SpriteRenderer();
	~SpriteRenderer();
	//@}

	/// @name �`��
	//@{
	void render(const DirectX::XMFLOAT3X3& aTransform);
	//@}

	/// @name �`��ݒ�
	//@{
	/// �X�v���C�g�ƃV�F�[�_�[��ݒ肷��
	void setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName);
	/// �J���[��ݒ肷�� 
	void setColor(const DirectX::XMFLOAT4& aColor);
	/// �`�撆�S�ʒu��ݒ肷��
	void setPivot(const DirectX::XMFLOAT2& aPivot);
	/// �`��J�n�ʒu��ݒ肷��
	void setAnchor(const DirectX::XMFLOAT2& aAnchor);
	/// UV��������ݒ肷��
	void setSplit(const DirectX::XMINT2& aSplit);
	//@}

private:
	/// �v���C�x�[�g�����o�ϐ�
	//@{
	/// Direct3D11
	Direct3D11* mD3D11;
	/// TextureLoader
	TextureLoader* mTex;
	/// �X�v���C�g�f�[�^
	SpriteData* mSpriteData;
	/// �V�F�[�_�[�f�[�^
	ShaderData* mShaderData;
	/// �J���[
	DirectX::XMFLOAT4 mColor;
	/// �`�撆�S�ʒu
	DirectX::XMFLOAT2 mPivot;
	/// �`��J�n�ʒu
	DirectX::XMFLOAT2 mAnchor;
	/// UV������
	DirectX::XMINT2 mSplit;
	//@}

};

} // namespace
// EOF
