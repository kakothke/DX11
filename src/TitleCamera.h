#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseCamera.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �^�C�g���J����
class TitleCamera : public BaseCamera
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	TitleCamera();
	~TitleCamera();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:

};

} // namespace
// EOF
