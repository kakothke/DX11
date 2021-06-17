#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "FontLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ���_�f�[�^�\����
struct FontVertex
{
	float pos[3] = {};
	float uv[2] = {};
};

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
		const DirectX::XMFLOAT3X3& aTransform = { 0,0,0,0,0,0,1,1,1 },
		const LPCTSTR aFontName = NULL);
	//@}

	/// @name �`��ݒ�
	//@{
	/// �V�F�[�_�[��ݒ肷��
	void setShaderData(const char* const aShaderFileName);
	/// �J���[��ݒ肷�� 
	void setColor(const DirectX::XMFLOAT4& aColor);
	/// �`�撆�S�ʒu��ݒ肷��
	void setPivot(const DirectX::XMFLOAT2& aPivot);
	/// �`��J�n�ʒu��ݒ肷��
	void setAnchor(const DirectX::XMFLOAT2& aAnchor);
	//@}

private:
	/// @name ��������
	//@{
	/// �r�b�g�}�b�v�쐬
	bool cretaeTexture();
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
	ShaderData* mShaderData;
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
