#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include <memory>
#include "GameObjectManager.h"

//-------------------------------------------------------------------------------------------------
#include "BossCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "TestPlayer.h"
#include "Boss.h"
#include "FontRenderer.h"
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ボス戦テストシーン
class BossTestScene : public AbstractScene
{
public:
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	BossTestScene(IChangeScene* aImpl);
	virtual ~BossTestScene();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	GameObjectManager mGameObjMgr;
	BossCamera* mCamera;
	TestPlayer* mPlayer;
	Boss* mBoss;
	FontRenderer mFontTest;
	SpriteRenderer mSpriteTest;
	//@}

};

} // namespace
// EOF
