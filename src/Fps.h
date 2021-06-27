#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Singleton.h"

#pragma comment(lib,"winmm.lib")

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// fpsを制御する
class Fps : public Singleton<Fps>
{
public:
	/// @name コンストラクタ
	//@{
	Fps();
	~Fps();
	//@}

	/// @name 更新
	//@{
	void update();
	//@}

	/// @name 前フレームからかかった時間を返す
	//@{
	float deltaTime();
	//@}

	/// @name アクセサ
	//@{
	/// 現在のfps値を返す
	const float& fps();
	/// fpsの平均を取るサンプル数を設定する
	void setFpsCount(int aFpsCount);
	//@}

private:
	/// name プライベートメンバ変数
	//@{
	/// fps
	float mFps;
	/// 平均を取るサンプル数
	int mFpsCount;
	/// 測定開始時刻
	int mStartTime;
	/// カウンタ
	int mCounter;
	/// 処理待機時間
	int mWaitTime;
	//@}

};

} // namespace
// EOF
