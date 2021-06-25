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
void OBJRenderer::render(const Transform& aTransform)
{
	// �ǂݍ��݃`�F�b�N
	if (!mOBJData || !mShaderData) {
		return;
	}

	// Direct3D11�擾
	const static auto d3D11 = Direct3D11::getInst();
	const static auto context = d3D11->getContext();
	const static auto constantBuffer = d3D11->getConstantBuffer();

	// �v���~�e�B�u�̌`����w��
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �V�F�[�_�[�̎w��
	d3D11->setShader(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJLoader::OBJVertex);
	UINT offsets = 0;

	for (auto index : mOBJData->indexes) {
		// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
		context->IASetVertexBuffers(0, 1, &mOBJData->vertexBuffer, &strides, &offsets);
		context->IASetIndexBuffer(mOBJData->indexBuffers[cnt], DXGI_FORMAT_R32_UINT, 0);

		// �R���X�^���g�o�b�t�@���X�V
		constantBuffer->setMatrixW(aTransform);
		constantBuffer->updateMatrix();
		constantBuffer->updateMaterial(mOBJData->materials[index.first]);

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
/// OBJ��ݒ肷��
/// @param aFileName �t�@�C���p�X
void OBJRenderer::setOBJ(const LPCSTR aFileName)
{
	const auto obj = OBJLoader::getInst()->getOBJData(aFileName);
	mOBJData = obj;
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[��ݒ肷��
/// @param aFileName �t�@�C���p�X
void OBJRenderer::setShader(const LPCSTR aFileName)
{
	const auto shader = ShaderLoader::getInst()->getShaderData(aFileName);
	mShaderData = shader;
}

} // namespace
// EOF
