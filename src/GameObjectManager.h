#pragma once

//-------------------------------------------------------------------------------------------------
#include "ISetGameObjectList.h"

//-------------------------------------------------------------------------------------------------
#include <memory>
#include <list>
#include <map>
#include "BaseGameObject.h"
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

	/// @name �Q�[���I�u�W�F�N�g�����X�g����
	//@{
	void setGameObjectListToWorld(BaseGameObject* aObject, const int& aLayer = 0, const bool& aAlphaBlend = false) override;
	void setGameObjectListToBackground(BaseGameObject* aObject, const int& aLayer = 0) override;
	void setGameObjectListToCanvas(BaseGameObject* aObject, const int& aLayer = 0) override;
	void setCameraObject(Camera* aObject);
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