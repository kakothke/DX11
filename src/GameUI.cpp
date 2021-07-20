#include "GameUI.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();

//-------------------------------------------------------------------------------------------------
const static float DEFINE_BLINKING_TIME = 1.0f;

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameUI::GameUI()
	: mArrowRenderer()
	, mScoreRenderer()
	, mRetryRenderer()
	, mRetryArrowRenderer()
	, mFadeRendererFront()
	, mFadeRendererMiddle()
	, mFadeRendererBack()
	, mArrowTransform()
	, mRetryTransform()
	, mRetryArrowTransform()
	, mFadeTransform()
	, mFadeColorFront(Color::black)
	, mFadeColorMiddle(Color::white)
	, mFadeColorBack(Color::black)
	, mScoreBlinkingTimer(0.0f)
	, mScore(0)
	, mMissFlag(false)
	, mRetryFlag(false)
{
	// ���
	int i = 0;
	for (auto& renderer : mArrowRenderer) {
		mArrowTransform[i].pos.y = -20.0f;
		renderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Arrow));
		renderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
		renderer.setSplit(4, 2);
		renderer.setAnchor(0.0f, 1.0f);
		renderer.setPivot(0.0f, 1.0f);
		renderer.setColor(Color(1.0f, 1.0f, 1.0f, 0.5f));
		i++;
	}
	mArrowTransform[0].pos.y -= 75.0f;
	mArrowTransform[1].pos.y += 0.0f;
	mArrowTransform[2].pos.x -= 90.0f;
	mArrowTransform[3].pos.x += 90.0f;

	// �X�R�A
	for (auto& renderer : mScoreRenderer) {
		renderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Numbers));
		renderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
		renderer.setSplit(10, 1);
		renderer.setAnchor(0.0f, -0.7f);
	}

	// ���g���C
	mRetryRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Retry));
	mRetryRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mRetryRenderer.setAnchor(0.0f, 0.0f);
	mRetryRenderer.setPivot(0.0f, 0.0f);
	mRetryTransform.pos = Vector3(60.0f, 0.0f, 0.0f);
	mRetryArrowRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Arrow));
	mRetryArrowRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mRetryArrowRenderer.setSplit(4, 2);
	mRetryArrowRenderer.setAnchor(0.0f, 0.0f);
	mRetryArrowRenderer.setPivot(0.0f, 0.0f);
	mRetryArrowTransform.pos = Vector3(-100.0f, 0.0f, 0.0f);

	// �t�F�[�h
	mFadeRendererFront.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_White));
	mFadeRendererFront.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mFadeRendererMiddle.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_White));
	mFadeRendererMiddle.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mFadeRendererBack.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_White));
	mFadeRendererBack.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mFadeTransform.scale = 10.0f;
	mFadeColorBack.a = 0.0f;
	mFadeColorMiddle.a = 0.0f;
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
GameUI::~GameUI()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameUI::update()
{
	const static float FADE_SPEED_BACK = 0.5f;
	const static float FADE_COLOR_TARGET_BACK = 0.5f;
	const static float FADE_SPEED_MIDDLE = 3.0f;

	if (mMissFlag) {
		// �X�R�A�_��
		if (mScoreBlinkingTimer > DEFINE_BLINKING_TIME) {
			mScoreBlinkingTimer = 0.0f;
		} else {
			mScoreBlinkingTimer += mFps->deltaTime();
		}
		// �t�F�[�h���
		if (mFadeColorBack.a < FADE_COLOR_TARGET_BACK) {
			mFadeColorBack.a += FADE_SPEED_BACK * mFps->deltaTime();
		}
		// �t�F�[�h����
		if (mFadeColorMiddle.a > 0.0f) {
			mFadeColorMiddle.a -= FADE_SPEED_MIDDLE * mFps->deltaTime();
		}
		// ���g���C�{�^��
		if (!mRetryFlag && INPUT_MANAGER->getButtonDown(InputCode::UP)) {
			mRetryFlag = true;
			mFadeColorFront = Color::clear;
		}
	}
	// �t�F�[�h�O��
	if (!mRetryFlag) {
		if (mFadeColorFront.a > 0.0f) {
			mFadeColorFront.a -= mFps->deltaTime();
		}
	} else {
		if (mFadeColorFront.a < 1.0f) {
			mFadeColorFront.a += mFps->deltaTime();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameUI::draw()
{
	// �t�F�[�h���
	if (mFadeColorBack.a > 0.0f) {
		mFadeRendererBack.setColor(mFadeColorBack);
		mFadeRendererBack.render(mFadeTransform);
	}

	// ���
	if (!mMissFlag) {
		Vector2 axis = INPUT_MANAGER->axesRaw();
		mArrowRenderer[0].setUVPos(0 + (axis.y == 1), 0);
		mArrowRenderer[1].setUVPos(2 + (axis.y == -1), 0);
		mArrowRenderer[2].setUVPos(0 + (axis.x == -1), 1);
		mArrowRenderer[3].setUVPos(2 + (axis.x == 1), 1);
		int i = 0;
		for (auto& renderer : mArrowRenderer) {
			renderer.render(mArrowTransform[i]);
			i++;
		}
	}

	// �X�R�A
	const static float POS_OFFSET = 40.0f;
	const static float NUM_VIEW_TIMING = 2.0f;
	Transform scoreTransform = Transform();
	std::vector<int> splitNum = Math::Split(mScore);
	int meterDegit = Math::Degit(mScore);
	scoreTransform.pos.x = (meterDegit - 1) * POS_OFFSET / 2.0f;
	if (mScoreBlinkingTimer < DEFINE_BLINKING_TIME / NUM_VIEW_TIMING) {
		for (int i = 0; i < meterDegit; i++) {
			mScoreRenderer[i].setUVPos(splitNum[i], 0);
			mScoreRenderer[i].render(scoreTransform);
			scoreTransform.pos.x -= POS_OFFSET;
		}
	}

	// ���g���C
	if (mMissFlag) {
		mRetryRenderer.render(mRetryTransform);
		mRetryArrowRenderer.setUVPos(0 + mRetryFlag, 0);
		mRetryArrowRenderer.render(mRetryArrowTransform);
	}

	// �t�F�[�h����
	if (mFadeColorMiddle.a > 0.0f) {
		mFadeRendererMiddle.setColor(mFadeColorMiddle);
		mFadeRendererMiddle.render(mFadeTransform);
	}

	// �t�F�[�h�O��
	if (mFadeColorFront.a > 0.0f) {
		mFadeRendererFront.setColor(mFadeColorFront);
		mFadeRendererFront.render(mFadeTransform);
	}
}

//-------------------------------------------------------------------------------------------------
/// �X�R�A���Z�b�g����
void GameUI::setScore(int aScore)
{
	mScore = aScore;
}

//-------------------------------------------------------------------------------------------------
/// �~�X�t���O�𗧂Ă�
void GameUI::setMissFlagTrue()
{
	mMissFlag = true;
	mFadeColorMiddle.a = 1.0f;
}

} // namespace
// EOF
