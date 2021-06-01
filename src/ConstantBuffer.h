#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <unordered_map>
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

/// スプライト
struct CB_SPRITE
{
	DirectX::XMFLOAT4X4 PROJ_2D;
	DirectX::XMFLOAT4 COLOR;
	DirectX::XMFLOAT4 UV_SIZE;
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
	CB_SPRITE SPRITE;
	CB_CAMERA CAMERA;
	CB_DLIGHT DLIGHT;
	CB_MATERIAL MATERIAL;
};

/// コンスタントバッファ
class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	bool create();
	void setMatrixW(const Transform& aTransform);
	void setMatrixV(const Transform& aTransform);
	void setMatrixP(const float aFov, const float aNearZ, const float aFarZ);
	void updateMatrix();
	void updateSprite();
	void updateCamera(const Transform& aTransform);
	void updateDirectionalLight(const Vector3& aRot, const DirectX::XMFLOAT4& aCol);
	void updateMaterial(const OBJMaterial& aMaterial);

private:
	enum BufferList {
		MATRIX,
		SPRITE,
		CAMERA,
		LIGHT,
		COLOR,
		MATERIAL,
	};
	std::unordered_map<int, ID3D11Buffer*> mBuffer;
	CB_DATA mData;

};

} // namespace
// EOF
