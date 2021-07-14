#include "Boss.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Boss::Boss()
	:mRenderer()
{
	// �g�����X�t�H�[���ݒ�
	mTransform.pos = Vector3(0.0f, 0.0f, 50.0f);

	// �^�O
	setTag(GameObjectTag::Boss);

	// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Boss));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
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
}

} // namespace
// EOF
