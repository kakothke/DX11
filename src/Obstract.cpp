#include "Obstract.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Obstract::Obstract(Transform aTransform, const float& aSpeed)
	: mMoveSpeed(aSpeed)
{
	// �g�����X�t�H�[���ݒ�
	mTransform = aTransform;

	// �^�O�ݒ�
	setTag(GameObjectTag::Obstract);

	/// �`��ݒ�
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Obstract));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Obstract::~Obstract()
{
}

//-------------------------------------------------------------------------------------------------
/// �ړ����x
void Obstract::setMoveSpeed(const float aSpeed)
{
	mMoveSpeed = aSpeed;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Obstract::update()
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
/// �`��
void Obstract::draw()
{
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// �����蔻��
Transform Obstract::getCollision()
{
	Transform transform;
	transform = mTransform;
	transform.pos.y = 0.0f;
	transform.scale.x *= 0.25f;
	
	return transform;
}

} // namespace
// EOF