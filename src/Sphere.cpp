#include "Sphere.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "OBJFileName.h"
#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Sphere::Sphere()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
Sphere::Sphere(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// ����������
void Sphere::initialize()
{
	mRenderer.setObjAndShaderData(
		OBJFileName::fileName(OBJList::Sphere),
		ShaderFileName::fileName(ShaderList::Unlit)
	);
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Sphere::update()
{
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Sphere::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
