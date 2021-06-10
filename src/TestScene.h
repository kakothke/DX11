#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"
#include "Camera.h"
#include "TestObj.h"
#include "TestSprite.h"
#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

class TestScene : public AbstractScene
{
public:
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	TestScene(IChangeScene* aImpl);
	virtual ~TestScene();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	void draw2D() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	TestObj mTestObj;
	TestSprite mTestSprite, mT2;
	Camera mCamera;
	DirectionalLight mDirectionalLight;
	
	//@}

};

} // namespace
// EOF
