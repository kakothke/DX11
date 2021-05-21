#include "Cube.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "OBJFileName.h"
#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Cube::Cube()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
Cube::Cube(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// ����������
void Cube::initialize()
{
	mRenderer.setObjAndShaderData(
		OBJFileName::fileName(OBJList::Cube),
		ShaderFileName::fileName(ShaderList::Unlit)
	);
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Cube::update()
{
	mTransform.scale.y += 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Cube::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
