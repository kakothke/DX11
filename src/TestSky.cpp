#include "TestSky.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	mRenderer.setObjAndShaderData(
		ResourceFileName::OBJ.at(OBJList::SkyDome),
		ResourceFileName::Shader.at(ShaderList::Standard)
	);
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
