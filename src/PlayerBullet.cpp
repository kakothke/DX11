#include "PlayerBullet.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
PlayerBullet::PlayerBullet(Transform aTransform, Vector3 aTargetPos)
	: mRenderer()
	, mVelocity(aTargetPos - aTransform.pos)
	, mTimer(0)
{
	// �g�����X�t�H�[���ݒ�
	mTransform = aTransform;
	mTransform.scale = 0.25f;
	mTransform.scale.z = 1.0f;

	// �`��ݒ�
	//mRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
PlayerBullet::~PlayerBullet()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void PlayerBullet::update()
{
	// �萔
	const static float DESTROY_TIME = 1.0f;
	const static float BULLET_SPEED = 2.0f;

	// �ʒu�X�V
	mTransform.pos += mVelocity.Normalized() * BULLET_SPEED;

	// ��莞�Ԃ����������
	if (mTimer > DESTROY_TIME) {
		destroyThisGameObject();
	}
	mTimer += FPS->deltaTime();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void PlayerBullet::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
