#include "TestObj.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "OBJFileName.h"
#include "ShaderFileName.h"

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
		OBJFileName::fileName(OBJList::TestObj),
		ShaderFileName::fileName(ShaderList::Standard)
	);
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
	mRenderer.render(mTransform);
}

} // namespace
// EOF
