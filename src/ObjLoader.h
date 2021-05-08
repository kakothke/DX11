#pragma once

//-------------------------------------------------------------------------------------------------
#include <D3D11.h>
#include <unordered_map>
#include "Singleton.h"
#include "Vector3.h"
#include "ObjList.h"
#include "Macros.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ���_�o�b�t�@�ۑ��p�\����
struct VertexData
{
	double position[3];
	double texture[2];
	double normal[3];
};

/// obj�t�@�C���f�[�^�ۑ��p�\����
struct ObjData
{
	/// ���_�o�b�t�@(Shader���M�p)
	ID3D11Buffer* vertexBuffer;
	/// �C���f�b�N�X�o�b�t�@(Shader���M�p)
	ID3D11Buffer* indexBuffer;
	/// ���̓��C�A�E�g
	ID3D11InputLayout* inputLayout;
	/// ���_�o�b�t�@
	std::vector<VertexData> vertexData;
	/// �C���f�b�N�X�o�b�t�@
	std::vector<UINT> indexes;

	/// �R���X�g���N�^
	ObjData()
		: vertexBuffer(nullptr)
		, indexBuffer(nullptr)
		, inputLayout(nullptr)
		, vertexData()
		, indexes()
	{
		vertexData.clear();
	}
	/// �f�X�g���N�^
	~ObjData()
	{
		if (vertexBuffer) {
			SAFE_RELEASE(vertexBuffer);
		}
		if (indexBuffer) {
			SAFE_RELEASE(indexBuffer);
		}
		if (inputLayout) {
			SAFE_RELEASE(inputLayout);
		}
	}
};

/// obj�t�@�C���ǂݍ��݃N���X
class ObjLoader : public Singleton<ObjLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ObjLoader();
	~ObjLoader();
	//@}

	/// @name �ǂݍ��݁A�j��
	//@{
	bool load(ObjList aObjList);
	void release(ObjList aObjList);
	//@}

	/// @name �ǂݍ���obj�f�[�^��Ԃ�
	//@{
	const ObjData& objData(ObjList aObjList);
	//@}

private:
	/// @name ���������֐�
	//@{
	/// ���b�V�����쐬����
	bool createMesh(ObjList aObjList);
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer();
	/// �C���f�b�N�X�o�b�t�@���쐬����
	bool createIndexBuffer();
	/// �������float�^�ɕϊ�����vector��push����
	template <typename T>
	void pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// obj�t�@�C���f�[�^
	std::unordered_map<ObjList, ObjData> mObjData;
	//@}

};

} // namespace
// EOF
