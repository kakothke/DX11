#include "TestSky.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TestSky::TestSky()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
TestSky::TestSky(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// ����������
void TestSky::initialize()
{
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::SkyBox));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::SkyBox));
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestSky::update()
{
	mTransform.rot.y += 0.001f;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestSky::draw()
{
	mRenderer.render(mTransform.XMFLOAT3X3());
}

} // namespace
// EOF
