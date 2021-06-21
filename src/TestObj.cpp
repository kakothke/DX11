#include "TestObj.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestObj::TestObj()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
TestObj::TestObj(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
void TestObj::initialize()
{
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Test));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mTransform.pos.y = -2;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestObj::update()
{
	mTransform.pos.x += InputManager::getInst()->getAxes().x * 0.5f;
	mTransform.pos.y += InputManager::getInst()->getAxes().y * 0.5f;
	mTransform.rot.y += 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestObj::draw()
{
	mRenderer.render(mTransform.XMFLOAT3X3());
}

} // namespace
// EOF
