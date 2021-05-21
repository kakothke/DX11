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
	DirectX::XMFLOAT4X4 MATRIX_W;
	DirectX::XMFLOAT4X4 MATRIX_V;
	DirectX::XMFLOAT4X4 MATRIX_P;
};

// カメラ
struct CB_CAMERA
{
	DirectX::XMFLOAT4 CAMERA_POS;
	DirectX::XMFLOAT4 CAMERA_ROT;
};

// ライト
struct CB_LIGHT
{
	DirectX::XMFLOAT4 LIGHT_ROT;
	DirectX::XMFLOAT4 LIGHT_COL;
};

// マテリアル
struct CB_MATERIAL
{
	DirectX::XMFLOAT4 MATERIAL_A;
	DirectX::XMFLOAT4 MATERIAL_D;
	DirectX::XMFLOAT4 MATERIAL_S;
};

struct CB_Data
{
	CB_MATRIX matrix;
	CB_CAMERA camera;
	CB_LIGHT light;
	CB_MATERIAL material;
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
	void setMatrixP(const float aFov, const float aNear, const float aFar);
	void updateMatrix();
	void updateCamera(const Transform& aTransform);
	void updateLight(const Vector3& aRot, const DirectX::XMFLOAT4& aCol);
	void updateMaterial(const OBJMaterial& aMaterial);

private:
	ID3D11Buffer* mBufferMatrix;
	ID3D11Buffer* mBufferCamera;
	ID3D11Buffer* mBufferLight;
	ID3D11Buffer* mBufferMaterial;
	CB_Data mData;

};

} // namespace
// EOF
