#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
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
SpriteRenderer::~SpriteRenderer()
{
}

//-------------------------------------------------------------------------------------------------
bool SpriteRenderer::render(const DirectX::XMFLOAT3X3& aTransform)
{
	// �ǂݍ��݃`�F�b�N
	if (!mSpriteData || !mShaderData) {
		return false;
	}

	// Direct3D11�擾
	static auto d3d11 = Direct3D11::getInst();
	static auto context = d3d11->getContext();
	static auto constantBuf = d3d11->getConstantBuffer();

	// �v���~�e�B�u�̌`����w��
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �V�F�[�_�[�̎w��
	d3d11->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(SpriteVertex);
	UINT offsets = 0;

	// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
	context->IASetVertexBuffers(0, 1, &mSpriteData->vertexBuffer, &strides, &offsets);

	// �R���X�^���g�o�b�t�@���X�V
	constantBuf->updateColor(mColor, mColor);
	constantBuf->updateSprite(aTransform, mAnchor, mPivot, mSplit);

	// �e�N�X�`���[�Z�b�g
	static auto texture = TextureLoader::getInst();
	d3d11->setTexture(texture->getTexture(mSpriteData->fileName));

	// �`��
	context->Draw(4, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName)
{
	auto sprite = SpriteLoader::getInst()->getSpriteData(aSpriteFileName);
	mSpriteData = sprite;
	auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setColor(const DirectX::XMFLOAT4& aColor)
{
	mColor = aColor;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setPivot(const DirectX::XMFLOAT2& aPivot)
{
	mPivot = aPivot;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setAnchor(const DirectX::XMFLOAT2& aAnchor)
{
	mAnchor = aAnchor;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setSplit(const DirectX::XMINT2& aSplit)
{
	mSplit = aSplit;
}

} // namespace
// EOF
