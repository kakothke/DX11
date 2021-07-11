#include "PlayerBooster.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
PlayerBooster::PlayerBooster(Transform aTransform)
	: mRenderer()
	, mColor()
{
	mTransform = aTransform;
	mTransform.pos.x += Random::RandomFloat(10, 0.01f) * Random::RandomSign();
	mTransform.pos.y += Random::RandomFloat(10, 0.01f) * Random::RandomSign();

	mRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Efect_Booster));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Unlit));
	mRenderer.setColor(mColor);
}

//-------------------------------------------------------------------------------------------------
PlayerBooster::~PlayerBooster()
{
}

//-------------------------------------------------------------------------------------------------
void PlayerBooster::update()
{
	const static float MOVE_SPEED = 50.0f;
	const static float SCALE_DOWN_SPEED = 3.0f;
	const static float COLOR_ALPHA_DOWN_SPEED = 3.0f;

	mTransform.pos.z -= MOVE_SPEED * FPS->deltaTime();
	mTransform.scale -= SCALE_DOWN_SPEED * FPS->deltaTime();
	mColor.a -= COLOR_ALPHA_DOWN_SPEED * FPS->deltaTime();

	if (mTransform.scale.x < 0.0f) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
void PlayerBooster::draw()
{
	mRenderer.setColor(mColor);
	mRenderer.render(mTransform, true);
}

} // namespace
// EOF