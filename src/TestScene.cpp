#include "TestScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TestScene::TestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mTestObj({ Vector3(0,0,0),Vector3(),Vector3(1) })
, mTestSprite({ Vector3(-100,0,0),Vector3(),Vector3(0.2f) })
, mT2({ Vector3(100,0,0),Vector3(),Vector3(0.2f) })
{
	mFont.setShaderData(ResourceFileName::Shader.at(ShaderList::Sprite));
	// �e�X�g�T�E���h
	const auto sound = Sound::getInst();
	const auto resource = ResourceManager::getInst();
	sound->play(resource->BGMHandle(BGMList::Test));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
TestScene::~TestScene()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestScene::update()
{
	mCamera.update();
	mDirectionalLight.update();
	mTestObj.update();
	mTestSky.update();
	mTestSprite.update();
	mT2.update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestScene::draw()
{
	mTestObj.draw();
}

//-------------------------------------------------------------------------------------------------
/// �`��2D
void TestScene::draw2D()
{
	mTestSprite.draw();
	mT2.draw();
}

//-------------------------------------------------------------------------------------------------
/// �w�i�`��
void TestScene::drawBackground()
{
	mTestSky.draw();
	DirectX::XMFLOAT3X3 a = {0,0,0,0,0,0,1,1,1};
	mFont.draw(TEXT("��������"),a, TEXT("���񂸂����X"));
}

} // namespace
// EOF
