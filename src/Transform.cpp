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
