#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "TextureLoader.h"
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();
const static auto TEXTURE_LOADER = TextureLoader::getInst();
const static auto SHADER_LOADER = ShaderLoader::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SpriteRenderer::SpriteRenderer()
	: mVertexBuffer(nullptr)
	, mTextureName(nullptr)
	, mTextureSize(1)
	, mShaderData()
	, mColor()
	, mPivot()
	, mAnchor()
	, mSplit(1.0f, 1.0f)
	, mUVPos()
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
SpriteRenderer::~SpriteRenderer()
{
	if (mVertexBuffer) {
		mVertexBuffer->Release();
		mVertexBuffer = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
/// @param aTransform �g�����X�t�H�[��
void SpriteRenderer::render(Transform aTransform, const bool& a3DModeFlag)
{
	// �ǂݍ��݃`�F�b�N
	if (!mTextureName || !mShaderData || !mVertexBuffer) {
		return;
	}

	// �T�C�Y���e�N�X�`���[�̃T�C�Y�ɍ��킹��
	aTransform.scale.x *= mTextureSize.x;
	aTransform.scale.y *= mTextureSize.y;
	if (a3DModeFlag) {
		aTransform.scale /= 100.0f;
	}

	// �v���~�e�B�u�̌`����w��
	D3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �V�F�[�_�[�̎w��
	D3D11->setShader(mShaderData);

	UINT strides = sizeof(VertexData);
	UINT offsets = 0;

	// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
	D3D11->getContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &strides, &offsets);

	// �R���X�^���g�o�b�t�@���X�V
	D3D11->getConstantBuffer()->updateColor(mColor, mColor);
	D3D11->getConstantBuffer()->setSpriteSplit(mSplit);
	D3D11->getConstantBuffer()->setSpriteUVpos(mUVPos);
	if (a3DModeFlag) {
		D3D11->getConstantBuffer()->setMatrixW(aTransform);
		D3D11->getConstantBuffer()->updateMatrix();
	} else {
		D3D11->getConstantBuffer()->setSpriteMatrixW(aTransform, mPivot);
		D3D11->getConstantBuffer()->setSpriteMatrixP(mAnchor);
		D3D11->getConstantBuffer()->updateSprite();
	}

	// �e�N�X�`���[�Z�b�g	
	D3D11->setTexture(TEXTURE_LOADER->getTexture(mTextureName));

	// �`��
	D3D11->getContext()->Draw(8, 0);

}

//-------------------------------------------------------------------------------------------------
/// �e�N�X�`���[��ݒ肷��
/// @param aFileName �t�@�C���p�X
void SpriteRenderer::setTexture(const LPCSTR aFileName)
{
	mTextureName = aFileName;
	mTextureSize = TEXTURE_LOADER->getTextureSize(aFileName);

	// �e�N�X�`���[�擾�G���[
	if (mTextureSize == Vector2(0)) {
		mTextureName = nullptr;
		mTextureSize = Vector2(1);
		return;
	}

	// ���_�o�b�t�@���܂��쐬����Ă��Ȃ��ꍇ�쐬����
	if (!mVertexBuffer) {
		createVertexBuffer();
	}
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

	mPivot.x = (mTextureSize.x / 2) * -aX;
	mPivot.y = (mTextureSize.y / 2) * aY;
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

	mTextureSize.x /= aX;
	mTextureSize.y /= aY;
}

//-------------------------------------------------------------------------------------------------
/// UV�ʒu��ݒ肷��
void SpriteRenderer::setUVPos(const UINT& aX, const UINT& aY)
{
	mUVPos.x = (float)aX;
	mUVPos.y = (float)aY;
}

//-------------------------------------------------------------------------------------------------
/// ���_�o�b�t�@���쐬����
/// @return ���� ����(true)
bool SpriteRenderer::createVertexBuffer()
{
	// ���_�쐬
	VertexData vertexes[8] = {};
	Vector2 size = 0.5f;
	// ���_0
	vertexes[0].pos[0] = -size.x;
	vertexes[0].pos[1] = -size.y;
	vertexes[0].uv[0] = 0.0f;
	vertexes[0].uv[1] = 1.0f;
	vertexes[0].nor[2] = -1.0f;
	// ���_1
	vertexes[1].pos[0] = size.x;
	vertexes[1].pos[1] = -size.y;
	vertexes[1].uv[0] = 1.0f;
	vertexes[1].uv[1] = 1.0f;
	vertexes[1].nor[2] = -1.0f;
	// ���_2
	vertexes[2].pos[0] = -size.x;
	vertexes[2].pos[1] = size.y;
	vertexes[2].uv[0] = 0.0f;
	vertexes[2].uv[1] = 0.0f;
	vertexes[2].nor[2] = -1.0f;
	// ���_3
	vertexes[3].pos[0] = size.x;
	vertexes[3].pos[1] = size.y;
	vertexes[3].uv[0] = 1.0f;
	vertexes[3].uv[1] = 0.0f;
	vertexes[3].nor[2] = -1.0f;
	// ���_4
	vertexes[4].pos[0] = -size.x;
	vertexes[4].pos[1] = -size.y;
	vertexes[4].uv[0] = 0.0f;
	vertexes[4].uv[1] = 1.0f;
	vertexes[4].nor[2] = 1.0f;
	// ���_5
	vertexes[5].pos[0] = size.x;
	vertexes[5].pos[1] = -size.y;
	vertexes[5].uv[0] = 1.0f;
	vertexes[5].uv[1] = 1.0f;
	vertexes[5].nor[2] = 1.0f;
	// ���_6
	vertexes[6].pos[0] = -size.x;
	vertexes[6].pos[1] = size.y;
	vertexes[6].uv[0] = 0.0f;
	vertexes[6].uv[1] = 0.0f;
	vertexes[6].nor[2] = 1.0f;
	// ���_7
	vertexes[7].pos[0] = size.x;
	vertexes[7].pos[1] = size.y;
	vertexes[7].uv[0] = 1.0f;
	vertexes[7].uv[1] = 0.0f;
	vertexes[7].nor[2] = 1.0f;

	D3D11_BUFFER_DESC bufferDesc;
	{
		// �o�b�t�@�̃T�C�Y
		bufferDesc.ByteWidth = sizeof(VertexData) * 8;
		// �g�p���@
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		// BIND�ݒ�
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
		bufferDesc.CPUAccessFlags = 0;
		// ���\�[�X�I�v�V�����̃t���O
		bufferDesc.MiscFlags = 0;
		// �\���̂̃T�C�Y
		bufferDesc.StructureByteStride = 0;
	}

	// ���\�[�X���
	D3D11_SUBRESOURCE_DATA subResource;
	{
		// �o�b�t�@�̒��g�̐ݒ�
		subResource.pSysMem = &vertexes[0];
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemPitch = 0;
		// texture�f�[�^���g�p����ۂɎg�p���郁���o
		subResource.SysMemSlicePitch = 0;
	}

	// �o�b�t�@�쐬
	HRESULT hr;
	hr = D3D11->getDevice()->CreateBuffer(&bufferDesc, &subResource, &mVertexBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

} // namespace
// EOF
