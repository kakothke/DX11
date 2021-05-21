#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "ConstantBuffer.h"

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
bool OBJRenderer::render(const Transform& aTransform)
{
	// �ǂݍ��݃`�F�b�N
	if (!mOBJData || !mShaderData) {
		return false;
	}

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
		ConstantBuffer::getInst()->setMatrixW(aTransform);
		ConstantBuffer::getInst()->updateMatrix();
		ConstantBuffer::getInst()->updateMaterial(mOBJData->materials[index.first]);

		// �`��
		Direct3D11::getInst()->getContext()->DrawIndexed((UINT)index.second.size(), 0, 0);

		cnt++;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void OBJRenderer::setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName)
{
	mOBJData = OBJLoader::getInst()->getObjData(aOBJFileName);
	mShaderData = ShaderLoader::getInst()->getShaderData(aShaderFileName);
}

} // namespace
// EOF
