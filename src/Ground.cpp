#include "Ground.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
Ground::Ground(Transform aTransform, const float& aSpeed)
	: mMoveSpeed(aSpeed)
{
	// トランスフォーム設定
	mTransform = aTransform;

	// タグ設定
	setTag(GameObjectTag::Ground);

	/// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Cube));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
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

	// 移動
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();

	// 消去
	if (mTransform.pos.z < DELETE_POS) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
void Ground::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF