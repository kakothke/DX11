#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();
const static auto OBJ_LOADER = OBJLoader::getInst();
const static auto TEXTURE_LOADER = TextureLoader::getInst();
const static auto SHADER_LOADER = ShaderLoader::getInst();

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

	// �v���~�e�B�u�̌`����w��
	D3D11->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �V�F�[�_�[�̎w��
	D3D11->setShader(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJLoader::OBJVertex);
	UINT offsets = 0;

	for (const auto index : mOBJData->indexes) {
		// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
		D3D11->getContext()->IASetVertexBuffers(0, 1, &mOBJData->vertexBuffer, &strides, &offsets);
		D3D11->getContext()->IASetIndexBuffer(mOBJData->indexBuffers[cnt], DXGI_FORMAT_R32_UINT, 0);

		// �R���X�^���g�o�b�t�@���X�V
		D3D11->getConstantBuffer()->setMatrixW(aTransform);
		D3D11->getConstantBuffer()->updateMatrix();
		D3D11->getConstantBuffer()->updateMaterial(mOBJData->materials[index.first]);

		if (!mOBJData->materials[index.first].textureFileName.empty()) {
			// �e�N�X�`���[�Z�b�g
			const char* texName = mOBJData->materials[index.first].textureFileName.c_str();			
			D3D11->setTexture(TEXTURE_LOADER->getTexture(texName));
		} else {
			D3D11->setTexture(nullptr);
		}

		// �`��
		D3D11->getContext()->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}
}

//-------------------------------------------------------------------------------------------------
/// OBJ��ݒ肷��
/// @param aFileName �t�@�C���p�X
void OBJRenderer::setOBJ(const LPCSTR aFileName)
{
	mOBJData = OBJ_LOADER->getOBJData(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// �V�F�[�_�[��ݒ肷��
/// @param aFileName �t�@�C���p�X
void OBJRenderer::setShader(const LPCSTR aFileName)
{
	mShaderData = SHADER_LOADER->getShaderData(aFileName);
}

} // namespace
// EOF
