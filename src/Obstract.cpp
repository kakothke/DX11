#include "Obstract.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Random.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Obstract::Obstract()
	: mColor()
	, mMoveSpeed(0.0f)
{
	// トランスフォーム設定
	mTransform.pos = Vector3(0.0f, -1.0f, 300.0f);
	mTransform.scale = Vector3(1.0f, 3.0f, 1.0f);
	mTransform.pos.x += Random::RandomFloat(500, 0.1f) * Random::RandomSign();
	mTransform.scale.x += Random::RandomInt(5);

	// タグ設定
	setTag(GameObjectTag::Obstract);

	/// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Obstract));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mColor.a = 0.0f;
	mRenderer.setColor(mColor);
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Obstract::~Obstract()
{
}

//-------------------------------------------------------------------------------------------------
/// 移動速度
void Obstract::setMoveSpeed(const float aSpeed)
{
	mMoveSpeed = aSpeed;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Obstract::update()
{
	// 定数
	const static float DELETE_POS = -20.0f;
	const static float COLOR_SPEED = 2.0f;

	// 移動
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();

	// 色
	if (mColor.a < 1) {
		mColor.a += COLOR_SPEED * FPS->deltaTime();
	}

	// 消去
	if (mTransform.pos.z < DELETE_POS) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Obstract::draw()
{
	mRenderer.setColor(mColor);
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// 当たり判定
Transform Obstract::getCollision()
{
	Transform transform;
	transform = mTransform;
	transform.pos.y = 0.0f;
	transform.scale.x *= 0.25f;

	return transform;
}

} // namespace
// EOF