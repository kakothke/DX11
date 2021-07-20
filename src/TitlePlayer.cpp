#include "TitlePlayer.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TitlePlayer::TitlePlayer()
	: mRenderer()
{
	// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
TitlePlayer::~TitlePlayer()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TitlePlayer::update()
{
	const static float ROT_SPEED = 10.0f;
	mTransform.rot *= Quaternion::Euler(Vector3::forward * ROT_SPEED * mFps->deltaTime());
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TitlePlayer::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
