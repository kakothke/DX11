#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Transform::Transform()
	: pos()
	, rot()
	, scale(1, 1, 1)
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
{
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�̉E�����̃x�N�g����Ԃ�
Vector3 Transform::Right()
{
	return rot * Vector3(1, 0, 0);
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�̏�����̃x�N�g����Ԃ�
Vector3 Transform::Up()
{
	return rot * Vector3(0, 1, 0);
}

//-------------------------------------------------------------------------------------------------
/// �I�u�W�F�N�g�̑O�����̃x�N�g����Ԃ�
Vector3 Transform::Forward()
{
	return rot * Vector3(0, 0, 1);
}

//-------------------------------------------------------------------------------------------------
/// WorldMatrix�ɕϊ����ĕԂ�
DirectX::XMMATRIX Transform::WorldMatrix() const
{
	DirectX::XMMATRIX position = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationQuaternion(rot.XMVECTOR());
	DirectX::XMMATRIX scaling = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	return scaling * rotation * position;
}

} // namespace
// EOF
