#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
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

	/// @name プライベートメンバ変数
	//@{
	GameObjectManager mGameOBJManager;
	GameState mState;
	//@}

};

} // namespace
// EOF
