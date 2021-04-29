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

} // namespace
// EOF
