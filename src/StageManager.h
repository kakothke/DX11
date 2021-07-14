#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ステージマネージャー
class StageManager : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	StageManager();
	~StageManager();
	//@}
	
	/// @name 更新/描画
	//@{
	void update();
	void draw();
	//@}

	/// @name アクセサ
	//@{
	/// メートルを返す
	int getScore();
	/// ミスフラグを立てる
	void setMissFlagTrue();
	//@}

private:
	/// @name 内部実装
	//@{
	/// レベル更新
	void updateLevel();
	/// オブジェクトを生成する
	void instanceObj();
	/// スピード変更
	void changeSpeed();
	/// ミスイベント
	void missEvent();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// レベルアップタイマー
	float mLevelUpTimer;
	/// 障害物生成タイマー
	float mInstanceObstractTimer;
	/// 地上生成タイマー
	float mInstanceGroundTimer;
	/// 移動線エフェクト生成タイマー
	float mInstanceMoveLineEffectTimer;
	/// スコア
	float mScore;
	/// スピード
	float mMoveSpeed;
	/// レベル
	int mLevel;
	/// 障害物生成数
	int mInstanceObstractCount;
	/// ミスフラグ
	bool mMissFlag;
	//@}

};

} // namespace
// EOF
