#include "TestObj.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	mRenderer.setObjAndShaderData(
		ResourceFileName::OBJ.at(OBJList::Test),
		ResourceFileName::Shader.at(ShaderList::Standard)
	);
	mTransform.pos.y = -2;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestObj::update()
{
	mTransform.rot.y += 0.01f;
	mTransform.pos.z -= 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestObj::draw()
{
	mRenderer.render(mTransform.XMFLOAT3X3());
}

} // namespace
// EOF
