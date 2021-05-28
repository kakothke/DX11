#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �S�ẴQ�[���I�u�W�F�N�g�̊��N���X
class DirectionalLight : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^
	//@{
	DirectionalLight();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}


protected:
	void updateConstantBuffer();
	DirectX::XMFLOAT4 mColor;

};

} // namespace
// EOF