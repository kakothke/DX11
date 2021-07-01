#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto INPUT = Input::getInst();
const static auto FPS = Fps::getInst();

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
	
	INPUT->update();

	// 方向入力
	mAxes = 0;
	mAxes.x -= INPUT->getKey(DIK_LEFT);
	mAxes.x += INPUT->getKey(DIK_RIGHT);
	mAxes.y -= INPUT->getKey(DIK_DOWN);
	mAxes.y += INPUT->getKey(DIK_UP);
	mAxes.x -= INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_LEFT);
	mAxes.x += INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_RIGHT);
	mAxes.y -= INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_DOWN);
	mAxes.y += INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_UP);
	mAxes.x += Math::Clamp(INPUT->getXInputThumb(0).x, -1.0f, 1.0f);
	mAxes.y += Math::Clamp(INPUT->getXInputThumb(0).y, -1.0f, 1.0f);
	mAxes.x = Math::Clamp(mAxes.x, -1.0f, 1.0f);
	mAxes.y = Math::Clamp(mAxes.y, -1.0f, 1.0f);

	// 決定ボタン
	mState[(int)InputCode::OK] =
		INPUT->getKey(DIK_Z) || INPUT->getXInputButton(XINPUT_GAMEPAD_B);

	// キャンセルボタン
	mState[(int)InputCode::Cancel] =
		INPUT->getKey(DIK_X) || INPUT->getXInputButton(XINPUT_GAMEPAD_A);

	

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

//-------------------------------------------------------------------------------------------------

Vector2 InputManager:: getAxesRaw(float Speed)
{

	if (INPUT->getKey(DIK_LEFT)) {
		mAxesRaw.x -= (FPS->deltaTime() * Speed);
		Code = 0;
	}else 
		
	if (INPUT->getKey(DIK_RIGHT)) {
		mAxesRaw.x += (FPS->deltaTime() * Speed);
		Code = 1;
	}else 

	if (INPUT->getKey(DIK_UP)) {
		mAxesRaw.y += (FPS->deltaTime() * Speed);
		Code = 2;
	}else

	if (INPUT->getKey(DIK_DOWN)) {
		mAxesRaw.y -= (FPS->deltaTime() * Speed);
		Code = 3;
	}
	else {

		switch (Code)
		{
		case 0:
			if (mAxesRaw.x < 0) {
				mAxesRaw.x += (FPS->deltaTime() * Speed);
			}
			else {
				mAxesRaw.x = 0;
			}
			break;

		case 1:
			if (mAxesRaw.x > 0) {
				mAxesRaw.x -= (FPS->deltaTime() * Speed);
			}
			else {
				mAxesRaw.x = 0;
			}
			break;

		case 2:
			if (mAxesRaw.y > 0) {
				mAxesRaw.y -= (FPS->deltaTime() * Speed);
			}
			else {
				mAxesRaw.y = 0;
			}
			break;

		case 3:
			if (mAxesRaw.y < 0) {
				mAxesRaw.y += (FPS->deltaTime() * Speed);
			}
			else {
				mAxesRaw.y = 0;
			}
			break;

		default:
			break;
		}	
		//mAxesRaw = Vector2(0, 0);
	}

	if (mAxesRaw.x > 1.0f)mAxesRaw.x = 1.0f;
	if (mAxesRaw.x < -1.0f)mAxesRaw.x = -1.0f;
	if (mAxesRaw.y > 1.0f)mAxesRaw.y = 1.0f;
	if (mAxesRaw.y < -1.0f)mAxesRaw.y = -1.0f;

	

	return mAxesRaw;
}

} // namespace
// EOF
