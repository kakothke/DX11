#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Transform::Transform()
	: pos()
	, rot()
	, scale(1)
	, localPos()
	, localRot()
	, localScale(1)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aPos �ʒu
/// @param aRot ��]
/// @param aScale �傫��
Transform::Transform(Vector3 aPos, Vector3 aRot, Vector3 aScale)
	: pos(aPos)
	, rot(Quaternion::Euler(aRot))
	, scale(aScale)
	, localPos()
	, localRot()
	, localScale(1)
{
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�̉E�����̃x�N�g����Ԃ�
Vector3 Transform::Right() const
{
	return rot * Vector3(1, 0, 0);
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�̏�����̃x�N�g����Ԃ�
Vector3 Transform::Up() const
{
	return rot * Vector3(0, 1, 0);
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�̑O�����̃x�N�g����Ԃ�
Vector3 Transform::Forward() const
{
	return rot * Vector3(0, 0, 1);
}

//-------------------------------------------------------------------------------------------------
/// WorldMatrix�ɕϊ����ĕԂ�
DirectX::XMMATRIX Transform::WorldMatrix() const
{
	Vector3 tmpPos = pos + rot * localPos;
	DirectX::XMMATRIX position = DirectX::XMMatrixTranslation(
		tmpPos.x, tmpPos.y, tmpPos.z
	);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationQuaternion(
		(rot * localRot).XMVECTOR()
	);
	DirectX::XMMATRIX scaling = DirectX::XMMatrixScaling(
		scale.x * localScale.x, scale.y * localScale.y, scale.z * localScale.z
	);
	return scaling * rotation * position;
}

//-------------------------------------------------------------------------------------------------
/// @brief local�ϐ��͑�����Ȃ�
void Transform::operator =(const Transform& aTransform)
{
	pos = aTransform.pos;
	rot = aTransform.rot;
	scale = aTransform.scale;
}

} // namespace
// EOF
