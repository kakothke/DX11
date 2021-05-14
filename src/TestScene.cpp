#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include "ObjLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TestScene::TestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	// ���\�[�X�̓ǂݍ���
	ObjLoader::getInst()->load(ObjList::Cube);
	ObjLoader::getInst()->load(ObjList::Sphere);
	ShaderLoader::getInst()->load(ShaderList::UnlitShader);
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
TestScene::~TestScene()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestScene::update()
{
	mCamera.update();
	mCube.update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestScene::draw()
{
	mCube.draw();
}

} // namespace
// EOF
