#include "GameObjectManager.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
bool compAlphaBlendObject(const std::shared_ptr<BaseGameObject>& aObject1, const std::shared_ptr<BaseGameObject>& aObject2);

//-------------------------------------------------------------------------------------------------
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameObjectManager::GameObjectManager()
	: mWorldGameObjectList()
	, mWorldGameObjectListAlpha()
	, mBackgroundGameObjectList()
	, mCanvasGameObjectList()
	, mCamera(nullptr)
{
	mWorldGameObjectList.clear();
	mWorldGameObjectListAlpha.clear();
	mBackgroundGameObjectList.clear();
	mCanvasGameObjectList.clear();
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
GameObjectManager::~GameObjectManager()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameObjectManager::update()
{
	if (!mCamera) {
		return;
	}

	// �w�i
	for (const auto layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->setCameraTransform(mCamera->transform());
				obj->update();
			}
		}
	}

	// ���[���h
	for (const auto layer : mWorldGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->setCameraTransform(mCamera->transform());
				obj->update();
			}
		}
	}
	for (const auto layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->setCameraTransform(mCamera->transform());
				obj->update();
			}
		}
	}

	// �L�����o�X
	for (const auto layer : mCanvasGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->setCameraTransform(mCamera->transform());
				obj->update();
			}
		}
	}

	// �J����
	mCamera->update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameObjectManager::draw()
{
	if (!mCamera) {
		return;
	}

	// �w�i
	D3D11->setZBuffer(false);
	for (const auto layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// ���[���h
	D3D11->setZBuffer(true);
	D3D11->setBlendMode(Direct3D11::BlendList::None);
	for (const auto layer : mWorldGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}
	for (auto layer : mWorldGameObjectListAlpha) {
		layer.second.sort(compAlphaBlendObject);
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// �L�����o�X
	D3D11->setZBuffer(false);
	for (const auto layer : mCanvasGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// �J����
	mCamera->draw();
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�����X�g�ɒǉ��i���[���h��ԁj
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
/// @param aAlphaBlend �A���t�@�u�����h��K�p���邩
void GameObjectManager::setGameObjectListToWorld(const std::shared_ptr<BaseGameObject>& aObject, const int& aLayer, const bool& aAlphaBlend)
{
	if (aAlphaBlend) {
		mWorldGameObjectListAlpha[aLayer].emplace_back(aObject);
	} else {
		mWorldGameObjectList[aLayer].emplace_back(aObject);
	}
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�����X�g�ɒǉ��i�w�i�j
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
void GameObjectManager::setGameObjectListToBackground(const std::shared_ptr<BaseGameObject>& aObject, const int& aLayer)
{
	mBackgroundGameObjectList[aLayer].emplace_back(aObject);
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�����X�g�ɒǉ��i�L�����o�X�j
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
void GameObjectManager::setGameObjectListToCanvas(const std::shared_ptr<BaseGameObject>& aObject, const int& aLayer)
{
	mCanvasGameObjectList[aLayer].emplace_back(aObject);
}

//-------------------------------------------------------------------------------------------------
/// �J������ݒ肷��
/// @param aObject �J�����I�u�W�F�N�g
void GameObjectManager::setCameraObject(const std::shared_ptr<Camera>& aObject)
{
	mCamera = aObject;
}

//-------------------------------------------------------------------------------------------------
/// �A���t�@�u�����h���K�p����Ă���I�u�W�F�N�g�̕`�揇���J��������̋������������Ƀ\�[�g����
bool compAlphaBlendObject(const std::shared_ptr<BaseGameObject>& aObject1, const std::shared_ptr<BaseGameObject>& aObject2)
{
	float length1 = (aObject1->cameraTransform().pos - aObject1->transform().pos).SqrMagnitude();
	float length2 = (aObject2->cameraTransform().pos - aObject2->transform().pos).SqrMagnitude();

	if (length1 > length2) {
		return true;
	}

	return false;
}

} // namespace
// EOF
