#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
const static Vector3 DEFINE_ANGLE = Vector3(50.0f, -30.0f, 0.0f);
const static Color DEFINE_COLOR = Color(1.0f, 0.9568627f, 0.8392157f, 1.0f);

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
DirectionalLight::DirectionalLight()
	: mAngle(DEFINE_ANGLE)
	, mColor(DEFINE_COLOR)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aAngle ���C�g�̌���
DirectionalLight::DirectionalLight(Vector3 aAngle)
	: mAngle(aAngle)
	, mColor(DEFINE_COLOR)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aColor �J���[
DirectionalLight::DirectionalLight(Color aColor)
	: mAngle(DEFINE_ANGLE)
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
/// �f�X�g���N�^
DirectionalLight::~DirectionalLight()
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
	D3D11->getConstantBuffer()->updateDLight(mAngle, mColor);
}

} // namespace
// EOF
