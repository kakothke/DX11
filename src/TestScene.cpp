#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestScene::TestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mSphere(Transform(Vector3(2, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1)))
, mTestObj(Transform(Vector3(-3, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1)))
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
	mCube.update();
	mSphere.update();
	mTestObj.update();
	mCamera.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestScene::draw()
{
	mCube.draw();
	mSphere.draw();
	mTestObj.draw();
}

} // namespace
// EOF
