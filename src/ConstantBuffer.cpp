#include "ConstantBuffer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
ConstantBuffer::ConstantBuffer()
	: mBufferMatrix(nullptr)
	, mBufferCamera(nullptr)
	, mBufferLight(nullptr)
	, mBufferMaterial(nullptr)
	, mData()
{
}

//-------------------------------------------------------------------------------------------------
ConstantBuffer::~ConstantBuffer()
{
	if (mBufferMatrix) {
		mBufferMatrix->Release();
		mBufferMatrix = nullptr;
	}
	if (mBufferCamera) {
		mBufferCamera->Release();
		mBufferCamera = nullptr;
	}
	if (mBufferLight) {
		mBufferLight->Release();
		mBufferLight = nullptr;
	}
	if (mBufferMaterial) {
		mBufferMaterial->Release();
		mBufferMaterial = nullptr;
	}
}

//-------------------------------------------------------------------------------------------------
bool ConstantBuffer::create()
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	bufferDesc.ByteWidth = sizeof(CB_MATRIX);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBufferMatrix))) {
		return false;
	}
	bufferDesc.ByteWidth = sizeof(CB_CAMERA);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBufferCamera))) {
		return false;
	}
	bufferDesc.ByteWidth = sizeof(CB_DLIGHT);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBufferLight))) {
		return false;
	}
	bufferDesc.ByteWidth = sizeof(CB_MATERIAL);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBufferMaterial))) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// World�}�g���N�X�ݒ�
void ConstantBuffer::setMatrixW(const Transform& aTransform)
{
	// ���[���h�}�g���N�X�ݒ�
	DirectX::XMMATRIX pos = DirectX::XMMatrixTranslation(aTransform.pos.x, aTransform.pos.y, aTransform.pos.z);
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(aTransform.rot.x, aTransform.rot.y, aTransform.rot.z);
	DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(aTransform.scale.x, aTransform.scale.y, aTransform.scale.z);
	DirectX::XMMATRIX worldMatrix = scale * rot * pos;

	XMStoreFloat4x4(&mData.MATRIX.W, XMMatrixTranspose(worldMatrix));
}

//-------------------------------------------------------------------------------------------------
/// View�}�g���N�X�ݒ�
void ConstantBuffer::setMatrixV(const Transform& aTransform)
{
	DirectX::XMVECTOR pos = { aTransform.pos.x, aTransform.pos.y, aTransform.pos.z, 0 };
	DirectX::XMVECTOR forcus = { aTransform.pos.x, aTransform.pos.y, aTransform.pos.z + 1, 0 };
	DirectX::XMVECTOR upVec = { 0, 1, 0, 0 };
	DirectX::XMMATRIX rot = DirectX::XMMatrixRotationRollPitchYaw(aTransform.rot.x, aTransform.rot.y, -aTransform.rot.z);
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(pos, forcus, upVec) * rot;

	XMStoreFloat4x4(&mData.MATRIX.V, XMMatrixTranspose(viewMatrix));
}

//-------------------------------------------------------------------------------------------------
/// Projection�}�g���N�X�ݒ�
void ConstantBuffer::setMatrixP(const float aFov, const float aNearZ, const float aFarZ)
{
	D3D11_VIEWPORT vp;
	UINT numVierports = 1;
	Direct3D11::getInst()->getContext()->RSGetViewports(&numVierports, &vp);
	DirectX::XMMATRIX projMatrix = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(aFov),
		(float)vp.Width / (float)vp.Height,
		aNearZ,
		aFarZ
	);

	XMStoreFloat4x4(&mData.MATRIX.P, XMMatrixTranspose(projMatrix));
}
//-------------------------------------------------------------------------------------------------
/// �}�g���N�X�R���X�^���g�o�b�t�@���X�V����
void ConstantBuffer::updateMatrix()
{
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBufferMatrix,
		0,
		NULL,
		&mData.MATRIX,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(0, 1, &mBufferMatrix);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(0, 1, &mBufferMatrix);
}

//-------------------------------------------------------------------------------------------------
/// �J�����R���X�^���g�o�b�t�@���X�V����
void ConstantBuffer::updateCamera(const Transform& aTransform)
{
	// �J�����ʒu
	DirectX::XMVECTOR pos = DirectX::XMVectorSet(
		aTransform.pos.x,
		aTransform.pos.y,
		aTransform.pos.z,
		0
	);
	XMStoreFloat4(&mData.CAMERA.POS, pos);
	// �J��������
	DirectX::XMVECTOR rot = DirectX::XMVectorSet(
		aTransform.rot.x,
		aTransform.rot.y,
		aTransform.rot.z,
		0
	);
	XMStoreFloat4(&mData.CAMERA.ROT, pos);

	// �X�V
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBufferCamera,
		0,
		NULL,
		&mData.CAMERA,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(1, 1, &mBufferCamera);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(1, 1, &mBufferCamera);
}

//-------------------------------------------------------------------------------------------------
/// ���C�g�R���X�^���g�o�b�t�@���X�V����
void ConstantBuffer::updateDirectionalLight(const Vector3& aRot, const DirectX::XMFLOAT4& aCol)
{
	// ���C�g����
	DirectX::XMVECTOR rot = DirectX::XMVector3Normalize(
		DirectX::XMVectorSet(
			aRot.x,
			aRot.y,
			aRot.z,
			0
		)
	);
	XMStoreFloat4(&mData.DLIGHT.ROT, rot);
	// ���C�g�J���[
	mData.DLIGHT.COL = aCol;

	// �X�V
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBufferLight,
		0,
		NULL,
		&mData.DLIGHT,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(2, 1, &mBufferLight);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(2, 1, &mBufferLight);
}

//-------------------------------------------------------------------------------------------------
/// �}�e���A���R���X�^���g�o�b�t�@���X�V����
void ConstantBuffer::updateMaterial(const OBJMaterial& aMaterial)
{	
	// �A���r�G���g
	mData.MATERIAL.A = DirectX::XMFLOAT4(
		aMaterial.ambient[0],
		aMaterial.ambient[1],
		aMaterial.ambient[2],
		1
	);

	// �f�B�t���[�Y
	mData.MATERIAL.D = DirectX::XMFLOAT4(
		aMaterial.diffuse[0],
		aMaterial.diffuse[1],
		aMaterial.diffuse[2],
		1
	);

	// �X�y�L�����[
	mData.MATERIAL.S = DirectX::XMFLOAT4(
		aMaterial.specular[0],
		aMaterial.specular[1],
		aMaterial.specular[2],
		1
	);

	// �X�V
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBufferMaterial,
		0,
		NULL,
		&mData.MATERIAL,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(3, 1, &mBufferMaterial);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(3, 1, &mBufferMaterial);
}

} // namespace
// EOF
