#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "Transform.h"
#include "Vector2.h"
#include "Color.h"
#include "FontLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �t�H���g�`��
class FontRenderer
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	FontRenderer();
	~FontRenderer();
	//@}

	/// @name �`��
	//@{
	void draw(Transform aTransform);
	//@}

	/// @name �`��ݒ�
	//@{
	/// �������ݒ肷��
	void setString(const LPCTSTR aString);
	/// �V�F�[�_�[��ݒ肷��
	void setShader(const LPCSTR aFileName);
	/// �t�H���g��ύX����
	void setFont(const LPCTSTR aFontName);
	/// �J���[��ݒ肷�� 
	void setColor(const Color& aColor);
	/// �`�挴�_��ݒ肷��
	void setPivot(float aX, float aY);
	/// �`��J�n�ʒu��ݒ肷��
	void setAnchor(float aX, float aY);
	//@}

private:
	/// @name �����\����
	//@{
	/// ���_�f�[�^�\����
	struct VertexData
	{
		float pos[3];
		float uv[2];
		float nor[3];
	};

	/// �e�N�X�`���[�f�[�^
	struct TextureData
	{
		/// �e�N�X�`���[
		ID3D11ShaderResourceView* texture;
		/// ���_�o�b�t�@(Shader���M�p)
		ID3D11Buffer* vertexBuffer;
		/// �e�N�X�`���[�T�C�Y
		Vector2 texSize;
		/// ���̕`��ʒu
		float nextPos;
		/// ���s�ʒu
		float newLine;
		/// �`�悵�Ȃ��t���O
		bool hideFlag;
	};
	//@}

	/// @name ��������
	//@{
	/// �t�H���g���b�V�����쐬����
	bool cretaeFontMesh();
	/// �t�H���g�e�N�X�`���[���쐬����
	bool createFontTexture(const UINT& aCode, const int& aLineCount);
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer(const int& aLineCount, const int& aIndexNum);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �\������
	LPCTSTR mString;
	/// �t�H���g��
	LPCTSTR mFontName;
	/// �e�N�X�`���[
	std::vector<std::vector<TextureData>> mTextures;
	/// �V�F�[�_�[�f�[�^
	ShaderLoader::ShaderData* mShaderData;
	/// �J���[
	Color mColor;
	/// �`�挴�_
	Vector2 mPivot;
	/// �`��J�n�ʒu
	Vector2 mAnchor;
	/// �����ƕ����̊�

	//@}

};

} // namespace
// EOF
