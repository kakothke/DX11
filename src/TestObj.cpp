#include "TestObj.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Test));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mTransform.pos.y = -2;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestObj::update()
{
	mTransform.rot.y += 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestObj::draw()
{
	mRenderer.render(mTransform.XMFLOAT3X3());
}

} // namespace
// EOF
