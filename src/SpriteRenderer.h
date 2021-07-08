#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "Transform.h"
#include "Vector2.h"
#include "Color.h"
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
	void render(Transform aTransform);
	//@}

	/// @name �`��ݒ�
	//@{
	/// �e�N�X�`���[���Z�b�g����
	void setTexture(const LPCSTR aFileName);
	/// �V�F�[�_�[��ݒ肷��
	void setShader(const LPCSTR aFileName);
	/// �J���[��ݒ肷�� 
	void setColor(const Color& aColor);
	/// �`�挴�_��ݒ肷��
	void setPivot(float aX, float aY);
	/// �`��J�n�ʒu��ݒ肷��
	void setAnchor(float aX, float aY);
	/// UV��������ݒ肷��
	void setSplit(const UINT& aX, const UINT& aY);
	//@}

private:
	/// @name ��������
	//@{
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer();
	//@}

	/// @name �����\����
	//@{
	/// ���_�f�[�^
	struct VertexData
	{
		float pos[3];
		float uv[2];
		float nor[3];
	};
	//@}

	/// �v���C�x�[�g�����o�ϐ�
	//@{
	/// ���_�o�b�t�@�[
	ID3D11Buffer* mVertexBuffer;
	/// �e�N�X�`���[��
	LPCSTR mTextureName;
	/// �e�N�X�`���[�T�C�Y
	Vector2 mTextureSize;
	/// �V�F�[�_�[�f�[�^
	ShaderLoader::ShaderData* mShaderData;
	/// �J���[
	Color mColor;
	/// �`�挴�_
	Vector2 mPivot;
	/// �`��J�n�ʒu
	Vector2 mAnchor;
	/// UV������
	Vector2 mSplit;
	//@}

};

} // namespace
// EOF
