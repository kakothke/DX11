#include "TestObj.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "OBJFileName.h"
#include "ShaderFileName.h"

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
		OBJFileName::fileName(OBJList::TestObj),
		ShaderFileName::fileName(ShaderList::Standard)
	);
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestObj::update()
{
	mTransform.rot.y += 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestObj::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
