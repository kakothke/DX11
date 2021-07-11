#include "Obstract.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Obstract::Obstract()
	: mColor()
	, mMoveSpeed(0.0f)
{
	// �g�����X�t�H�[���ݒ�
	mTransform.pos = Vector3(0.0f, -1.0f, 300.0f);
	mTransform.scale = Vector3(1.0f, 3.0f, 1.0f);
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
void Obstract::setMoveSpeed(const float aSpeed)
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
/// �����蔻��
Transform Obstract::getCollision()
{
	Transform transform;
	transform = mTransform;
	transform.pos.y = 0.0f;
	transform.scale.x *= 0.25f;

	return transform;
}

} // namespace
// EOF