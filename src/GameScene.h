#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "GameCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "Player.h"
#include "ObstractManager.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ゲームシーン
class GameScene : public AbstractScene
{
public:
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	GameScene(IChangeScene* aImpl);
	virtual ~GameScene();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	void draw2D() override;
	void drawBackground() override;
	//@}

private:
	/// @name シーン内ゲームオブジェクト
	//@{
	GameCamera mCamera;
	GameSkyBox mSkyBox;
	DirectionalLight mDirectionalLight;
	Player mPlayer;
	ObstractManager mObstractManager;

	OBJRenderer mOBJTest;
	SpriteRenderer mSpriteTest;
	//@}

};

} // namespace
// EOF
