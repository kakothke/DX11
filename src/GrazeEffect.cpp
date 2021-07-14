#include "GrazeEffect.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
GrazeEffect::GrazeEffect(Vector3 aObstractPos, Vector3 aPlayerPos)
	: mRenderer()
{
	mTransform.pos = aPlayerPos;
	mTransform.rot = Quaternion::Euler(Vector3(0.0f, 0.0f, 45.0f));
	mTransform.scale = 0.5f;
	mVelocityY = Random::RandomFloat(10, 0.5f) * Random::RandomSign();

	mRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Effect_Graze));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Unlit));

	mVelocity = aPlayerPos - aObstractPos;
}

//-------------------------------------------------------------------------------------------------
GrazeEffect::~GrazeEffect()
{
}

//-------------------------------------------------------------------------------------------------
void GrazeEffect::update()
{
	const static float MOVE_SPEED = 20.0f;
	const static float MOVE_SPEED_Z = MOVE_SPEED * 4.0f;
	const static float SCALE_DOWN_SPEED = 3.0f;

	mTransform.pos += mVelocity.Normalized() * MOVE_SPEED * FPS->deltaTime();
	mTransform.pos.y += mVelocityY * FPS->deltaTime();
	mTransform.pos.z -= MOVE_SPEED_Z * FPS->deltaTime();
	mTransform.scale -= SCALE_DOWN_SPEED * FPS->deltaTime();

	if (mTransform.scale.x < 0.0f) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
void GrazeEffect::draw()
{
	mRenderer.render(mTransform, true);
}

} // namespace
// EOF
