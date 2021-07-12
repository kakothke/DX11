#include "ExplosionEffect.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
ExplosionEffect::ExplosionEffect(Vector3 aInstancePos)
	: mRenderer()
{
	mTransform.pos = aInstancePos;
	/*mTransform.pos.x += Random::RandomInt(3) * Random::RandomSign();
	mTransform.pos.y += Random::RandomInt(3) * Random::RandomSign();*/

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

	mTransform.scale.x += SCALE_UP_SPEED * FPS->deltaTime();
	mTransform.scale.y += SCALE_UP_SPEED * FPS->deltaTime();
	mColor.a -= COLOR_ALPHA_DOWN_SPEED * FPS->deltaTime();

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