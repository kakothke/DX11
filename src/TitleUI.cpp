#include "TitleUI.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
TitleUI::TitleUI()
	: mArrowRenderer()
	, mLogoRenderer()
	, mStartRenderer()
	, mBlackRenderer()
	, mBlackColor(Color::clear)
	, mStartButtonDown(false)
{
	// ���
	mArrowRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Arrow));
	mArrowRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mArrowRenderer.setSplit(4, 2);
	mArrowRenderer.setAnchor(0.0f, 1.0f);
	mArrowRenderer.setPivot(0.0f, 1.0f);

	// ���S
	mLogoRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_TitleLogo));
	mLogoRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mLogoRenderer.setAnchor(0.0f, -1.0f);
	mLogoRenderer.setPivot(0.0f, -1.0f);

	// �X�^�[�g
	mStartRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Start));
	mStartRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mStartRenderer.setAnchor(0.0f, 1.0f);
	mStartRenderer.setPivot(0.0f, 1.0f);

	// �u���b�N�A�E�g
	mBlackRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Black));
	mBlackRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mBlackRenderer.setColor(mBlackColor);
}

//-------------------------------------------------------------------------------------------------
TitleUI::~TitleUI()
{
}

//-------------------------------------------------------------------------------------------------
void TitleUI::update()
{
	if (!mStartButtonDown) {
		if (INPUT_MANAGER->axesRaw().y == 1) {
			mStartButtonDown = true;
		}
	} else {
		mBlackColor.a += FPS->deltaTime();
	}
}

//-------------------------------------------------------------------------------------------------
void TitleUI::draw()
{
	// ���
	mArrowRenderer.setUVPos(0 + mStartButtonDown, 0);
	mArrowRenderer.render(Transform(Vector3(-100.0f, -60.0f, 0.0f), Vector3(), Vector3(1.0f)));
	// ���S
	mLogoRenderer.render(Transform(Vector3(0.0f, 30.0f, 0.0f), Vector3(), Vector3(1.0f)));
	// �X�^�[�g
	mStartRenderer.render(Transform(Vector3(60.0f, -60.0f, 0.0f), Vector3(), Vector3(1.0f)));
	// �u���b�N
	if (mStartButtonDown) {
		mBlackRenderer.setColor(mBlackColor);
		mBlackRenderer.render(Transform(Vector3(), Vector3(), Vector3(10.0f)));
	}
}

} // namespace
// EOF
