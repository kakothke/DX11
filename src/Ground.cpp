#include "Ground.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
Ground::Ground()
	: mColor()
	, mMoveSpeed(0.0f)
{
	// �g�����X�t�H�[���ݒ�
	mTransform.pos = Vector3(0.0f, -9.0f, 500.0f);
	mTransform.scale = Vector3(16.0f, 5.0f, 16.0f);
	mTransform.pos.x += Random::RandomInt(50) * Random::RandomSign();
	mTransform.pos.y += Random::RandomInt(4);

	// �^�O�ݒ�
	setTag(GameObjectTag::Ground);

	/// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Cube));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mColor.a = 0.0f;
	mRenderer.setColor(mColor);
}

//-------------------------------------------------------------------------------------------------
Ground::~Ground()
{
}

//-------------------------------------------------------------------------------------------------
void Ground::setMoveSpeed(const float aSpeed)
{
	mMoveSpeed = aSpeed;
}

//-------------------------------------------------------------------------------------------------
void Ground::update()
{
	// �萔
	const static float DELETE_POS = -20.0f;
	const static float COLOR_SPEED = 0.01f;

	// �ړ�
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();

	// �F
	if (mColor.a < 1) {
		mColor.a += COLOR_SPEED * mMoveSpeed * FPS->deltaTime();
	}

	// ����
	if (mTransform.pos.z < DELETE_POS) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
void Ground::draw()
{
	mRenderer.setColor(mColor);
	mRenderer.render(mTransform);
}

} // namespace
// EOF