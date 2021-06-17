#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SpriteRenderer::SpriteRenderer()
	: mD3D11(Direct3D11::getInst())
	, mTex(TextureLoader::getInst())
	, mSpriteData()
	, mShaderData()
	, mColor(1, 1, 1, 1)
	, mPivot(0.5f, 0.5f)
	, mAnchor(-1, -1)
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

	// �v���~�e�B�u�̌`����w��
	mD3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �V�F�[�_�[�̎w��
	mD3D11->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(SpriteVertex);
	UINT offsets = 0;

	// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
	mD3D11->getContext()->IASetVertexBuffers(0, 1, &mSpriteData->vertexBuffer, &strides, &offsets);

	// �R���X�^���g�o�b�t�@���X�V
	mD3D11->getConstantBuffer()->updateColor(mColor, mColor);
	mD3D11->getConstantBuffer()->updateSprite(aTransform, mAnchor, mPivot, mSplit);

	// �e�N�X�`���[�Z�b�g
	mD3D11->setTexture(mTex->getTexture(mSpriteData->fileName));

	// �`��
	mD3D11->getContext()->Draw(4, 0);
}

//-------------------------------------------------------------------------------------------------
/// �X�v���C�g�ƃV�F�[�_�[��ݒ肷��
/// @param aSpriteFileName �X�v���C�g�̃t�@�C���p�X
/// @param aShaderFileName �V�F�[�_�[�̃t�@�C���p�X
void SpriteRenderer::setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName)
{
	auto sprite = SpriteLoader::getInst()->getSpriteData(aSpriteFileName);
	mSpriteData = sprite;
	auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

//-------------------------------------------------------------------------------------------------
/// �J���[��ݒ肷��
/// @param aColor �F(0~1)
void SpriteRenderer::setColor(const DirectX::XMFLOAT4& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
/// �`�撆�S�ʒu��ݒ肷��
/// @param aPivot ���S�ʒu(x,y){0~1}
void SpriteRenderer::setPivot(const DirectX::XMFLOAT2& aPivot)
{
	mPivot = aPivot;
}

//-------------------------------------------------------------------------------------------------
/// �`��J�n�ʒu��ݒ肷��
/// @param aAnchor �J�n�ʒu(x,y){-1~1}
void SpriteRenderer::setAnchor(const DirectX::XMFLOAT2& aAnchor)
{
	mAnchor = aAnchor;
}

//-------------------------------------------------------------------------------------------------
/// UV��������ݒ肷��
/// @param aSplit ������(x,y)
void SpriteRenderer::setSplit(const DirectX::XMINT2& aSplit)
{
	mSplit = aSplit;
}

} // namespace
// EOF
