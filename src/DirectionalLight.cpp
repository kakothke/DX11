#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
static const Vector3 DEFAULT_ANGLE = Vector3(50.0f, -30.0f, 0.0f);
static const Color DEFAULT_COLOR = Color(1.0f, 0.9568627f, 0.8392157f, 1.0f);

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
DirectionalLight::DirectionalLight()
	: mAngle(DEFAULT_ANGLE)
	, mColor(DEFAULT_COLOR)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aAngle ���C�g�̌���
DirectionalLight::DirectionalLight(Vector3 aAngle)
	: mAngle(aAngle)
	, mColor(DEFAULT_COLOR)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aColor �J���[
DirectionalLight::DirectionalLight(Color aColor)
	: mAngle(DEFAULT_ANGLE)
	, mColor(aColor)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aAngle ���C�g�̌���
/// @param aColor �J���[
DirectionalLight::DirectionalLight(Vector3 aAngle, Color aColor)
	: mAngle(aAngle)
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
	cBuf->updateDLight(mAngle, mColor);
}

} // namespace
// EOF
