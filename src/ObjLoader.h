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

/// OBJ�t�@�C���ǂݍ��݃N���X
class OBJLoader : public Singleton<OBJLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	OBJLoader();
	~OBJLoader();
	//@}

	/// @name �\����
	//@{
	/// ���_�f�[�^�\����
	struct OBJVertex
	{
		float pos[3] = {};
		float uv[2] = {};
		float nor[3] = {};
	};
	/// �}�e���A���f�[�^�\����
	struct OBJMaterial
	{
		float ambient[3] = {};
		float diffuse[3] = {};
		float specular[3] = {};
		std::string textureFileName;
	};
	/// OBJ�t�@�C���f�[�^�ۑ��p�\����
	struct OBJData
	{
		/// ���_�o�b�t�@(Shader���M�p)
		ID3D11Buffer* vertexBuffer = nullptr;
		/// �C���f�b�N�X�o�b�t�@(Shader���M�p)
		std::vector<ID3D11Buffer*> indexBuffers;
		/// �C���f�b�N�X�o�b�t�@
		std::unordered_map<std::string, std::vector<UINT>> indexes;
		/// �}�e���A��
		std::unordered_map<std::string, OBJMaterial> materials;
		/// �f�X�g���N�^
		~OBJData();
	};
	//@}

	/// @name �ǂݍ��݁A�j��
	//@{
	bool load(const LPCSTR aFileName);
	void release(const LPCSTR aFileName);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// OBJ�f�[�^���擾����
	OBJData* getOBJData(const LPCSTR aFileName);
	//@}

private:
	/// @name ��������
	//@{
	/// ���b�V�����쐬����
	bool createMesh(const LPCSTR aFileName, std::vector<OBJVertex>& aVertexes, std::vector<std::string>& aMtlNames);
	/// �}�e���A���t�@�C����ǂݍ���
	bool loadMtlFile(const LPCSTR aFileName, const std::vector<std::string>& aMtlNames);
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer(const LPCSTR aFileName, const std::vector<OBJVertex>& aVertexes);
	/// �C���f�b�N�X�o�b�t�@���쐬����
	bool createIndexBuffer(const LPCSTR aFileName);
	/// �����̕�����𐔒l�ɕϊ����č��W����push����
	void pushStoV(std::vector<std::vector<float>>& aData, const std::vector<std::string>& aStrs);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// obj�t�@�C���f�[�^
	std::unordered_map<LPCSTR, OBJData> mOBJData;
	//@}

};

} // namespace
// EOF
