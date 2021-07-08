#include "BossTestScene.h"

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
BossTestScene::BossTestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	SOUND->play((int)SoundList::BGM_00);

	mSpriteTest.setAnchor(1.0f, 1.0f);
	mSpriteTest.setPivot(1.0f, 1.0f);
	mSpriteTest.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mSpriteTest.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));

	mFontTest.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mFontTest.setAnchor(-0.5f, -0.9f);
	mFontTest.setPivot(-1.0f, -1.0f);
	mFontTest.setFont(TEXT("あんずもじ湛"));
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
BossTestScene::~BossTestScene()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void BossTestScene::update()
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
void BossTestScene::draw()
{
	mPlayer.draw();
	mBoss.draw();
}

//-------------------------------------------------------------------------------------------------
/// 描画2D
void BossTestScene::draw2D()
{
	static Transform sptmp;
	sptmp.rot *= Quaternion::Euler(Vector3::up);
	mSpriteTest.render(sptmp);
	mFontTest.draw(TEXT("フォント 描画テスト"), Transform(Vector3(), Vector3(), Vector3(0.5f)));
}

//-------------------------------------------------------------------------------------------------
/// 背景描画
void BossTestScene::drawBackground()
{
	mSkyBox.draw();
}

} // namespace
// EOF
