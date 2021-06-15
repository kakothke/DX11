#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
InputManager::InputManager()
	: mState()
	, mPrevState()
{
}

//-------------------------------------------------------------------------------------------------
InputManager::~InputManager()
{
}

//-------------------------------------------------------------------------------------------------
void InputManager::update()
{
	// 更新前に最新の情報を保存
	for (int i = 0; i < (int)InputCode::TERM; i++) {
		memcpy(mPrevState, mState, sizeof(mState));
	}

	// 方向入力
	mAxes = 0;
	mAxes.x -= Input::getInst()->getKey(DIK_LEFT);
	mAxes.x += Input::getInst()->getKey(DIK_RIGHT);
	mAxes.y -= Input::getInst()->getKey(DIK_DOWN);
	mAxes.y += Input::getInst()->getKey(DIK_UP);
	mAxes.x -= Input::getInst()->getXInputButton(XINPUT_GAMEPAD_DPAD_LEFT);
	mAxes.x += Input::getInst()->getXInputButton(XINPUT_GAMEPAD_DPAD_RIGHT);
	mAxes.y -= Input::getInst()->getXInputButton(XINPUT_GAMEPAD_DPAD_DOWN);
	mAxes.y += Input::getInst()->getXInputButton(XINPUT_GAMEPAD_DPAD_UP);
	mAxes.x += Math::Clamp(Input::getInst()->getXInputThumb(0).x, -1.0f, 1.0f);
	mAxes.y += Math::Clamp(Input::getInst()->getXInputThumb(0).y, -1.0f, 1.0f);
	mAxes.x = Math::Clamp(mAxes.x, -1.0f, 1.0f);
	mAxes.y = Math::Clamp(mAxes.y, -1.0f, 1.0f);

	// 決定ボタン
	mState[(int)InputCode::OK] =
		Input::getInst()->getKey(DIK_Z) || Input::getInst()->getXInputButton(XINPUT_GAMEPAD_B);

	// キャンセルボタン
	mState[(int)InputCode::Cancel] =
		Input::getInst()->getKey(DIK_X) || Input::getInst()->getXInputButton(XINPUT_GAMEPAD_A);

}

//-------------------------------------------------------------------------------------------------
const Vector2& InputManager::getAxes() const
{
	return mAxes;
}

//-------------------------------------------------------------------------------------------------
bool InputManager::getInput(const InputCode& aCode) const
{
	if (mState[(int)aCode]) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool InputManager::getInputDown(const InputCode& aCode) const
{
	if (mState[(int)aCode] && !mPrevState[(int)aCode]) {
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
bool InputManager::getInputUp(const InputCode& aCode) const
{
	if (!mState[(int)aCode] && mPrevState[(int)aCode]) {
		return true;
	}
	return false;
}

} // namespace
// EOF
