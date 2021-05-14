#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include "ObjLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestScene::TestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	// リソースの読み込み
	ObjLoader::getInst()->load(ObjList::Cube);
	ObjLoader::getInst()->load(ObjList::Sphere);
	ShaderLoader::getInst()->load(ShaderList::UnlitShader);
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
TestScene::~TestScene()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestScene::update()
{
	mCamera.update();
	mCube.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestScene::draw()
{
	mCube.draw();
}

} // namespace
// EOF
