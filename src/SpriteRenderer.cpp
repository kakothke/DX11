#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SpriteRenderer::SpriteRenderer()
	: mSpriteData()
	, mShaderData()
	, mColor(1, 1, 1, 1)
	, mPivot(0.5f, 0.5f)
	, mAnchor(0, 0)
	, mSplit(1, 1)
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
void SpriteRenderer::render(const DirectX::XMFLOAT3X3& aTransform)
{
	// �ǂݍ��݃`�F�b�N
	if (!mSpriteData || !mShaderData) {
		return;
	}

	// Direct3D11�擾
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto cBuf = d3D11->getConstantBuffer();

	// �v���~�e�B�u�̌`����w��
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �V�F�[�_�[�̎w��
	d3D11->setShader(mShaderData);

	UINT strides = sizeof(SpriteVertex);
	UINT offsets = 0;

	// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
	context->IASetVertexBuffers(0, 1, &mSpriteData->vertexBuffer, &strides, &offsets);

	// �R���X�^���g�o�b�t�@���X�V
	cBuf->updateColor(mColor, mColor);
	cBuf->updateSprite(aTransform, mAnchor, mPivot, mSplit);

	// �e�N�X�`���[�Z�b�g
	const static auto tex = TextureLoader::getInst();
	d3D11->setTexture(tex->getTexture(mSpriteData->fileName));

	// �`��
	context->Draw(4, 0);
}

//-------------------------------------------------------------------------------------------------
/// �X�v���C�g�ƃV�F�[�_�[��ݒ肷��
/// @param aSpriteFileName �X�v���C�g�̃t�@�C���p�X
/// @param aShaderFileName �V�F�[�_�[�̃t�@�C���p�X
void SpriteRenderer::setSpriteAndShaderData(
	const char* const aSpriteFileName,
	const char* const aShaderFileName)
{
	const auto sprite = SpriteLoader::getInst()->getSpriteData(aSpriteFileName);
	mSpriteData = sprite;
	const auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

//-------------------------------------------------------------------------------------------------
/// �J���[��ݒ肷��
/// @param aColor �J���[(0~1)
void SpriteRenderer::setColor(DirectX::XMFLOAT4& aColor)
{
	aColor.x = Math::Clamp(aColor.x, -1.0f, 1.0f);
	aColor.y = Math::Clamp(aColor.y, -1.0f, 1.0f);
	aColor.z = Math::Clamp(aColor.z, -1.0f, 1.0f);
	aColor.w = Math::Clamp(aColor.w, -1.0f, 1.0f);

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

	const auto tex = TextureLoader::getInst();
	DirectX::XMFLOAT2 size = tex->getTextureSize(mSpriteData->fileName);

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
	mSplit.x = aX;
	mSplit.y = aY;
}

} // namespace
// EOF
