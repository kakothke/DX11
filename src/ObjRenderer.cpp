#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
OBJRenderer::OBJRenderer()
	: mD3D11(Direct3D11::getInst())
	, mTex(TextureLoader::getInst())
	, mOBJData()
	, mShaderData()
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
OBJRenderer::~OBJRenderer()
{
}

//-------------------------------------------------------------------------------------------------
/// �`��
/// @param aTransform �g�����X�t�H�[��
void OBJRenderer::render(const DirectX::XMFLOAT3X3& aTransform)
{
	// �ǂݍ��݃`�F�b�N
	if (!mOBJData || !mShaderData) {
		return;
	}

	// �v���~�e�B�u�̌`����w��
	mD3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �V�F�[�_�[�̎w��
	mD3D11->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJVertex);
	UINT offsets = 0;

	for (auto index : mOBJData->indexes) {
		// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
		mD3D11->getContext()->IASetVertexBuffers(0, 1, &mOBJData->vertexBuffer, &strides, &offsets);
		mD3D11->getContext()->IASetIndexBuffer(mOBJData->indexBuffers[cnt], DXGI_FORMAT_R32_UINT, 0);

		// �R���X�^���g�o�b�t�@���X�V
		mD3D11->getConstantBuffer()->setMatrixW(aTransform);
		mD3D11->getConstantBuffer()->updateMatrix();
		mD3D11->getConstantBuffer()->updateMaterial(mOBJData->materials[index.first]);

		if (!mOBJData->materials[index.first].textureFileName.empty()) {
			// �e�N�X�`���[�Z�b�g
			const char* texName = mOBJData->materials[index.first].textureFileName.c_str();
			mD3D11->setTexture(mTex->getTexture(texName));
		} else {
			mD3D11->setTexture(nullptr);
		}

		// �`��
		mD3D11->getContext()->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJ�ƃV�F�[�_�[��ݒ肷��
/// @param aOBJFileName OBJ�t�@�C���p�X
/// @param aShaderFileName �V�F�[�_�[�t�@�C���p�X
void OBJRenderer::setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName)
{
	auto obj = OBJLoader::getInst()->getOBJData(aOBJFileName);
	mOBJData = obj;
	auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

} // namespace
// EOF
