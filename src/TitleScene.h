
#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "GameObjectManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ゲームシーン
class TitleScene : public AbstractScene
{
public:
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	TitleScene(IChangeScene* aImpl);
	virtual ~TitleScene();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	GameObjectManager mGameOBJManager;
	float mSceneChangeWaitTimer;
	bool mStartFlag;
	//@}

};

} // namespace
// EOF
