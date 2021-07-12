#include "TitlePlayer.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"
#include "BoosterEffect.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TitlePlayer::TitlePlayer()
{
	// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
TitlePlayer::~TitlePlayer()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TitlePlayer::update()
{
	const static float ROT_SPEED = 10.0f;
	mTransform.rot *= Quaternion::Euler(Vector3::forward * ROT_SPEED * FPS->deltaTime());
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TitlePlayer::draw()
{
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// �G�t�F�N�g����
void TitlePlayer::instanceEffect()
{
	const static float INSTANCE_BOOSTER_TIME = 0.05f;
	const static float SCALE_RANGE = 0.25f;

	if (mInstanceBoosterTimer > INSTANCE_BOOSTER_TIME) {
		mInstanceBoosterTimer = 0.0f;
		Transform transform = mTransform;
		float axisY = INPUT_MANAGER->axesRaw().y;
		if (axisY == 1) {
			transform.scale += SCALE_RANGE;
		} else if (axisY == -1) {
			transform.scale -= SCALE_RANGE;
		}
		mGameObjectList->setGameObjectListToWorld(new BoosterEffect(transform), 0, true);
	} else {
		mInstanceBoosterTimer += FPS->deltaTime();
	}
}

} // namespace
// EOF
