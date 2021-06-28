#include "PlayerBullet.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
const static float DEFINE_ACTIVE_TIME = 1.0f;
const static float DEFINE_BULLET_SPEED = 2.0f;

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
PlayerBullet::PlayerBullet(Transform aTransform, Vector3 aTargetPos)
	: mRenderer()
	, mVelocity(aTargetPos - aTransform.pos)
	, mTimer(0)
{
	// �����ʒu
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
	mTransform.pos += mVelocity.Normalized() * DEFINE_BULLET_SPEED;

	// ��莞�Ԃ����������
	if (mTimer > DEFINE_ACTIVE_TIME) {
		setActive(false);
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
