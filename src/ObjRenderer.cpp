#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
OBJRenderer::OBJRenderer()
	: mOBJData()
	, mShaderData()
{
}

//-------------------------------------------------------------------------------------------------
OBJRenderer::~OBJRenderer()
{
}

//-------------------------------------------------------------------------------------------------
bool OBJRenderer::render(const DirectX::XMFLOAT3X3& aTransform)
{
	// �ǂݍ��݃`�F�b�N
	if (!mOBJData || !mShaderData) {
		return false;
	}

	// �v���~�e�B�u�̌`����w��
	Direct3D11::getInst()->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �V�F�[�_�[�̎w��
	Direct3D11::getInst()->setUpContext(mShaderData);

	int cnt = 0;
	UINT strides = sizeof(OBJVertex);
	UINT offsets = 0;

	for (auto index : mOBJData->indexes) {
		// IA�ɐݒ肷�钸�_�o�b�t�@�̎w��
		Direct3D11::getInst()->getContext()->IASetVertexBuffers(
			0,
			1,
			&mOBJData->vertexBuffer,
			&strides,
			&offsets
		);
		Direct3D11::getInst()->getContext()->IASetIndexBuffer(
			mOBJData->indexBuffers[cnt],
			DXGI_FORMAT_R32_UINT,
			0
		);

		// �R���X�^���g�o�b�t�@���X�V
		Direct3D11::getInst()->getConstantBuffer()->setMatrixW(aTransform);
		Direct3D11::getInst()->getConstantBuffer()->updateMatrix();
		Direct3D11::getInst()->getConstantBuffer()->updateMaterial(mOBJData->materials[index.first]);

		if (!mOBJData->materials[index.first].textureFileName.empty()) {
			// �e�N�X�`���[�Z�b�g
			const char* texName = mOBJData->materials[index.first].textureFileName.c_str();
			Direct3D11::getInst()->setTexture(Resource::getInst()->Texture()->getTexture(texName));
		} else {
			Direct3D11::getInst()->setTexture(nullptr);
		}

		// �`��
		Direct3D11::getInst()->getContext()->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void OBJRenderer::setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName)
{
	mOBJData = Resource::getInst()->OBJ()->getOBJData(aOBJFileName);
	mShaderData = Resource::getInst()->Shader()->getShaderData(aShaderFileName);
}

} // namespace
// EOF
