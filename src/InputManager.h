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
	/// 上
	UP,
	/// 下
	DOWN,

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
	/// 方向入力状況を返す(-1.0f~1.0f)
	const Vector2& axes() const;
	/// 方向入力状況を返す(-1~1)
	const Vector2& axesRaw() const;
	/// ボタンを押しているか
	bool getButton(const InputCode& aCode) const;
	/// ボタンを押したか
	bool getButtonDown(const InputCode& aCode) const;
	/// ボタンを離したか
	bool getButtonUp(const InputCode& aCode) const;
	//@}

private:
	/// @name 内部実装
	//@{
	/// 方向入力状況更新
	void updateAxes();
	/// ボタン入力状況更新
	void updateButtons();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// 方向(-1.0f~1.0f)
	Vector2 mAxes;
	/// 方向(-1~1)
	Vector2 mAxesRaw;
	/// 現在の入力状況
	bool mState[(int)InputCode::TERM];
	/// 前フレームの入力状況
	bool mPrevState[(int)InputCode::TERM];
	//@}

};

} // namespace
// EOF
