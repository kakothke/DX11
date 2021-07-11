#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class PlayerBooster : public BaseGameObject
{
public:
	PlayerBooster(Transform aTransform);
	~PlayerBooster();
	void update() override;
	void draw() override;

private:
	SpriteRenderer mRenderer;
	Color mColor;

};

} // namespace
// EOF
