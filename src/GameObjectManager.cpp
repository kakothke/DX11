#include "GameObjectManager.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
bool compAlphaBlendObject(BaseGameObject* aObject1, BaseGameObject* aObject2);

//-------------------------------------------------------------------------------------------------
static Vector3 gCameraPos = Vector3();

//-------------------------------------------------------------------------------------------------
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameObjectManager::GameObjectManager()
	: mWorldGameObjectList()
	, mWorldGameObjectListAlpha()
	, mBackgroundGameObjectList()
	, mCanvasGameObjectList()
	, mCameraGameObjectList()
{
	mWorldGameObjectList.clear();
	mWorldGameObjectListAlpha.clear();
	mBackgroundGameObjectList.clear();
	mCanvasGameObjectList.clear();
	mCameraGameObjectList.clear();
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
	for (const auto& layer : mCameraGameObjectList) {
		for (auto obj : layer.second) {
			delete obj;
			obj = nullptr;
		}
	}
	mCameraGameObjectList.clear();
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameObjectManager::update()
{
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
	for (auto& layer : mCameraGameObjectList) {
		for (auto itr = layer.second.begin(); itr != layer.second.end();) {
			// �X�V
			if ((*itr)->activeSelf()) {
				(*itr)->update();
				(*itr)->updateConstantBuffer();
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
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameObjectManager::draw()
{
	// �J�������Z�b�g����Ă��Ȃ���Ε`�悵�Ȃ�
	if (mCameraGameObjectList.empty()) {
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
		// �J�������牓�����Ƀ\�[�g
		gCameraPos = mCameraGameObjectList[0].front()->transform().pos + mCameraGameObjectList[0].front()->transform().localPos;
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
	for (const auto& layer : mCameraGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->activeSelf()) {
				obj->draw();
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�𐶐�����i���[���h��ԁj
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
/// @param aAlphaBlend �A���t�@�u�����h��K�p���邩
void GameObjectManager::instanceToWorld(BaseGameObject* aObject, const int& aLayer)
{
	mWorldGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�𐶐�����i���[���h���/�A���t�@�u�����h�j
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
/// @param aAlphaBlend �A���t�@�u�����h��K�p���邩
void GameObjectManager::instanceToWorldAlpha(BaseGameObject* aObject, const int& aLayer)
{
	mWorldGameObjectListAlpha[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�𐶐�����i�w�i�j
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
void GameObjectManager::instanceToBackground(BaseGameObject* aObject, const int& aLayer)
{
	mBackgroundGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�𐶐�����i�L�����o�X�j
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
void GameObjectManager::instanceToCanvas(BaseGameObject* aObject, const int& aLayer)
{
	mCanvasGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�𐶐�����i�J�����j
/// @param aObject �ǉ�����Q�[���I�u�W�F�N�g
/// @param aLayer �����������߂郌�C���[
void GameObjectManager::instanceToCamera(BaseCamera* aObject, const int& aLayer)
{
	mCameraGameObjectList[aLayer].emplace_back(aObject);
	aObject->setGameObjectList(this);
	aObject->initialize();
}

//-------------------------------------------------------------------------------------------------
/// �^�O����Q�[���I�u�W�F�N�g���ЂƂ�������i���[���h��ԁj
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
BaseGameObject* GameObjectManager::findWorldGameObject(const GameObjectTag& aTag)
{
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}	
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// �^�O����Q�[���I�u�W�F�N�g���ЂƂ�������i���[���h���/�A���t�@�u�����h�j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
BaseGameObject* GameObjectManager::findWorldGameObjectAlpha(const GameObjectTag& aTag)
{
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	return nullptr;
}


//-------------------------------------------------------------------------------------------------
/// �^�O����Q�[���I�u�W�F�N�g���ЂƂ�������i�w�i�j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
BaseGameObject* GameObjectManager::findBackgroundGameObject(const GameObjectTag& aTag)
{
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// �^�O����Q�[���I�u�W�F�N�g���ЂƂ�������i�L�����o�X�j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
BaseGameObject* GameObjectManager::findCanvasGameObject(const GameObjectTag& aTag)
{
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
/// �^�O����Q�[���I�u�W�F�N�g���ЂƂ�������i�J�����j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
BaseCamera* GameObjectManager::findCameraGameObject(const GameObjectTag& aTag)
{
	for (const auto& layer : mCameraGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				return obj;
			}
		}
	}
	return nullptr;
}

//-------------------------------------------------------------------------------------------------
/// �^�O����Q�[���I�u�W�F�N�g�𕡐���������i���[���h��ԁj
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
std::vector<BaseGameObject*> GameObjectManager::findWorldGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
	for (const auto& layer : mWorldGameObjectList) {
		for (const auto& obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// �^�O����Q�[���I�u�W�F�N�g�𕡐���������i���[���h���/�A���t�@�u�����h�j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
std::vector<BaseGameObject*> GameObjectManager::findWorldGameObjectsAlpha(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
	for (const auto& layer : mWorldGameObjectListAlpha) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// �^�O����Q�[���I�u�W�F�N�g�𕡐���������i�w�i�j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
std::vector<BaseGameObject*> GameObjectManager::findBackgroundGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
	for (const auto& layer : mBackgroundGameObjectList) {
		for (const auto obj : layer.second) {
			if (obj->tag() == aTag) {
				out.emplace_back(obj);
			}
		}
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// �^�O����Q�[���I�u�W�F�N�g�𕡐���������i�L�����o�X�j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
std::vector<BaseGameObject*> GameObjectManager::findCanvasGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseGameObject*> out = {};
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
/// �^�O����Q�[���I�u�W�F�N�g�𕡐���������i�J�����j
/// @param aTag �����������Q�[���I�u�W�F�N�g�̃^�O
/// @return ���������Q�[���I�u�W�F�N�g
std::vector<BaseCamera*> GameObjectManager::findCameraGameObjects(const GameObjectTag& aTag)
{
	std::vector<BaseCamera*> out = {};
	for (const auto& layer : mCameraGameObjectList) {
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
	Vector3 objPos1 = aObject1->transform().pos + aObject1->transform().localPos;
	Vector3 objPos2 = aObject2->transform().pos + aObject2->transform().localPos;
	float length1 = (gCameraPos - objPos1).SqrMagnitude();
	float length2 = (gCameraPos - objPos2).SqrMagnitude();

	// �J��������̋������������Ƀ\�[�g
	if (length1 > length2) {
		return true;
	}

	return false;
}

} // namespace
// EOF
