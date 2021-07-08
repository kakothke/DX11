#include "DebugScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
DebugScene::DebugScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	mOBJTest.setOBJ(ResourceFileName::OBJ.at(OBJList::Cube));
	mOBJTest.setShader(ResourceFileName::Shader.at(ShaderList::Standard));

	mSpriteTest.setAnchor(1.0f, 1.0f);
	mSpriteTest.setPivot(1.0f, 1.0f);
	mSpriteTest.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mSpriteTest.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
DebugScene::~DebugScene()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void DebugScene::update()
{
	// ワールド関連
	mCamera.update();
	mDirectionalLight.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void DebugScene::draw()
{
	mOBJTest.render(Transform());
	mSpriteTest.render(Transform());
}

//-------------------------------------------------------------------------------------------------
/// 描画2D
void DebugScene::draw2D()
{
}

//-------------------------------------------------------------------------------------------------
/// 背景描画
void DebugScene::drawBackground()
{
	mSkyBox.draw();
}

} // namespace
// EOF
