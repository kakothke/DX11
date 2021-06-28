#include "PlayerBullet.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
PlayerBullet::PlayerBullet()
{
	mRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
PlayerBullet::~PlayerBullet()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void PlayerBullet::update()
{

}

//-------------------------------------------------------------------------------------------------
/// �`��
void PlayerBullet::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
