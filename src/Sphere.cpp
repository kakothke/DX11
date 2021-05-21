#include "Sphere.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "OBJFileName.h"
#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Sphere::Sphere()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
Sphere::Sphere(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
void Sphere::initialize()
{
	mRenderer.setObjAndShaderData(
		OBJFileName::fileName(OBJList::Sphere),
		ShaderFileName::fileName(ShaderList::Standard)
	);
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Sphere::update()
{
	mTransform.scale.z += 0.05f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Sphere::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
