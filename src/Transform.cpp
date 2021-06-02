#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	, rot(aRot)
	, scale(aScale)
{
}

//-------------------------------------------------------------------------------------------------
/// XMFLOAT3X3�^�ɕϊ����ĕԂ�
DirectX::XMFLOAT3X3 Transform::XMFLOAT3X3() const
{
	return {
		pos.x, pos.y, pos.z,
		rot.x, rot.y, rot.z,
		scale.x, scale.y, scale.z
	};
}

} // namespace
// EOF
