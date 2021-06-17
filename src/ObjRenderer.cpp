#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
OBJRenderer::OBJRenderer()
	: mOBJData()
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

	// Direct3D11�擾
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto cBuf = d3D11->getConstantBuffer();

	// �v���~�e�B�u�̌`����w��
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �V�F�[�_�[�̎w��
	d3D11->setShader(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJVertex);
	UINT offsets = 0;

	for (auto index : mOBJData->indexes) {
		// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
		context->IASetVertexBuffers(0, 1, &mOBJData->vertexBuffer, &strides, &offsets);
		context->IASetIndexBuffer(mOBJData->indexBuffers[cnt], DXGI_FORMAT_R32_UINT, 0);

		// �R���X�^���g�o�b�t�@���X�V
		cBuf->setMatrixW(aTransform);
		cBuf->updateMatrix();
		cBuf->updateMaterial(mOBJData->materials[index.first]);

		if (!mOBJData->materials[index.first].textureFileName.empty()) {
			// �e�N�X�`���[�Z�b�g
			const char* texName = mOBJData->materials[index.first].textureFileName.c_str();
			const static auto tex = TextureLoader::getInst();
			d3D11->setTexture(tex->getTexture(texName));
		} else {
			d3D11->setTexture(nullptr);
		}

		// �`��
		context->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJ�ƃV�F�[�_�[��ݒ肷��
/// @param aOBJFileName OBJ�t�@�C���p�X
/// @param aShaderFileName �V�F�[�_�[�t�@�C���p�X
void OBJRenderer::setObjAndShaderData(const char* const aOBJFileName, const char* const aShaderFileName)
{
	const auto obj = OBJLoader::getInst()->getOBJData(aOBJFileName);
	mOBJData = obj;
	const auto shader = ShaderLoader::getInst()->getShaderData(aShaderFileName);
	mShaderData = shader;
}

} // namespace
// EOF
