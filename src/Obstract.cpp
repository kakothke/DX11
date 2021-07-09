#include "Obstract.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
Obstract::Obstract(const Transform& aTransform, const float& aSpeed)
	: mMoveSpeed(aSpeed)
{
	// �g�����X�t�H�[���ݒ�
	mTransform = aTransform;

	/// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Obstract));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
Obstract::~Obstract()
{
}

//-------------------------------------------------------------------------------------------------
void Obstract::setMoveSpeed(const float aSpeed)
{
	mMoveSpeed = aSpeed;
}

//-------------------------------------------------------------------------------------------------
void Obstract::update()
{
	mTransform.pos.z -= mMoveSpeed * FPS->deltaTime();
	if (mTransform.pos.z < -10.0f) {
		setActive(false);
	}
}

//-------------------------------------------------------------------------------------------------
void Obstract::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF