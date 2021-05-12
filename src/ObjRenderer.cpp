#include "ObjRenderer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
ObjRenderer::ObjRenderer()
	: mObjData()
	, mShaderData()
{
}

//-------------------------------------------------------------------------------------------------
ObjRenderer::~ObjRenderer()
{
}

//-------------------------------------------------------------------------------------------------
void ObjRenderer::render(Transform aTransform)
{
	Direct3D11::getInst()->setUpContext(mObjData, mShaderData);

	// ���[���h�}�g���N�X�ݒ�
	DirectX::XMMATRIX worldMatrix;
	DirectX::XMMATRIX pos = DirectX::XMMatrixTranslation(aTransform.pos.x, aTransform.pos.y, aTransform.pos.z);
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(aTransform.rot.x, aTransform.rot.y, aTransform.rot.z);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(aTransform.scale.x, aTransform.scale.y, aTransform.scale.z);
	worldMatrix = scale * rot * pos;

	// ���[���h�}�g���N�X���R���X�^���g�o�b�t�@�ɐݒ�
	XMStoreFloat4x4(&Direct3D11::getInst()->getConstantBufferData()->World, XMMatrixTranspose(worldMatrix));

	// �R���X�^���g�o�b�t�@�X�V
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		Direct3D11::getInst()->getConstantBuffer(),
		0,
		NULL,
		Direct3D11::getInst()->getConstantBufferData(),
		0,
		0
	);

	ID3D11Buffer* constantBuffer = Direct3D11::getInst()->getConstantBuffer();
	// �R���e�L�X�g�ɃR���X�^���g�o�b�t�@��ݒ�
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(0, 1, &constantBuffer);

	// �`��
	Direct3D11::getInst()->getContext()->DrawIndexed(
		mObjData.indexes.size(),
		0,
		0
	);
}

//-------------------------------------------------------------------------------------------------
void ObjRenderer::setObjAndShaderData(ObjList aObjList, ShaderList aShaderList)
{
	mObjData = ObjLoader::getInst()->objData(aObjList);
	mShaderData = ShaderLoader::getInst()->shaderData(aShaderList);
}

} // namespace
// EOF
