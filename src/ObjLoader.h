#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 頂点データ構造体
struct OBJVertex
{
	float pos[3];
	float uv[2];
	float nor[3];

	OBJVertex()
		: pos{ 0,0,0 }
		, uv{ 0,0 }
		, nor{ 0,0,0 }
	{
	}
};

/// マテリアルデータ構造体
struct OBJMaterial
{
	float ambient[3];
	float diffuse[3];
	float specular[3];
	std::string textureFileName;

	OBJMaterial()
		: ambient{ 0,0,0 }
		, diffuse{ 0,0,0 }
		, specular{ 0,0,0 }
		, textureFileName()
	{
	}
};

/// OBJファイルデータ保存用構造体
struct OBJData
{
	/// 頂点バッファ(Shader送信用)
	ID3D11Buffer* vertexBuffer;
	/// インデックスバッファ(Shader送信用)
	std::vector<ID3D11Buffer*> indexBuffers;
	/// インデックスバッファ
	std::unordered_map<std::string, std::vector<UINT>> indexes;
	/// マテリアル
	std::unordered_map<std::string, OBJMaterial> materials;

	/// コンストラクタ
	OBJData()
		: vertexBuffer(nullptr)
		, indexBuffers()
		, indexes()
	{
		indexBuffers.clear();
		indexes.clear();
	}
	/// デストラクタ
	~OBJData()
	{
		if (vertexBuffer) {
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}
		for (auto buffer : indexBuffers) {
			buffer->Release();
			buffer = nullptr;
		}
		if (!indexes.empty()) {
			indexes.clear();
		}
	}
};

/// OBJファイル読み込みクラス
class OBJLoader
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	OBJLoader();
	~OBJLoader();
	//@}

	/// @name 読み込み、破棄
	//@{
	bool load(const char* const aFileName);
	void release(const char* const aFileName);
	//@}

	/// @name OBJデータを取得する
	//@{
	OBJData* getOBJData(const char* const aFileName);
	//@}

private:
	/// @name 内部実装関数
	//@{
	/// メッシュを作成する
	bool createMesh(const char* const aFileName, std::vector<OBJVertex>& aVertexes, std::vector<std::string>& aMtlNames);
	/// マテリアルファイルを読み込む
	bool loadMtlFile(const char* const aFileName, const std::vector<std::string>& aMtlNames);
	/// 頂点バッファを作成する
	bool createVertexBuffer(const char* const aFileName, const std::vector<OBJVertex>& aVertexes);
	/// インデックスバッファを作成する
	bool createIndexBuffer(const char* const aFileName);
	/// 複数の文字列を数値に変換して座標情報をpushする
	void pushStoV(std::vector<std::vector<float>>& aData, const std::vector<std::string>& aStrs);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// objファイルデータ
	std::unordered_map<const char*, OBJData> mOBJData;
	//@}

};

} // namespace
// EOF
