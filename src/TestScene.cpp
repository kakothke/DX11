#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestScene::TestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mTestObj({ Vector3(0,0,0),Vector3(),Vector3(1) })
, mTestSprite({ Vector3(100,100,0),Vector3(),Vector3(0.25f) })
, mT2({ Vector3(0,0,0),Vector3(),Vector3(0.5f) })
{
	mFont.setShaderData(ResourceFileName::Shader.at(ShaderList::Sprite));
	mFont.setFont(TEXT("あんずもじ湛"));
	// テストサウンド
	const auto sound = Sound::getInst();
	const auto resource = ResourceManager::getInst();
	sound->play(resource->BGMHandle(BGMList::Test));
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
	//mT2.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestScene::draw()
{
	mTestObj.draw();
}

//-------------------------------------------------------------------------------------------------
/// 描画2D
void TestScene::draw2D()
{
	mT2.draw();
	mTestSprite.draw();
}

//-------------------------------------------------------------------------------------------------
/// 背景描画
void TestScene::drawBackground()
{
	mTestSky.draw();
	mFont.draw(TEXT("宇宙"), { 0, -200, 0, 0, 0, 0, 1, 1, 1 });
}

} // namespace
// EOF
