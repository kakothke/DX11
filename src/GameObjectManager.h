#pragma once

//-------------------------------------------------------------------------------------------------
#include <memory>
#include <list>
#include <unordered_map>
#include "BaseGameObject.h"
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �Q�[���I�u�W�F�N�g�}�l�[�W���[
class GameObjectManager
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

	/// @name �Q�[���I�u�W�F�N�g�����X�g�ɒǉ�����
	//@{
	void setGameObjectListToWorld(const std::shared_ptr<BaseGameObject>& aObject, const int& aLayer = 0, const bool& aAlphaBlend = false);
	void setGameObjectListToBackground(const std::shared_ptr<BaseGameObject>&, const int& aLayer = 0);
	void setGameObjectListToCanvas(const std::shared_ptr<BaseGameObject>&, const int& aLayer = 0);
	void setCameraObject(const std::shared_ptr<Camera>& aObject);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ���[���h��ԃ��X�g
	std::unordered_map<int, std::list<std::shared_ptr<BaseGameObject>>> mWorldGameObjectList;
	/// ���ߗL�胏�[���h��ԃ��X�g
	std::unordered_map<int, std::list<std::shared_ptr<BaseGameObject>>> mWorldGameObjectListAlpha;
	/// �w�i���X�g
	std::unordered_map<int, std::list<std::shared_ptr<BaseGameObject>>> mBackgroundGameObjectList;
	/// �L�����o�X���X�g
	std::unordered_map<int, std::list<std::shared_ptr<BaseGameObject>>> mCanvasGameObjectList;
	/// �J�������X�g
	std::shared_ptr<Camera> mCamera;
	//@}

};

} // namespace
// EOF