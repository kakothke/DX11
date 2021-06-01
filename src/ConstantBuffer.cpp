#include "ConstantBuffer.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
ConstantBuffer::ConstantBuffer()
	: mBuffer()
	, mData()
{
	mBuffer.clear();
}

//-------------------------------------------------------------------------------------------------
ConstantBuffer::~ConstantBuffer()
{
	for (auto buffer : mBuffer) {
		if (buffer.second) {
			buffer.second->Release();
			buffer.second = nullptr;
		}
	}
	mBuffer.clear();
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

	// �ϊ��s��
	bufferDesc.ByteWidth = sizeof(CB_MATRIX);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[MATRIX]))) {
		return false;
	}
	// �ϊ��s��2D
	bufferDesc.ByteWidth = sizeof(CB_SPRITE);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[SPRITE]))) {
		return false;
	}
	// �J�������
	bufferDesc.ByteWidth = sizeof(CB_CAMERA);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[CAMERA]))) {
		return false;
	}
	// �f�B���N�V���i�����C�g���
	bufferDesc.ByteWidth = sizeof(CB_DLIGHT);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[LIGHT]))) {
		return false;
	}
	// �}�e���A�����
	bufferDesc.ByteWidth = sizeof(CB_MATERIAL);
	if (FAILED(Direct3D11::getInst()->getDevice()->CreateBuffer(&bufferDesc, nullptr, &mBuffer[MATERIAL]))) {
		return false;
	}

	// �X�v���C�g�p�v���W�F�N�V�����s����Z�b�g
	float w = Define::ResolutionWidth;
	float h = Define::ResolutionHeight;
	DirectX::XMMATRIX proj2D = {
	h / w , 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
	};
	XMStoreFloat4x4(&mData.SPRITE.PROJ_2D, XMMatrixTranspose(proj2D));
	updateSprite();

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
		mBuffer[MATRIX],
		0,
		NULL,
		&mData.MATRIX,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(MATRIX, 1, &mBuffer[MATRIX]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(MATRIX, 1, &mBuffer[MATRIX]);
}

//-------------------------------------------------------------------------------------------------
void ConstantBuffer::updateSprite()
{
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBuffer[SPRITE],
		0,
		NULL,
		&mData.SPRITE,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(SPRITE, 1, &mBuffer[SPRITE]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(SPRITE, 1, &mBuffer[SPRITE]);
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
		mBuffer[CAMERA],
		0,
		NULL,
		&mData.CAMERA,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(CAMERA, 1, &mBuffer[CAMERA]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(CAMERA, 1, &mBuffer[CAMERA]);
}

//-------------------------------------------------------------------------------------------------
/// ���C�g�R���X�^���g�o�b�t�@���X�V����
void ConstantBuffer::updateDirectionalLight(const Vector3& aRot, const DirectX::XMFLOAT4& aCol)
{
	// ���C�g����
	DirectX::XMVECTOR rot = DirectX::XMVector3Normalize(
		DirectX::XMVectorSet(
			-aRot.y,
			aRot.x,
			0,
			0
		)
	);
	XMStoreFloat4(&mData.DLIGHT.ROT, rot);
	// ���C�g�J���[
	mData.DLIGHT.COL = aCol;

	// �X�V
	Direct3D11::getInst()->getContext()->UpdateSubresource(
		mBuffer[LIGHT],
		0,
		NULL,
		&mData.DLIGHT,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(LIGHT, 1, &mBuffer[LIGHT]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(LIGHT, 1, &mBuffer[LIGHT]);
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
		mBuffer[MATERIAL],
		0,
		NULL,
		&mData.MATERIAL,
		0,
		0
	);
	Direct3D11::getInst()->getContext()->VSSetConstantBuffers(MATERIAL, 1, &mBuffer[MATERIAL]);
	Direct3D11::getInst()->getContext()->PSSetConstantBuffers(MATERIAL, 1, &mBuffer[MATERIAL]);
}

} // namespace
// EOF
