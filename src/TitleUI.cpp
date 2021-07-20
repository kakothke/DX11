#include "TitleUI.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();

//-------------------------------------------------------------------------------------------------
TitleUI::TitleUI()
	: mLogoRenderer()
	, mStartRenderer()
	, mStartArrowRenderer()
	, mFadeRenderer()
	, mLogoTransform()
	, mArrowTransform()
	, mStartTransform()
	, mFadeTransform()
	, mFadeColor(Color::clear)
	, mStartButtonDown(false)
{
	// ロゴ
	mLogoRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_TitleLogo));
	mLogoRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mLogoRenderer.setAnchor(0.0f, -1.0f);
	mLogoRenderer.setPivot(0.0f, -1.0f);
	mLogoTransform.pos.y = 30.0f;

	// スタート
	mStartRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Start));
	mStartRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mStartRenderer.setAnchor(0.0f, 1.0f);
	mStartRenderer.setPivot(0.0f, 1.0f);
	mStartTransform.pos = Vector3(60.0f, -60.0f, 0.0f);
	mStartArrowRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Arrow));
	mStartArrowRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mStartArrowRenderer.setSplit(4, 2);
	mStartArrowRenderer.setAnchor(0.0f, 1.0f);
	mStartArrowRenderer.setPivot(0.0f, 1.0f);
	mArrowTransform.pos = Vector3(-100.0f, -60.0f, 0.0f);


	// フェードアウト
	mFadeRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_White));
	mFadeRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mFadeRenderer.setColor(mFadeColor);
	mFadeTransform.scale = 10.0f;
}

//-------------------------------------------------------------------------------------------------
TitleUI::~TitleUI()
{
}

//-------------------------------------------------------------------------------------------------
void TitleUI::update()
{
	if (!mStartButtonDown) {
		if (INPUT_MANAGER->getButtonDown(InputCode::UP)) {
			mStartButtonDown = true;
		}
	} else {
		mFadeColor.a += mFps->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
void TitleUI::draw()
{
	// ロゴ
	mLogoRenderer.render(mLogoTransform);
	// スタート
	mStartRenderer.render(mStartTransform);
	mStartArrowRenderer.setUVPos(0 + mStartButtonDown, 0);
	mStartArrowRenderer.render(mArrowTransform);
	// フェードアウト
	if (mStartButtonDown) {
		mFadeRenderer.setColor(mFadeColor);
		mFadeRenderer.render(mFadeTransform);
	}
}

} // namespace
// EOF
