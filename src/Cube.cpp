#include "Cube.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "OBJFileName.h"
#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Cube::Cube()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
Cube::Cube(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
void Cube::initialize()
{
	mRenderer.setObjAndShaderData(
		OBJFileName::fileName(OBJList::Cube),
		ShaderFileName::fileName(ShaderList::Unlit)
	);
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Cube::update()
{
	mTransform.scale.y += 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Cube::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
