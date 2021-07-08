#include "Boss.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �萔
const static Vector3 DEFINE_POS = Vector3(0.0f, 0.0f, 50.0f);

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Boss::Boss()
{
	// �����ʒu
	mTransform.pos = DEFINE_POS;
	//mTransform.scale = 100;

	// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Boss));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));

	mSRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
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
