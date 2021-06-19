#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// OBJファイル読み込みクラス
class OBJLoader : public Singleton<OBJLoader>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	OBJLoader();
	~OBJLoader();
	//@}

	/// @name 構造体
	//@{
	/// 頂点データ構造体
	struct OBJVertex
	{
		float pos[3] = {};
		float uv[2] = {};
		float nor[3] = {};
	};
	/// マテリアルデータ構造体
	struct OBJMaterial
	{
		float ambient[3] = {};
		float diffuse[3] = {};
		float specular[3] = {};
		std::string textureFileName;
	};
	/// OBJファイルデータ保存用構造体
	struct OBJData
	{
		/// 頂点バッファ(Shader送信用)
		ID3D11Buffer* vertexBuffer = nullptr;
		/// インデックスバッファ(Shader送信用)
		std::vector<ID3D11Buffer*> indexBuffers;
		/// インデックスバッファ
		std::unordered_map<std::string, std::vector<UINT>> indexes;
		/// マテリアル
		std::unordered_map<std::string, OBJMaterial> materials;
		/// デストラクタ
		~OBJData();
	};
	//@}

	/// @name 読み込み、破棄
	//@{
	bool load(const LPCSTR aFileName);
	void release(const LPCSTR aFileName);
	//@}

	/// @name アクセサ
	//@{
	/// OBJデータを取得する
	OBJData* getOBJData(const LPCSTR aFileName);
	//@}

private:
	/// @name 内部実装
	//@{
	/// メッシュを作成する
	bool createMesh(const LPCSTR aFileName, std::vector<OBJVertex>& aVertexes, std::vector<std::string>& aMtlNames);
	/// マテリアルファイルを読み込む
	bool loadMtlFile(const LPCSTR aFileName, const std::vector<std::string>& aMtlNames);
	/// 頂点バッファを作成する
	bool createVertexBuffer(const LPCSTR aFileName, const std::vector<OBJVertex>& aVertexes);
	/// インデックスバッファを作成する
	bool createIndexBuffer(const LPCSTR aFileName);
	/// 複数の文字列を数値に変換して座標情報をpushする
	void pushStoV(std::vector<std::vector<float>>& aData, const std::vector<std::string>& aStrs);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// objファイルデータ
	std::unordered_map<LPCSTR, OBJData> mOBJData;
	//@}

};

} // namespace
// EOF
