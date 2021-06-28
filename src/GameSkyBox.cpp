#include "GameSkyBox.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameSkyBox::GameSkyBox()
{
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::SkyBox));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::SkyBox));
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameSkyBox::update()
{
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameSkyBox::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
