#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ���_�f�[�^�\����
struct OBJVertex
{
	/// ���_���W
	float pos[3];
	/// UV���W
	float uv[2];
	/// �@�����W
	float nor[3];
};

/// �}�e���A���f�[�^�\����
struct OBJMaterial
{
	float ambient[3];
	float diffuse[3];
	float specular[3];
};

/// OBJ�t�@�C���f�[�^�ۑ��p�\����
struct OBJData
{
	/// ���_�o�b�t�@(Shader���M�p)
	ID3D11Buffer* vertexBuffer;
	/// �C���f�b�N�X�o�b�t�@(Shader���M�p)
	std::vector<ID3D11Buffer*> indexBuffers;
	/// �C���f�b�N�X�o�b�t�@
	std::unordered_map<std::string, std::vector<UINT>> indexes;
	/// �}�e���A���f�[�^
	std::unordered_map<std::string, OBJMaterial> materials;

	/// �R���X�g���N�^
	OBJData()
		: vertexBuffer(nullptr)
		, indexBuffers()
		, indexes()
	{
		indexBuffers.clear();
		indexes.clear();
	}
	/// �f�X�g���N�^
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
		indexBuffers.clear();
		if (!indexes.empty()) {
			indexes.clear();
		}
	}
};

/// OBJ�t�@�C���ǂݍ��݃N���X
class OBJLoader : public Singleton<OBJLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	OBJLoader();
	~OBJLoader();
	//@}

	/// @name �ǂݍ��݁A�j��
	//@{
	bool load(const char* const aFileName);
	void release(const char* const aFileName);
	//@}

	/// @name OBJ�f�[�^���擾����
	//@{
	OBJData* getObjData(const char* const aFileName);
	//@}

private:
	/// @name ���������֐�
	//@{
	/// OBJ�t�@�C����ǂݍ���
	bool loadOBJFile(const char* const aFileName, std::vector<OBJVertex>& aVertexes, std::vector<std::string>& aMtlNames);
	/// �}�e���A���t�@�C����ǂݍ���
	bool loadMtlFile(const char* const aFileName, const std::vector<std::string>& aMtlNames);
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer(const char* const aFileName, const std::vector<OBJVertex>& aVertexes);
	/// �C���f�b�N�X�o�b�t�@���쐬����
	bool createIndexBuffer(const char* const aFileName);
	/// �����̕�����𐔒l�ɕϊ����č��W����push����
	void pushStoV(std::vector<std::vector<float>>& aData, const std::vector<std::string>& aStrs);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// obj�t�@�C���f�[�^
	std::unordered_map<const char*, OBJData> mOBJData;
	//@}

};

} // namespace
// EOF
