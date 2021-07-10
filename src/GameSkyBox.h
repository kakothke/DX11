#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// スカイボックス
class GameSkyBox : public BaseGameObject
{
public:
	/// name コンストラクタ
	//@{
	GameSkyBox();
	~GameSkyBox();
	//@}

	/// @name 初期化/更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	OBJRenderer mRenderer;
	//@}

};

} // namespace
// EOF
