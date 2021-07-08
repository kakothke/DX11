#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "Camera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "SpriteRenderer.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// デバッグシーン
class DebugScene : public AbstractScene
{
public:
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	DebugScene(IChangeScene* aImpl);
	virtual ~DebugScene();
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
	Camera mCamera;
	GameSkyBox mSkyBox;
	DirectionalLight mDirectionalLight;
	OBJRenderer mOBJTest;
	SpriteRenderer mSpriteTest;
	//@}

};

} // namespace
// EOF
