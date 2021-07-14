#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
const static float DEFINE_AXIS_SPEED = 10.0f;

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto INPUT = Input::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
InputManager::InputManager()
	: mState()
	, mPrevState()
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
InputManager::~InputManager()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void InputManager::update()
{
	// �X�V�O�ɍŐV�̏���ۑ�
	INPUT->update();
	for (int i = 0; i < (int)InputCode::TERM; i++) {
		memcpy(mPrevState, mState, sizeof(mState));
	}

	// ��������
	updateAxes();
	// �{�^������
	updateButtons();
}

//-------------------------------------------------------------------------------------------------
/// �������͏󋵂�Ԃ�(-1.0f~1.0f)
/// @return �������͏�
const Vector2& InputManager::axes() const
{
	return mAxes;
}

//-------------------------------------------------------------------------------------------------
/// �������͏󋵂�Ԃ�(-1~1)
/// @return �������͏�
const Vector2& InputManager::axesRaw() const
{
	return mAxesRaw;
}

//-------------------------------------------------------------------------------------------------
/// �{�^���������Ă��邩
/// @return �����Ă���(true)
bool InputManager::getButton(const InputCode& aCode) const
{
	return mState[(int)aCode];
}

//-------------------------------------------------------------------------------------------------
/// �{�^������������
/// @return ������(true)
bool InputManager::getButtonDown(const InputCode& aCode) const
{
	return mState[(int)aCode] && !mPrevState[(int)aCode];
}

//-------------------------------------------------------------------------------------------------
/// �{�^���𗣂�����
/// @return ������(true)
bool InputManager::getButtonUp(const InputCode& aCode) const
{
	return !mState[(int)aCode] && mPrevState[(int)aCode];
}

//-------------------------------------------------------------------------------------------------
/// �������͏󋵍X�V
void InputManager::updateAxes()
{
	// AxesRaw�����{�^��
	mAxesRaw = 0;
	mAxesRaw.x += INPUT->getKey(DIK_RIGHT) || INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_RIGHT);
	mAxesRaw.x -= INPUT->getKey(DIK_LEFT) || INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_LEFT);
	mAxesRaw.y += INPUT->getKey(DIK_UP) || INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_UP);
	mAxesRaw.y -= INPUT->getKey(DIK_DOWN) || INPUT->getXInputButton(XINPUT_GAMEPAD_DPAD_DOWN);

	// AxesRaw�X�e�B�b�N
	Vector2 thumb = INPUT->getXInputThumb(0);
	mAxesRaw.x += Math::Clamp(thumb.x, -1.0f, 1.0f);
	mAxesRaw.y += Math::Clamp(thumb.y, -1.0f, 1.0f);
	mAxesRaw.x = Math::Clamp(mAxesRaw.x, -1.0f, 1.0f);
	mAxesRaw.y = Math::Clamp(mAxesRaw.y, -1.0f, 1.0f);

	// Axes�����{�^��
	float speed = FPS->deltaTime() * DEFINE_AXIS_SPEED;
	mAxes.x = Math::Lerp(mAxes.x, Math::Sign(mAxesRaw.x), speed);
	mAxes.y = Math::Lerp(mAxes.y, Math::Sign(mAxesRaw.y), speed);

}

//-------------------------------------------------------------------------------------------------
/// �{�^�����͏󋵍X�V
void InputManager::updateButtons()
{
	// ����{�^��
	mState[(int)InputCode::OK] =
		INPUT->getKey(DIK_Z) || INPUT->getXInputButton(XINPUT_GAMEPAD_B);
	// �L�����Z���{�^��
	mState[(int)InputCode::Cancel] =
		INPUT->getKey(DIK_X) || INPUT->getXInputButton(XINPUT_GAMEPAD_A);
	// ��L�[
	mState[(int)InputCode::UP] = (mAxesRaw.y == 1);
	// ���L�[
	mState[(int)InputCode::DOWN] = (mAxesRaw.y == -1);
}

} // namespace
// EOF
