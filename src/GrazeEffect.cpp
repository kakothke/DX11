#include "GrazeEffect.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
GrazeEffect::GrazeEffect(Vector3 aObstractPos, Vector3 aPlayerPos)
	: mRenderer()
	, mVelocity(aPlayerPos - aObstractPos)
	, mColor()
	, mVelocityY(Random::RandomFloat(10, 0.5f)* Random::RandomSign())
{
	mTransform.pos = aPlayerPos;
	mTransform.scale = 0.5f;

	mRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Effect_Graze));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Unlit));

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

	mTransform.pos += mVelocity.Normalized() * MOVE_SPEED * mFps->deltaTime();
	mTransform.pos.y += mVelocityY * mFps->deltaTime();
	mTransform.pos.z -= MOVE_SPEED_Z * mFps->deltaTime();
	mTransform.scale -= SCALE_DOWN_SPEED * mFps->deltaTime();
	mColor.a -= mFps->deltaTime();

	if (mTransform.scale.x < 0.0f) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
void GrazeEffect::draw()
{
	mRenderer.setColor(mColor);
	mRenderer.render(mTransform, true);
}

} // namespace
// EOF
