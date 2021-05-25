#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "Singleton.h"
#include "Transform.h"
#include "OBJLoader.h"

namespace DX11 {

/// 行列
struct CB_MATRIX
{
	DirectX::XMFLOAT4X4 W;
	DirectX::XMFLOAT4X4 V;
	DirectX::XMFLOAT4X4 P;
};

// カメラ
struct CB_CAMERA
{
	DirectX::XMFLOAT4 POS;
	DirectX::XMFLOAT4 ROT;
};

// ライト
struct CB_DLIGHT
{
	DirectX::XMFLOAT4 ROT;
	DirectX::XMFLOAT4 COL;
};

// マテリアル
struct CB_MATERIAL
{
	DirectX::XMFLOAT4 A;
	DirectX::XMFLOAT4 D;
	DirectX::XMFLOAT4 S;
};

struct CB_DATA
{
	CB_MATRIX MATRIX;
	CB_CAMERA CAMERA;
	CB_DLIGHT DLIGHT;
	CB_MATERIAL MATERIAL;
};

/// コンスタントバッファ
class ConstantBuffer : public Singleton<ConstantBuffer>
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	bool create();
	void setMatrixW(const Transform& aTransform);
	void setMatrixV(const Transform& aTransform);
	void setMatrixP(const float aFov, const float aNearZ, const float aFarZ);
	void updateMatrix();
	void updateCamera(const Transform& aTransform);
	void updateDirectionalLight(const Vector3& aRot, const DirectX::XMFLOAT4& aCol);
	void updateMaterial(const OBJMaterial& aMaterial);

private:
	ID3D11Buffer* mBufferMatrix;
	ID3D11Buffer* mBufferCamera;
	ID3D11Buffer* mBufferLight;
	ID3D11Buffer* mBufferMaterial;
	CB_DATA mData;

};

} // namespace
// EOF
