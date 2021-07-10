#include "Ground.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
Ground::Ground(Transform aTransform, const float& aSpeed)
	: mMoveSpeed(aSpeed)
{
	// �g�����X�t�H�[���ݒ�
	mTransform = aTransform;

	// �^�O�ݒ�
	setTag(GameObjectTag::Ground);

	/// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Cube));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
Ground::~Ground()
{
}

//-------------------------------------------------------------------------------------------------
void Ground::setMoveSpeed(const float aSpeed)
{
	mMoveSpeed = aSpeed;
}

//-------------------------------------------------------------------------------------------------
void Ground::update()
{
	// �萔
	const static float DELETE_POS = -20.0f;

	// �ړ�
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();

	// ����
	if (mTransform.pos.z < DELETE_POS) {
		destroyThisGameObject();
	}
}

//-------------------------------------------------------------------------------------------------
void Ground::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF