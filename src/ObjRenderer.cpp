#include "ObjRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
ObjRenderer::ObjRenderer()
	: mObjData()
	, mShaderData()
{
}

//-------------------------------------------------------------------------------------------------
ObjRenderer::~ObjRenderer()
{
}

//-------------------------------------------------------------------------------------------------
void ObjRenderer::render(Transform aTransform)
{

}

//-------------------------------------------------------------------------------------------------
void ObjRenderer::setObjAndShaderData(ObjList aObjList, ShaderList aShaderList)
{
	mObjData = ObjLoader::getInst()->objData(aObjList);
	mShaderData = ShaderLoader::getInst()->shaderData(aShaderList);
}

} // namespace
// EOF
