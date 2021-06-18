#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "SpriteLoader.h"
#include "ShaderLoader.h"

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
	void setSpriteAndShaderData(
		const char* const aSpriteFileName,
		const char* const aShaderFileName);
	/// �J���[��ݒ肷�� 
	void setColor(DirectX::XMFLOAT4& aColor);
	/// �`�挴�_��ݒ肷��
	void setPivot(float aX, float aY);
	/// �`��J�n�ʒu��ݒ肷��
	void setAnchor(float aX, float aY);
	/// UV��������ݒ肷��
	void setSplit(const UINT& aX, const UINT& aY);
	//@}

private:
	/// �v���C�x�[�g�����o�ϐ�
	//@{
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
