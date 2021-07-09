#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	/*mOBJTest.setOBJ(ResourceFileName::OBJ.at(OBJList::Cube));
	mOBJTest.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mSpriteTest.setAnchor(1.0f, 1.0f);
	mSpriteTest.setPivot(1.0f, 1.0f);
	mSpriteTest.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mSpriteTest.setShader(ResourceFileName::Shader.at(ShaderList::Standard));*/
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
GameScene::~GameScene()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameScene::update()
{
	// ワールド関連
	mCamera.update();
	mDirectionalLight.update();

	// オブジェクト
	mPlayer.update();
	mObstractManager.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameScene::draw()
{
	mPlayer.draw();
	mObstractManager.draw();

	//mOBJTest.render(Transform());
	//mSpriteTest.render(Transform());
}

//-------------------------------------------------------------------------------------------------
/// 描画2D
void GameScene::draw2D()
{
}

//-------------------------------------------------------------------------------------------------
/// 背景描画
void GameScene::drawBackground()
{
	mSkyBox.draw();
}

} // namespace
// EOF
