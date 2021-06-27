#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto INPUT = Input::getInst();

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
	// �X�V�O�ɍŐV�̏���ۑ�
	for (int i = 0; i < (int)InputCode::TERM; i++) {
		memcpy(mPrevState, mState, sizeof(mState));
	}
	
	INPUT->update();

	// ��������
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

	// ����{�^��
	mState[(int)InputCode::OK] =
		INPUT->getKey(DIK_Z) || INPUT->getXInputButton(XINPUT_GAMEPAD_B);

	// �L�����Z���{�^��
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

} // namespace
// EOF
