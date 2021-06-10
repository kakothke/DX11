#include "TestObj.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TestObj::TestObj()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
TestObj::TestObj(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// ����������
void TestObj::initialize()
{
	mRenderer.setObjAndShaderData(
		ResourceFileName::OBJ.at(OBJList::Test),
		ResourceFileName::Shader.at(ShaderList::Standard)
	);
	mTransform.pos.y = -2;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestObj::update()
{
	mTransform.rot.y += 0.01f;
	mTransform.pos.z -= 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestObj::draw()
{
	mRenderer.render(mTransform.XMFLOAT3X3());
}

} // namespace
// EOF
