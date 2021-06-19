#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
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
	void draw(
		const LPCTSTR aString,
		const DirectX::XMFLOAT3X3& aTransform = { 0,0,0,0,0,0,1,1,1 });
	//@}

	/// @name �`��ݒ�
	//@{
	/// �V�F�[�_�[��ݒ肷��
	void setShader(const LPCSTR aFileName);
	/// �t�H���g��ύX����
	void setFont(const LPCTSTR aFontName);
	/// �J���[��ݒ肷�� 
	void setColor(const DirectX::XMFLOAT4& aColor);
	/// �`�撆�S�ʒu��ݒ肷��
	void setPivot(const DirectX::XMFLOAT2& aPivot);
	/// �`��J�n�ʒu��ݒ肷��
	void setAnchor(const DirectX::XMFLOAT2& aAnchor);
	//@}

private:
	/// @name �����\����
	//@{
	/// ���_�f�[�^�\����
	struct FontVertex
	{
		float pos[3] = {};
		float uv[2] = {};
	};
	//@}

	/// @name ��������
	//@{
	/// �r�b�g�}�b�v�쐬
	bool cretaeTexture();
	bool createFontTexture(const UINT& aCode);
	bool createVertexBuffer();
	void createMesh(FontVertex* aVertexes);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �\������
	LPCTSTR mString;
	/// �t�H���g��
	LPCTSTR mFontName;
	/// ���_�o�b�t�@(Shader���M�p)
	ID3D11Buffer* mVertexBuffer;
	/// �e�N�X�`���[
	ID3D11ShaderResourceView* mTexture;
	/// �V�F�[�_�[�f�[�^
	ShaderLoader::ShaderData* mShaderData;
	/// �J���[
	DirectX::XMFLOAT4 mColor;
	/// �`�撆�S�ʒu
	DirectX::XMFLOAT2 mPivot;
	/// �`��J�n�ʒu
	DirectX::XMFLOAT2 mAnchor;
	//@}

};

} // namespace
// EOF
