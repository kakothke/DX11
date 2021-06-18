#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <unordered_map>
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
		DirectX::XMINT4 SPLIT;
	};
	/// �J����
	struct CB_CAMERA
	{
		DirectX::XMFLOAT4 POS;
		DirectX::XMFLOAT4 ROT;
	};
	/// ���C�g
	struct CB_DLIGHT
	{
		DirectX::XMFLOAT4 ROT;
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
	void setMatrixW(const DirectX::XMFLOAT3X3& aTransform);
	void setMatrixVP(const DirectX::XMFLOAT3X3& aTransform, const DirectX::XMFLOAT3& aCamera);
	void updateMatrix();
	/// �X�v���C�g
	void updateSprite(
		const DirectX::XMFLOAT3X3& aTransform,
		const DirectX::XMFLOAT2& aAnchor,
		const DirectX::XMFLOAT2& aPivot,
		const DirectX::XMINT2 aSplit
	);
	/// �J����
	void updateCamera(const DirectX::XMVECTOR& aPos, const DirectX::XMVECTOR& aRot);
	/// �f�B���N�V���i�����C�g
	void updateDLight(const DirectX::XMVECTOR& aRot, const DirectX::XMFLOAT4& aCol);
	/// �J���[
	void updateColor(const DirectX::XMFLOAT4& aCol0, const DirectX::XMFLOAT4& aCol1);
	/// OBJ�}�e���A��
	void updateMaterial(const OBJMaterial& aMaterial);
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
