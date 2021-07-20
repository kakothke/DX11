#include "ExplosionEffect.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
ExplosionEffect::ExplosionEffect(Vector3 aInstancePos)
	: mRenderer()
{
	mTransform.pos = aInstancePos;

	mTransform.scale.x = 0.25f;
	mTransform.scale.y = 0.25f;

	mRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Effect_Explosion));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Unlit));
}

//-------------------------------------------------------------------------------------------------
ExplosionEffect::~ExplosionEffect()
{
}

//-------------------------------------------------------------------------------------------------
void ExplosionEffect::update()
{
	const static float DESTROY_SCALE = 1.0f;
	const static float SCALE_UP_SPEED = 8.0f;
	const static float COLOR_ALPHA_DOWN_SPEED = 3.0f;

	mTransform.scale.x += SCALE_UP_SPEED * mFps->deltaTime();
	mTransform.scale.y += SCALE_UP_SPEED * mFps->deltaTime();
	mColor.a -= COLOR_ALPHA_DOWN_SPEED * mFps->deltaTime();

	if (mColor.a < 0.0f) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
void ExplosionEffect::draw()
{
	mRenderer.setColor(mColor);
	mRenderer.render(mTransform, true);
}

} // namespace
// EOF