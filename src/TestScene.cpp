#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestScene::TestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mTestSprite({ Vector3(-100,0,0),Vector3(),Vector3(0.2f) })
, mT2({ Vector3(100,0,0),Vector3(),Vector3(0.2f) })
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
TestScene::~TestScene()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
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
/// 描画
void TestScene::draw()
{
	mTestSky.draw();
	mTestObj.draw();
}

//-------------------------------------------------------------------------------------------------
/// 描画2D
void TestScene::draw2D()
{
	mTestSprite.draw();
	mT2.draw();
}

} // namespace
// EOF
