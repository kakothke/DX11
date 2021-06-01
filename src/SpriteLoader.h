#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 頂点データ構造体
struct SpriteVertex
{
	float pos[3];
	float uv[2];
	SpriteVertex()
		: pos{ 0,0,0 }
		, uv{ 0,0 }
	{
	}
};

/// スプライトデータ構造体
struct SpriteData
{
	/// 頂点バッファ(Shader送信用)
	ID3D11Buffer* vertexBuffer;
	/// ファイル名
	const char* fileName;

	/// コンストラクタ
	SpriteData()
		: vertexBuffer(nullptr)
		, fileName("")
	{
	}
	/// デストラクタ
	~SpriteData()
	{
		if (vertexBuffer) {
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}
	}
};

/// スプライト読み込みクラス
class SpriteLoader
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	SpriteLoader();
	~SpriteLoader();
	//@}

	/// @name 読み込み、破棄
	//@{
	bool load(const char* const aFileName);
	void release(const char* const aFileName);
	//@}

	/// @name OBJデータを取得する
	//@{
	SpriteData* getSpriteData(const char* const aFileName);
	//@}

private:
	/// 頂点バッファを作成する
	bool createVertexBuffer(const char* const aFileName);
	/// メッシュを作成する
	void createMesh(const char* const aFileName, SpriteVertex* aVertexes);
	/// メッシュの大きさをテクスチャーのサイズに合わせる
	//void resizeMesh();

	/// @name プライベートメンバ変数
	//@{
	/// スプライトデータ
	std::unordered_map<const char*, SpriteData> mSpriteData;
	//@}

};

} // namespace
// EOF
