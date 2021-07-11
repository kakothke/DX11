#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class GrazeEffect : public BaseGameObject
{
public:
	GrazeEffect(Vector3 aObstractPos, Vector3 aPlayerPos);
	~GrazeEffect();
	void update() override;
	void draw() override;

private:
	SpriteRenderer mRenderer;
	Vector3 mVelocity;

};

} // namespace
// EOF
