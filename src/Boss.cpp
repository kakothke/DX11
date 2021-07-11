#include "Boss.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Boss::Boss()
{
	// �g�����X�t�H�[���ݒ�
	mTransform.pos = Vector3(0.0f, 0.0f, 50.0f);

	// �^�O
	setTag(GameObjectTag::Boss);

	// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Boss));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));

	mSRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Arrow));
	mSRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Unlit));
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Boss::update()
{
}

//-------------------------------------------------------------------------------------------------
/// �`��
void Boss::draw()
{
	mRenderer.render(mTransform);
	mSRenderer.render(mTransform);
}

} // namespace
// EOF
