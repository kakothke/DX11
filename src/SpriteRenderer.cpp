#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
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

	// Direct3D11�擾
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto cBuf = d3D11->getConstantBuffer();

	// �v���~�e�B�u�̌`����w��
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �V�F�[�_�[�̎w��
	d3D11->setUpContext(mShaderData);

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
void SpriteRenderer::setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName)
{
	const auto sprite = SpriteLoader::getInst()->getSpriteData(aSpriteFileName);
	mSpriteData = sprite;
	const auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
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
