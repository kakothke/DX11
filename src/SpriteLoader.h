#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ���_�f�[�^�\����
struct SpriteVertex
{
	float pos[3] = {};
	float uv[2] = {};
};

/// �X�v���C�g�f�[�^�\����
struct SpriteData
{
	/// ���_�o�b�t�@(Shader���M�p)
	ID3D11Buffer* vertexBuffer;
	/// �t�@�C����
	const char* fileName;
	/// �f�X�g���N�^
	~SpriteData()
	{
		if (vertexBuffer) {
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}
	}
};

/// �X�v���C�g�ǂݍ��݃N���X
class SpriteLoader : public Singleton<SpriteLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	SpriteLoader();
	~SpriteLoader();
	//@}

	/// @name �ǂݍ��݁A�j��
	//@{
	bool load(const char* const aFileName);
	void release(const char* const aFileName);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �X�v���C�g�f�[�^���擾����
	SpriteData* getSpriteData(const char* const aFileName);
	//@}

private:
	/// @name ��������
	//@{
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer(const char* const aFileName);
	/// ���b�V�����쐬����
	void createMesh(const char* const aFileName, SpriteVertex* aVertexes);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �X�v���C�g�f�[�^
	std::unordered_map<const char*, SpriteData> mSpriteData;
	//@}

};

} // namespace
// EOF
