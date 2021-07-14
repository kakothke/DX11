#pragma once

//-------------------------------------------------------------------------------------------------
#include "ISetGameObjectList.h"

//-------------------------------------------------------------------------------------------------
#include <vector>
#include <list>
#include <map>
#include "BaseGameObject.h"
#include "GameObjectTag.h"
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �Q�[���I�u�W�F�N�g�}�l�[�W���[
class GameObjectManager : public ISetGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^ 
	//@{
	GameObjectManager();
	~GameObjectManager();
	//@}

	/// @name �X�V/�`��
	//@{
	void update();
	void draw();
	//@}

	/// @name �Q�[���I�u�W�F�N�g���X�g����
	//@{
	void instanceToWorld(BaseGameObject* aObject, const int& aLayer = 0) override;
	void instanceToWorldAlpha(BaseGameObject* aObject, const int& aLayer = 0) override;
	void instanceToBackground(BaseGameObject* aObject, const int& aLayer = 0) override;
	void instanceToCanvas(BaseGameObject* aObject, const int& aLayer = 0) override;
	void setCameraObject(Camera* aObject);
	BaseGameObject* findGameObject(const GameObjectTag& aTag) override;
	std::vector<BaseGameObject*> findGameObjects(const GameObjectTag& aTag) override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ���[���h��ԃ��X�g
	std::map<int, std::list<BaseGameObject*>> mWorldGameObjectList;
	/// ���ߗL�胏�[���h��ԃ��X�g
	std::map<int, std::list<BaseGameObject*>> mWorldGameObjectListAlpha;
	/// �w�i���X�g
	std::map<int, std::list<BaseGameObject*>> mBackgroundGameObjectList;
	/// �L�����o�X���X�g
	std::map<int, std::list<BaseGameObject*>> mCanvasGameObjectList;
	/// �J����
	Camera* mCamera;
	//@}

};

} // namespace
// EOF