#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TestScene::TestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mTestSprite({ Vector3(-100,0,0),Vector3(),Vector3(0.2f) })
, mT2({ Vector3(100,0,0),Vector3(),Vector3(0.2f) })
{
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
	mDirectionalLight.update();
	mTestObj.update();
	mTestSky.update();
	mTestSprite.update();
	mT2.update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestScene::draw()
{
	mTestSky.draw();
	mTestObj.draw();
}

//-------------------------------------------------------------------------------------------------
/// �`��2D
void TestScene::draw2D()
{
	mTestSprite.draw();
	mT2.draw();
}

} // namespace
// EOF
