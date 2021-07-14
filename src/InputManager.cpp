#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static float DEFINE_AXIS_SPEED = 10.0f;

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto INPUT = Input::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
InputManager::InputManager()
	: mState()
	, mPrevState()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
InputManager::~InputManager()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void InputManager::update()
{
	// 更新前に最新の情報を保存
	INPUT->update();
	for (int i = 0; i < (int)InputCode::TERM; i++) {
		memcpy(mPrevState, mState, sizeof(mState));
	}

	// 方向入力
	updateAxes();
	// ボタン操作
	updateButtons();
}

//-------------------------------------------------------------------------------------------------
/// 方向入力状況を返す(-1.0f~1.0f)
/// @return 方向入力状況
const Vector2& InputManager::axes() const
{
	return mAxes;
}

//-------------------------------------------------------------------------------------------------
/// 方向入力状況を返す(-1~1)
/// @return 方向入力状況
const Vector2& InputManager::axesRaw() const
{
	return mAxesRaw;
}

//-------------------------------------------------------------------------------------------------
/// ボタンを押しているか
/// @return 押している(true)
bool InputManager::getButton(const InputCode& aCode) const
{
	return mState[(int)aCode];
}

//-------------------------------------------------------------------------------------------------
/// ボタンを押したか
/// @return 押した(true)
bool InputManager::getButtonDown(const InputCode& aCode) const
{
	return mState[(int)aCode] && !mPrevState[(int)aCode];
}

//-------------------------------------------------------------------------------------------------
/// ボタンを離したか
/// @return 離した(true)
bool InputManager::getButtonUp(const InputCode& aCode) const
{
	return !mState[(int)aCode] && mPrevState[(int)aCode];
}

//-------------------------------------------------------------------------------------------------
/// 方向入力状況更新
void InputManager::updateAxes()
{
	// AxesRaw方向ボタン
	mAxesRaw = 0;
	mAxesRaw.x += INPUT->getKey(DIK_RIGHT) || INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_RIGHT);
	mAxesRaw.x -= INPUT->getKey(DIK_LEFT) || INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_LEFT);
	mAxesRaw.y += INPUT->getKey(DIK_UP) || INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_UP);
	mAxesRaw.y -= INPUT->getKey(DIK_DOWN) || INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_DOWN);

	// AxesRawスティック
	Vector2 thumb = INPUT->getXInputThumb(0);
	mAxesRaw.x += Math::Clamp(thumb.x, -1.0f, 1.0f);
	mAxesRaw.y += Math::Clamp(thumb.y, -1.0f, 1.0f);
	mAxesRaw.x = Math::Clamp(mAxesRaw.x, -1.0f, 1.0f);
	mAxesRaw.y = Math::Clamp(mAxesRaw.y, -1.0f, 1.0f);

	// Axes方向ボタン
	float speed = FPS->deltaTime() * DEFINE_AXIS_SPEED;
	mAxes.x = Math::Lerp(mAxes.x, Math::Sign(mAxesRaw.x), speed);
	mAxes.y = Math::Lerp(mAxes.y, Math::Sign(mAxesRaw.y), speed);

}

//-------------------------------------------------------------------------------------------------
/// ボタン入力状況更新
void InputManager::updateButtons()
{
	// 決定ボタン
	mState[(int)InputCode::OK] =
		INPUT->getKey(DIK_Z) || INPUT->getXInputButton(XINPUT_GAMEPAD_B);
	// キャンセルボタン
	mState[(int)InputCode::Cancel] =
		INPUT->getKey(DIK_X) || INPUT->getXInputButton(XINPUT_GAMEPAD_A);
	// 上キー
	mState[(int)InputCode::UP] = (mAxesRaw.y == 1);
	// 下キー
	mState[(int)InputCode::DOWN] = (mAxesRaw.y == -1);
}

} // namespace
// EOF
