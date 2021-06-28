#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	SOUND->play((int)SoundList::BGM_00);

	mSpriteTest.setAnchor(1.0f, 1.0f);
	mSpriteTest.setPivot(1.0f, 1.0f);
	mSpriteTest.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mSpriteTest.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));

	mFontTest.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mFontTest.setAnchor(-0.75f, -0.75f);
	mFontTest.setPivot(-1.0f, -1.0f);
	mFontTest.setFont(TEXT("あんずもじ湛"));
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
	// キャラクター
	mPlayer.setTargetPos(mBoss.transform().pos);
	mPlayer.update();
	mBoss.update();

	// ワールド関連
	mCamera.setPlayerTransform(mPlayer.transform());
	mCamera.setPlayerVelocity(mPlayer.moveVelocity());
	mCamera.update();
	mDirectionalLight.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameScene::draw()
{
	mPlayer.draw();
	mBoss.draw();
}

//-------------------------------------------------------------------------------------------------
/// 描画2D
void GameScene::draw2D()
{
	mSpriteTest.render(Transform());
	mFontTest.draw(TEXT("テスト"), Transform());
}

//-------------------------------------------------------------------------------------------------
/// 背景描画
void GameScene::drawBackground()
{
	mSkyBox.draw();
}

} // namespace
// EOF
