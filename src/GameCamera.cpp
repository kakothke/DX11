#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
#include "InputManager.h"
#include "Math.h"
#include "Player.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameCamera::GameCamera()
	: mPlayer(nullptr)
	, mKatamuki(1.0f)
{	
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
GameCamera::~GameCamera()
{
}

//-------------------------------------------------------------------------------------------------
/// ������
void GameCamera::initialize()
{
	mPlayer = (Player*)mGameObjectList->findWorldGameObject(GameObjectTag::Player);
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameCamera::update()
{
	// �萔
	const static float NORMAL_KATAMUKI_LEVEL = 1.0f;
	const static float UP_KATAMUKI_LEVEL = NORMAL_KATAMUKI_LEVEL * 2.0f;
	const static float DOWN_KATAMUKI_LEVEL = NORMAL_KATAMUKI_LEVEL / 2.0f;
	const static Vector3 LOCAL_POS = Vector3(0.0f, 2.0f, -20.0f);

	if (mPlayer->activeSelf()) {
		// �v���C���[�̈ʒu
		Vector3 playerPos = mPlayer->transform().pos - mPlayer->transform().localPos;

		// �J�����X���x�X�V
		float speed = 10.0f * mFps->deltaTime();
		if (INPUT_MANAGER->axesRaw().y == 1) {
			// ��L�[����������
			if (mKatamuki != UP_KATAMUKI_LEVEL) {
				mKatamuki = Math::Lerp(mKatamuki, UP_KATAMUKI_LEVEL, speed);
			}
		} if (INPUT_MANAGER->axesRaw().y == -1) {
			// ���L�[����������
			if (mKatamuki != DOWN_KATAMUKI_LEVEL) {
				mKatamuki = Math::Lerp(mKatamuki, DOWN_KATAMUKI_LEVEL, speed);
			}
		} else {
			// �ʏ�
			if (mKatamuki != NORMAL_KATAMUKI_LEVEL) {
				mKatamuki = Math::Lerp(mKatamuki, NORMAL_KATAMUKI_LEVEL, speed);
			}
		}
		float rotY = INPUT_MANAGER->axes().x * -mKatamuki;
		float rotZ = rotY * 6.0f;

		// �v���C���[��e�I�u�W�F�N�g�Ƃ��ĘA��������
		mTransform.pos = playerPos;

		// ���[�J���ʒu��ύX
		float localPosX = rotY * 2.0f;
		mTransform.localPos = LOCAL_POS;
		mTransform.localPos.x = localPosX;
		mTransform.localRot = Quaternion::Euler(Vector3(0.0f, rotY, rotZ));
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameCamera::draw()
{
}

} // namespace
// EOF
