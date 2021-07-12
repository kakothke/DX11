#include "GameObjectManager.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
bool compAlphaBlendObject(BaseGameObject* aObject1, BaseGameObject* aObject2);

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
	for (const auto& layer : mWorldGameObjectList) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mWorldGameObjectList.clear();
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mWorldGameObjectListAlpha.clear();
	for (const auto& layer : mBackgroundGameObjectList) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mBackgroundGameObjectList.clear();
	for (const auto& layer : mCanvasGameObjectList) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mCanvasGameObjectList.clear();

	delete mCamera;
	mCamera = nullptr;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameObjectManager::update()
{
	if (!mCamera) {
		return;
	}

	// �w�i
	for (auto& layer : mBackgroundGameObjectList) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// �X�V
			if ((*itr)->activeSelf()) {
				(*itr)->update();
			}
			// ����
			if ((*itr)->destroyFlag()) {
				delete (*itr);
				(*itr) = nullptr;
				itr = layer.second.erase(itr);
				continue;
			}
			itr++;
		}
	}

	// ���[���h
	// �A���t�@�u�����h����
	for (auto& layer : mWorldGameObjectList) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// �X�V
			if ((*itr)->activeSelf()) {
				(*itr)->update();
			}
			// ����
			if ((*itr)->destroyFlag()) {
				delete (*itr);
				(*itr) = nullptr;
				itr = layer.second.erase(itr);
				continue;
			}
			itr++;
		}
	}
	// �A���t�@�u�����h�L��
	for (auto& layer : mWorldGameObjectListAlpha) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// �X�V
			if ((*itr)->activeSelf()) {
				(*itr)->update();
			}
			// ����
			if ((*itr)->destroyFlag()) {
				delete (*itr);
				(*itr) = nullptr;
				itr = layer.second.erase(itr);
				continue;
			}
			itr++;
		}
	}

	// �L�����o�X
	for (auto& layer : mCanvasGameObjectList) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// �X�V
			if ((*itr)->activeSelf()) {
				(*itr)->update();
			}
			// ����
			if ((*itr)->destroyFlag()) {
				delete (*itr);
				(*itr) = nullptr;
				itr = layer.second.erase(itr);
				continue;
			}
			itr++;
		}
	}

	// �J����
	mCamera->update();
	mCamera->updateConstantBuffer();
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
	D3D11->setBlendMode(Direct3D11::BlendList::Normal);
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// ���[���h
	// �A���t�@�u�����h����
	D3D11->setZBuffer(true);
	D3D11->setBlendMode(Direct3D11::BlendList::None);
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}
	// �A���t�@�u�����h�L��
	D3D11->setBlendMode(Direct3D11::BlendList::Normal);
	for (auto& layer : mWorldGameObjectListAlpha) {
		// �\�[�g
		layer.second.sort(compAlphaBlendObject);
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// �L�����o�X
	D3D11->setZBuffer(false);
	D3D11->setBlendMode(Direct3D11::BlendList::Normal);
	for (const auto& layer : mCanvasGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}

	// �J����
	D3D11->setZBuffer(true);
	D3D11->setBlendMode(Direct3D11::BlendList::None);
	mCamera->draw();
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�����X�g�ɒǉ��i���[���h��ԁj
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
/// @param aAlphaBlend �A���t�@�u�����h��K�p���邩
void GameObjectManager::setGameObjectListToWorld(BaseGameObject* aObject, const int& aLayer, const bool& aAlphaBlend)
{
	if (!aAlphaBlend) {
		// �A���t�@�u�����h����
		mWorldGameObjectList[aLayer].emplace_back(aObject);
	} else {
		// �A���t�@�u�����h�L��
		mWorldGameObjectListAlpha[aLayer].emplace_back(aObject);
	}
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�����X�g�ɒǉ��i�w�i�j
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
void GameObjectManager::setGameObjectListToBackground(BaseGameObject* aObject, const int& aLayer)
{
	mBackgroundGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�����X�g�ɒǉ��i�L�����o�X�j
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
void GameObjectManager::setGameObjectListToCanvas(BaseGameObject* aObject, const int& aLayer)
{
	mCanvasGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// �J������ݒ肷��
/// @param aObject �J�����I�u�W�F�N�g
void GameObjectManager::setCameraObject(Camera* aObject)
{
	mCamera = aObject;
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g����������i�P�́j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return �Q�[���I�u�W�F�N�g
BaseGameObject* GameObjectManager::findGameObject(const GameObjectTag& aTag)
{
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	for (const auto& layer : mCanvasGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g����������i�����j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return �Q�[���I�u�W�F�N�g
std::vector<BaseGameObject*> GameObjectManager::findGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	for (const auto& layer : mCanvasGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// �A���t�@�u�����h���K�p����Ă���I�u�W�F�N�g�̕`�揇���J��������̋������������Ƀ\�[�g����
bool compAlphaBlendObject(BaseGameObject* aObject1, BaseGameObject* aObject2)
{
	// �J��������̋������v�Z
	Vector3 cameraPos = Vector3(0.0f, 0.0f, -30.0f);
	Vector3 objPos1 = aObject1->transform().pos - aObject1->transform().localPos;
	Vector3 objPos2 = aObject2->transform().pos - aObject2->transform().localPos;
	float length1 = (cameraPos - objPos1).SqrMagnitude();
	float length2 = (cameraPos - objPos2).SqrMagnitude();

	// �J��������̋������������Ƀ\�[�g
	if (length1 > length2) {
		return true;
	}

	return false;
}

} // namespace
// EOF
