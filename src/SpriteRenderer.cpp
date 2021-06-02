#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
SpriteRenderer::SpriteRenderer()
	: mSpriteData()
	, mShaderData()
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

	// �v���~�e�B�u�̌`����w��
	Direct3D11::getInst()->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �V�F�[�_�[�̎w��
	Direct3D11::getInst()->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(SpriteVertex);
	UINT offsets = 0;

	// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
	Direct3D11::getInst()->getContext()->IASetVertexBuffers(
		0,
		1,
		&mSpriteData->vertexBuffer,
		&strides,
		&offsets
	);

	// �R���X�^���g�o�b�t�@���X�V
	/*Direct3D11::getInst()->getConstantBuffer()->setMatrixW(aTransform.pos.XMFLOAT3(), aTransform.rot.XMFLOAT3(), aTransform.scale.XMFLOAT3());
	Direct3D11::getInst()->getConstantBuffer()->updateMatrix();*/

	// �e�N�X�`���[�Z�b�g
	Direct3D11::getInst()->setTexture(ResourceManager::getInst()->Texture()->getTexture(mSpriteData->fileName));

	// �`��
	Direct3D11::getInst()->getContext()->Draw(4, 0);

	return true;
}

//-------------------------------------------------------------------------------------------------
void SpriteRenderer::setSpriteAndShaderData(const char* aSpriteFileName, const char* aShaderFileName)
{
	mSpriteData = ResourceManager::getInst()->Sprite()->getSpriteData(aSpriteFileName);
	mShaderData = ResourceManager::getInst()->Shader()->getShaderData(aShaderFileName);
}

} // namespace
// EOF
