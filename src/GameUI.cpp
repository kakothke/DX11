#include "GameUI.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
GameUI::GameUI()
	: mArrowTransform()
	, mArrowRenderer()
	, mBlackRenderer()
	, mBlackColor()
{
	// 矢印
	for (auto& arrow : mArrowTransform) {
		arrow.pos.y = -20.0f;
	}
	mArrowTransform[0].pos -= Vector3::up * 75.0f;
	mArrowTransform[1].pos += Vector3::up * 0.0f;
	mArrowTransform[2].pos -= Vector3::right * 90.0f;
	mArrowTransform[3].pos += Vector3::right * 90.0f;
	for (auto& arrow : mArrowRenderer) {
		arrow.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Arrow));
		arrow.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
		arrow.setSplit(4, 2);
		arrow.setAnchor(0.0f, 1.0f);
		arrow.setPivot(0.0f, 1.0f);
		arrow.setColor(Color(1.0f, 1.0f, 1.0f, 0.5f));
	}

	// ブラックアウト
	mBlackRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Black));
	mBlackRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
}

//-------------------------------------------------------------------------------------------------
GameUI::~GameUI()
{

}

//-------------------------------------------------------------------------------------------------
void GameUI::update()
{
	if (mBlackColor.a > 0) {
		mBlackColor.a -= FPS->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
void GameUI::draw()
{
	// 矢印
	Vector2 axis = INPUT_MANAGER->axesRaw();
	mArrowRenderer[0].setUVPos(0 + (axis.y == 1), 0);
	mArrowRenderer[1].setUVPos(2 + (axis.y == -1), 0);
	mArrowRenderer[2].setUVPos(0 + (axis.x == -1), 1);
	mArrowRenderer[3].setUVPos(2 + (axis.x == 1), 1);
	for (int i = 0; i < 4; i++) {
		mArrowRenderer[i].render(mArrowTransform[i]);
	}

	// ブラック
	if (mBlackColor.a > 0.0f) {
		mBlackRenderer.setColor(mBlackColor);
		mBlackRenderer.render(Transform(Vector3(), Vector3(), Vector3(10.0f)));
	}
}

} // namespace
// EOF
