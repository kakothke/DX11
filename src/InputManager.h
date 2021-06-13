#pragma once

//-------------------------------------------------------------------------------------------------
#include "Input.h"
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	InputManager();
	~InputManager();
	
	void update();

	const Vector2& getAxes() const;
	bool getInput(const InputCode& aCode) const;
	bool getInputDown(const InputCode& aCode) const;
	bool getInputUp(const InputCode& aCode) const;

private:
	Vector2 mAxes;
	bool mState[(int)InputCode::TERM];
	bool mPrevState[(int)InputCode::TERM];

};

} // namespace
// EOF
