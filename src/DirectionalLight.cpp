#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
DirectionalLight::DirectionalLight()
	: mColor(255, 244, 214, 255)
{
	mTransform.rot = Vector3(50, -30, 0);
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aRot ����
DirectionalLight::DirectionalLight(Vector3 aRot)
	: mColor(255, 244, 214, 255)
{
	mTransform.rot = aRot;
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aColor �J���[
DirectionalLight::DirectionalLight(Color aColor)
	: mColor(aColor)
{
	mTransform.rot = Vector3(50, -30, 0);
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aRot ����
/// @param aColor �J���[
DirectionalLight::DirectionalLight(Vector3 aRot, Color aColor)
	: mColor(aColor)
{
	mTransform.rot = aRot;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void DirectionalLight::update()
{
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void DirectionalLight::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�^���g�o�b�t�@���X�V����
void DirectionalLight::updateConstantBuffer()
{
	Vector3 rot = Vector3(-mTransform.rot.y, mTransform.rot.x, 0).Normalized();
	const static auto cBuf = Direct3D11::getInst()->getConstantBuffer();
	cBuf->updateDLight(rot.XMVECTOR(), mColor.XMFLOAT4());
}

} // namespace
// EOF
