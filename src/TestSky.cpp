#include "TestSky.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestSky::TestSky()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
TestSky::TestSky(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
void TestSky::initialize()
{
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::SkyBox));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::SkyBox));
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestSky::update()
{
	mTransform.rot.y += 0.001f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestSky::draw()
{
	mRenderer.render(mTransform.XMFLOAT3X3());
}

} // namespace
// EOF
