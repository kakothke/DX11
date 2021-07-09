#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
#include "InputManager.h"
#include "Math.h"
#include "MyOutputDebugString.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();
const static auto INPUT_MANAGER = InputManager::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameCamera::GameCamera()
	: mPlayerPos()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameCamera::update()
{
	static float decelerate = 1.0f;
	float speed = 10.0f * FPS->deltaTime();
	if (INPUT_MANAGER->getButton(InputCode::Cancel)) {
		if (decelerate != 1.0f / 4.0f) {
			decelerate = Math::Lerp(decelerate, 1.0f / 4.0f, speed);
		}
	} else {
		if (decelerate < 1.0f) {
			decelerate = Math::Lerp(decelerate, 1.0f, speed);
		}
	}

	float x = INPUT_MANAGER->axes().x * decelerate;

	// �v���C���[��e�I�u�W�F�N�g�Ƃ��ĘA��������
	mTransform.pos = mPlayerPos;
	mTransform.localPos.x = x * -2.0f;
	mTransform.localPos.y = 0.5f;
	mTransform.localPos.z = -20.0f;
	mTransform.localRot = Quaternion::Euler(Vector3(0.0f, x, x * 6.0f));

	// �R���X�^���g�o�b�t�@�X�V
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameCamera::draw()
{
}

//-------------------------------------------------------------------------------------------------
void GameCamera::setPlayerPos(const Vector3& aPos)
{
	mPlayerPos = aPos;
}

} // namespace
// EOF
