#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "GameCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "Player.h"
#include "ObstractManager.h"
#include "GameObjectManager.h"

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
	/// @name 列挙型
	//@{
	/// ゲーム状況
	enum class GameState
	{
		Intro,
		Game,
		Miss,
	};
	//@}

	/// @name シーン内ゲームオブジェクト
	//@{
	std::shared_ptr<GameCamera> mCamera;
	std::shared_ptr<Player> mPlayer;
	//@}

	/// @name プライベートメンバ変数
	//@{
	GameObjectManager mGameOBJManager;
	GameState mState;
	//@}

};

} // namespace
// EOF
