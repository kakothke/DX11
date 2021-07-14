#include "MoveLineEffect.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Fps.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
MoveLineEffect::MoveLineEffect()
	: mMoveSpeed(0.0f)
{
	// �^�O
	setTag(GameObjectTag::Effect_MoveLine);

	// �`��ݒ�
	mRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Effect_Circle));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Unlit));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
MoveLineEffect::~MoveLineEffect()
{
}

//-------------------------------------------------------------------------------------------------
/// ������
void MoveLineEffect::initialize()
{
	const static float INSTANCE_RADIUS = 60.0f;

	const auto cameraPosX = mGameObjectList->findWorldGameObject(GameObjectTag::Player)->transform().pos.x;
	const float angleDegree = (float)Random::RandomInt(360);
	const float angleRadian = angleDegree * 3.141592653589793f / 180.0f;
	mTransform.pos.x = cameraPosX + INSTANCE_RADIUS * cos(angleRadian);
	mTransform.pos.y = INSTANCE_RADIUS * sin(angleRadian);
	mTransform.pos.z = 600.0f;
	mTransform.rot = Quaternion::Euler(Vector3(-angleDegree, 90.0f, 0.0f));
	mTransform.scale = Vector3(10.0f, 0.25f, 1.0f);
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void MoveLineEffect::update()
{
	// �萔
	const static float MULTIPLE_SPEED = 4.0f;
	const static float DELETE_POS = -20.0f;
	const static float COLOR_SPEED = 2.0f;

	// �ړ�
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime() * MULTIPLE_SPEED;

	// ����
	if (mTransform.pos.z < DELETE_POS) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
void MoveLineEffect::draw()
{
	mRenderer.render(mTransform, true);
}

//-------------------------------------------------------------------------------------------------
/// �ړ����x�ύX
void MoveLineEffect::setMoveSpeed(const float aSpeed)
{
	mMoveSpeed = aSpeed;
}

} // namespace
// EOF
