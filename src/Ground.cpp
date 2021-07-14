#include "Ground.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
Ground::Ground()
	: mColor()
	, mMoveSpeed(0.0f)
{
	// トランスフォーム設定
	mTransform.pos = Vector3(0.0f, -9.0f, 500.0f);
	mTransform.scale = Vector3(16.0f, 5.0f, 16.0f);
	mTransform.pos.x += Random::RandomInt(50) * Random::RandomSign();
	mTransform.pos.y += Random::RandomInt(4);

	// タグ設定
	setTag(GameObjectTag::Ground);

	/// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Cube));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mColor.a = 0.0f;
	mRenderer.setColor(mColor);
}

//-------------------------------------------------------------------------------------------------
Ground::~Ground()
{
}

//-------------------------------------------------------------------------------------------------
void Ground::setMoveSpeed(const float aSpeed)
{
	mMoveSpeed = aSpeed;
}

//-------------------------------------------------------------------------------------------------
void Ground::update()
{
	// 定数
	const static float DELETE_POS = -20.0f;
	const static float COLOR_SPEED = 0.01f;

	// 移動
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();

	// 色
	if (mColor.a < 1) {
		mColor.a += COLOR_SPEED * mMoveSpeed * FPS->deltaTime();
	}

	// 消去
	if (mTransform.pos.z < DELETE_POS) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
void Ground::draw()
{
	mRenderer.setColor(mColor);
	mRenderer.render(mTransform);
}

} // namespace
// EOF