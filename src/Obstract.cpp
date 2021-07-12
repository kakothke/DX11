#include "Obstract.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"
#include "Sound.h"
#include "GrazeEffect.h"
#include "Player.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Obstract::Obstract()
	: mColor()
	, mMoveSpeed(0.0f)
{
	// �g�����X�t�H�[���ݒ�
	mTransform.pos = Vector3(0.0f, -3.0f, 300.0f);
	mTransform.scale = Vector3(2.0f, 5.0f, 1.0f);
	mTransform.pos.x += Random::RandomFloat(500, 0.1f) * Random::RandomSign();
	mTransform.scale.x += Random::RandomInt(5);

	// �^�O�ݒ�
	setTag(GameObjectTag::Obstract);

	/// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Obstract));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mColor.a = 0.0f;
	mRenderer.setColor(mColor);
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Obstract::~Obstract()
{
}

//-------------------------------------------------------------------------------------------------
/// �ړ����x
void Obstract::setMoveSpeed(const float& aSpeed)
{
	mMoveSpeed = aSpeed;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Obstract::update()
{
	// �萔
	const static float DELETE_POS = -20.0f;
	const static float COLOR_SPEED = 2.0f;

	// �ړ�
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();

	// �F
	if (mColor.a < 1) {
		mColor.a += COLOR_SPEED * FPS->deltaTime();
	}

	// �����蔻��
	collisionPlayer();

	// ����
	if (mTransform.pos.z < DELETE_POS) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Obstract::draw()
{
	mRenderer.setColor(mColor);
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// �v���C���[�Ƃ̓����蔻��
void Obstract::collisionPlayer()
{
	const static auto PLAYER_OBJ = (Player*)mGameObjectList->findGameObject(GameObjectTag::Player);
	const static float PLAYER_SIZE = 0.5f;

	if (PLAYER_OBJ->activeSelf()) {
		Vector3 playerPos = PLAYER_OBJ->transform().pos;
		Transform collisionTransform = mTransform;
		collisionTransform.pos.y = 0;
		collisionTransform.scale.y = 2.0f;

		// �v���C���[�Ƀq�b�g
		if (collisionTransform.pos.x - collisionTransform.scale.x / 2.0f < playerPos.x + PLAYER_SIZE &&
			collisionTransform.pos.x + collisionTransform.scale.x / 2.0f > playerPos.x - PLAYER_SIZE &&
			collisionTransform.pos.y - collisionTransform.scale.y / 2.0f < playerPos.y + PLAYER_SIZE &&
			collisionTransform.pos.y + collisionTransform.scale.y / 2.0f > playerPos.y - PLAYER_SIZE &&
			collisionTransform.pos.z - collisionTransform.scale.z / 2.0f < playerPos.z + PLAYER_SIZE &&
			collisionTransform.pos.z + collisionTransform.scale.z / 2.0f > playerPos.z - PLAYER_SIZE) {
			PLAYER_OBJ->missEvent();
			destroyThisGameObject();
			return;
		}

		// �v���C���[�ɂ�����
		collisionTransform.scale.x *= 4.0f;
		if (collisionTransform.pos.x - collisionTransform.scale.x / 2.0f < playerPos.x + PLAYER_SIZE &&
			collisionTransform.pos.x + collisionTransform.scale.x / 2.0f > playerPos.x - PLAYER_SIZE &&
			collisionTransform.pos.y - collisionTransform.scale.y / 2.0f < playerPos.y + PLAYER_SIZE &&
			collisionTransform.pos.y + collisionTransform.scale.y / 2.0f > playerPos.y - PLAYER_SIZE &&
			collisionTransform.pos.z - collisionTransform.scale.z / 2.0f < playerPos.z + PLAYER_SIZE &&
			collisionTransform.pos.z + collisionTransform.scale.z / 2.0f > playerPos.z - PLAYER_SIZE) {
			SOUND->playOneShot((int)SoundList::SE_Graze);

			mGameObjectList->setGameObjectListToWorld(new GrazeEffect(collisionTransform.pos, playerPos), 0, true);
		}
	}
}

} // namespace
// EOF
