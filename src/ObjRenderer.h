#pragma once

//-------------------------------------------------------------------------------------------------
#include <D3D11.h>
#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// .obj�t�@�C���`��N���X
class ObjRenderer
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ObjRenderer();
	~ObjRenderer();
	//@}

	void initialize();
	void render(Transform aTransform);

private:
	

};

} // namespace
// EOF
