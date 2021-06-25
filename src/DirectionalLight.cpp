#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
DirectionalLight::DirectionalLight()
	: mEulerAngle(50, -30, 0)
	, mColor(255, 244, 214, 255)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aRot ����
DirectionalLight::DirectionalLight(Vector3 aAngle)
	: mEulerAngle(aAngle)
	, mColor(255, 244, 214, 255)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aColor �J���[
DirectionalLight::DirectionalLight(Color aColor)
	: mEulerAngle(50, -30, 0)
	, mColor(aColor)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aRot ����
/// @param aColor �J���[
DirectionalLight::DirectionalLight(Vector3 aAngle, Color aColor)
	: mEulerAngle(aAngle)
	, mColor(aColor)
{
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
	const static auto cBuf = Direct3D11::getInst()->getConstantBuffer();
	cBuf->updateDLight(mEulerAngle, mColor);
}

} // namespace
// EOF
