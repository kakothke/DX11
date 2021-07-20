#include "TitlePlayer.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TitlePlayer::TitlePlayer()
	: mRenderer()
{
	// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
TitlePlayer::~TitlePlayer()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TitlePlayer::update()
{
	const static float ROT_SPEED = 10.0f;
	mTransform.rot *= Quaternion::Euler(Vector3::forward * ROT_SPEED * mFps->deltaTime());
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TitlePlayer::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
