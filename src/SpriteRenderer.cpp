#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();
const static auto TEXTURE_LOADER = TextureLoader::getInst();
const static auto SPRITE_LOADER = SpriteLoader::getInst();
const static auto SHADER_LOADER = ShaderLoader::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SpriteRenderer::SpriteRenderer()
	: mSpriteData()
	, mShaderData()
	, mColor()
	, mPivot(0.5f, 0.5f)
	, mAnchor(0.0f, 0.0f)
	, mSplit(1.0f, 1.0f)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
SpriteRenderer::~SpriteRenderer()
{
}

//-------------------------------------------------------------------------------------------------
/// �`��
/// @param aTransform �g�����X�t�H�[��
void SpriteRenderer::render(const Transform& aTransform)
{
	// �ǂݍ��݃`�F�b�N
	if (!mSpriteData || !mShaderData) {
		return;
	}

	// �v���~�e�B�u�̌`����w��
	D3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �V�F�[�_�[�̎w��
	D3D11->setShader(mShaderData);

	UINT strides = sizeof(SpriteLoader::SpriteVertex);
	UINT offsets = 0;

	// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
	D3D11->getContext()->IASetVertexBuffers(0, 1, &mSpriteData->vertexBuffer, &strides, &offsets);

	// �R���X�^���g�o�b�t�@���X�V
	D3D11->getConstantBuffer()->updateColor(mColor, mColor);
	D3D11->getConstantBuffer()->setSpriteSplit(mSplit);
	D3D11->getConstantBuffer()->setSpriteMatrixW(aTransform, mPivot);
	D3D11->getConstantBuffer()->updateSprite();

	// �e�N�X�`���[�Z�b�g	
	D3D11->setTexture(TEXTURE_LOADER->getTexture(mSpriteData->fileName));

	// �`��
	D3D11->getContext()->Draw(4, 0);
}

//-------------------------------------------------------------------------------------------------
/// �X�v���C�g��ݒ肷��
/// @param aFileName �t�@�C���p�X
void SpriteRenderer::setSprite(const LPCSTR aFileName)
{
	mSpriteData = SPRITE_LOADER->getSpriteData(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[��ݒ肷��
/// @param aFileName �t�@�C���p�X
void SpriteRenderer::setShader(const LPCSTR aFileName)
{
	mShaderData = SHADER_LOADER->getShaderData(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// �J���[��ݒ肷��
/// @param aColor �J���[
void SpriteRenderer::setColor(const Color& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
/// �`�挴�_��ݒ肷��
/// @param aX ���_x(-1~1)
/// @param aY ���_y(-1~1)
void SpriteRenderer::setPivot(float aX, float aY)
{
	aX = Math::Clamp(aX, -1.0f, 1.0f);
	aY = Math::Clamp(aY, -1.0f, 1.0f);

	DirectX::XMFLOAT2 size = TEXTURE_LOADER->getTextureSize(mSpriteData->fileName);

	mPivot.x = (size.x / 2) * -aX;
	mPivot.y = (size.y / 2) * aY;
}

//-------------------------------------------------------------------------------------------------
/// �`��J�n�ʒu��ݒ肷��
/// @param aX �`��J�n�ʒux(-1~1)
/// @param aY �`��J�n�ʒuy(-1~1)
void SpriteRenderer::setAnchor(float aX, float aY)
{
	aX = Math::Clamp(aX, -1.0f, 1.0f);
	aY = Math::Clamp(aY, -1.0f, 1.0f);

	mAnchor.x = aX;
	mAnchor.y = aY;
}

//-------------------------------------------------------------------------------------------------
/// UV��������ݒ肷��
/// @param aX ������x
/// @param aY ������y
void SpriteRenderer::setSplit(const UINT& aX, const UINT& aY)
{
	mSplit.x = (float)aX;
	mSplit.y = (float)aY;
}

} // namespace
// EOF
