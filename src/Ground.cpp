#include "Ground.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
Ground::Ground(const Transform& aTransform, const float& aSpeed)
	: mMoveSpeed(aSpeed)
{
	// �g�����X�t�H�[���ݒ�
	mTransform = aTransform;

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
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();
	if (mTransform.pos.z < -10.0f) {
		setActive(false);
	}
}

//-------------------------------------------------------------------------------------------------
void Ground::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF