#include "GameSkyBox.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameSkyBox::GameSkyBox()
{
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::SkyBox));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::SkyBox));
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameSkyBox::update()
{
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameSkyBox::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
