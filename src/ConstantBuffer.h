#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <unordered_map>
#include "Transform.h"
#include "Color.h"
#include "OBJLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �R���X�^���g�o�b�t�@
class ConstantBuffer
{
private:
	/// @name �����\����
	//@{
	/// �ϊ��s��
	struct CB_MATRIX
	{
		DirectX::XMFLOAT4X4 W;
		DirectX::XMFLOAT4X4 V;
		DirectX::XMFLOAT4X4 P;
	};
	/// �X�v���C�g
	struct CB_SPRITE
	{
		DirectX::XMFLOAT4X4 MATRIX_P;
		DirectX::XMFLOAT4X4 MATRIX_W;
		DirectX::XMINT4 SPLIT = { 1, 1, 1, 1 };
	};
	/// �J����
	struct CB_CAMERA
	{
		DirectX::XMFLOAT4 POS;
	};
	/// ���C�g
	struct CB_DLIGHT
	{
		DirectX::XMFLOAT4 ANGLE;
		DirectX::XMFLOAT4 COL;
	};
	/// �J���[
	struct CB_COLOR
	{
		DirectX::XMFLOAT4 COL0;
		DirectX::XMFLOAT4 COL1;
	};
	/// �}�e���A��
	struct CB_MATERIAL
	{
		DirectX::XMFLOAT4 A;
		DirectX::XMFLOAT4 D;
		DirectX::XMFLOAT4 S;
	};
	//@}

public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ConstantBuffer();
	~ConstantBuffer();
	//@}

	/// @name ������
	//@{
	bool initialize(ID3D11Device* aDevice, ID3D11DeviceContext* aContext);
	//@}

	/// @name �R���X�^���g�o�b�t�@����
	//@{
	/// �ϊ��s��
	void setMatrixW(const Transform& aTransform);
	void setMatrixV(const Transform& aTransform);
	void setMatrixP(const float& aFov, const float& aNearZ, const float& aFarZ);
	void updateMatrix();
	/// �X�v���C�g
	void setSpriteMatrixW(const Transform& aTransform, const Vector2& aPivot);
	void setSpriteMatrixP(const Vector2& aAnchor);
	void setSpriteSplit(const Vector2& aSplit);
	void updateSprite();
	/// �J����
	void updateCamera(const Vector3& aPos);
	/// �f�B���N�V���i�����C�g
	void updateDLight(const Vector3& aAngle, const Color& aCol);
	/// �J���[
	void updateColor(const Color& aCol0, const Color& aCol1);
	/// OBJ�}�e���A��
	void updateMaterial(const OBJLoader::OBJMaterial& aMaterial);
	//@}

private:
	/// @name �����񋓌^
	//@{
	/// �R���X�^���g�o�b�t�@�̎��
	enum BufferList
	{
		MATRIX,
		SPRITE,
		CAMERA,
		DLIGHT,
		COLOR,
		MATERIAL,
	};
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* mContext;
	/// �e��R���X�^���g�o�b�t�@���܂Ƃ߂��A�z�z��
	std::unordered_map<BufferList, ID3D11Buffer*> mBuffers;
	/// �e��o�b�t�@�̍\����
	CB_MATRIX mMATRIX;
	CB_SPRITE mSPRITE;
	CB_CAMERA mCAMERA;
	CB_DLIGHT mDLIGHT;
	CB_COLOR mCOLOR;
	CB_MATERIAL mMATERIAL;
	//@}

};

} // namespace
// EOF
