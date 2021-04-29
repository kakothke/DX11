#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <list>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// fpsを制御する
class Fps
{
public:
	/// @name コンストラクタ
	//@{
	Fps();
	~Fps();
	//@}

	/// 更新
	void update();
	/// 待つ
	void wait();
	/// 現在のfpsを描画する
	void draw() const;

private:
	/// name プライベートメンバ変数
	//@{
	float mFps;
	int mStartTime;
	int mCounter;
	//@}

};

} // namespace
// EOF
