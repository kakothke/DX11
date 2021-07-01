#pragma once

//-------------------------------------------------------------------------------------------------
#include "Input.h"
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 複数のデバイスの入力状況をまとめる列挙型
enum class InputCode
{
	/// 決定ボタン
	OK,
	/// キャンセルボタン
	Cancel,

	TERM,
};

/// 複数のデバイスの入力状況を管理する
class InputManager : public Singleton<InputManager>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	InputManager();
	~InputManager();
	//@}
	
	/// @name 更新
	//@{
	void update();
	//@}

	/// @name 入力状況取得
	//@{
	const Vector2& getAxes() const;
	bool getInput(const InputCode& aCode) const;
	bool getInputDown(const InputCode& aCode) const;
	bool getInputUp(const InputCode& aCode) const;

	Vector2 getAxesRaw(float Speed);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// 方向
	Vector2 mAxes;
	Vector2 mAxesRaw;
	/// 現在の入力状況
	bool mState[(int)InputCode::TERM];
	/// 前フレームの入力状況
	bool mPrevState[(int)InputCode::TERM];

	int Code;
	//@}

};

} // namespace
// EOF
