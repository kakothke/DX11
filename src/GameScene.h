#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "GameObjectManager.h"
#include "Player.h"
#include "StageManager.h"
#include "GameUI.h"

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
	//@}

private:
	/// @name 内部実装
	//@{
	void missEvent();
	//@}

	/// @name プライベートメンバ変数
	//@{
	GameObjectManager mGameOBJManager;
	Player* mPlayer;
	StageManager* mStageManager;
	GameUI* mGameUI;
	float mRetryWaitTimer;
	bool mMissFlag;
	bool mRetryFlag;
	//@}

};

} // namespace
// EOF
