#include "Obstract.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Obstract::Obstract(const Transform& aTransform, const float& aSpeed)
	: mMoveSpeed(aSpeed)
{
	// トランスフォーム設定
	mTransform = aTransform;

	/// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Obstract));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
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
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();
	if (mTransform.pos.z < -10.0f) {
		destroyThisGameObject();
	}	
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Obstract::draw()
{
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