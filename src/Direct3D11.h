#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "Singleton.h"
#include "ConstantBuffer.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "d3d11.lib")

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// Direct3D11�̊Ǘ�
class Direct3D11 : public Singleton<Direct3D11>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Direct3D11();
	~Direct3D11();
	//@}

	/// @name ����������
	//@{
	bool initialize();
	//@}

	/// @name �`��J�n/�`��I��
	//@{
	void drawStart(const float aClearCol[4]);
	void drawEnd();
	//@}

	/// @name �`��ݒ�
	//@{
	/// �V�F�[�_�[��ݒ肷��
	void setShader(const ShaderLoader::ShaderData* aShaderData);
	/// �e�N�X�`���[���Z�b�g����
	void setTexture(ID3D11ShaderResourceView* aTexture);
	/// Z�o�b�t�@��L��������
	void zBufferOn();
	/// Z�o�b�t�@�𖳌�������
	void zBufferOff();
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �f�o�C�X���擾����
	ID3D11Device* getDevice() const;
	/// �R���e�L�X�g���擾����
	ID3D11DeviceContext* getContext() const;
	/// �R���X�^���g�o�b�t�@�[���擾����
	ConstantBuffer* getConstantBuffer();
	//@}

private:
	/// @name ���������֐�
	//@{
	/// �f�o�C�X�ƃX���b�v�`�F�[�����쐬����
	bool createDeviceAndSwapChain();
	/// �����_�[�^�[�Q�b�g�r���[���쐬����
	bool createRenderTargetView();
	/// �[�x�X�e���V���r���[���쐬����
	bool createDepthAndStencil();
	/// �[�x�X�e���V���X�e�[�g���쐬����
	bool createDepthStencilState();
	/// �e�N�X�`���T���v���[���쐬����
	bool createTextureSampler();
	/// �u�����h�X�e�[�g���쐬����
	bool createBlendState();
	/// �r���[�|�[�g��ݒ肷��
	void setUpViewPort();
	/// ���X�^���C�Y��ݒ肷��
	void setUpRasterize();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �f�o�C�X�̃C���^�[�t�F�[�X
	ID3D11Device* mDevice;
	/// �R���e�L�X�g
	ID3D11DeviceContext* mContext;
	/// �X���b�v�`�F�[���̃C���^�[�t�F�[�X
	IDXGISwapChain* mSwapChain;
	/// �����_�[�^�[�Q�b�g�r���[�̃C���^�[�t�F�[�X
	ID3D11RenderTargetView* mRenderTargetViews;
	/// �[�x�X�e���V���r���[
	ID3D11DepthStencilView* mDepthStencilView;
	/// �[�x�X�e���V���r���[�𐶐�����ׂ̃e�N�X�`��
	ID3D11Texture2D* mDepthStencilTexture;
	/// �[�x�X�e���V���X�e�[�g
	ID3D11DepthStencilState* mDepthStencilState;
	ID3D11DepthStencilState* mDepthDisabledStencilState;
	/// �e�N�X�`���T���v���[
	ID3D11SamplerState* mSamplerState;
	/// �u�����h�X�e�[�g
	ID3D11BlendState* mBlendState;
	/// �R���X�^���g�o�b�t�@�[
	ConstantBuffer mConstantBuffer;
	//@}

};

} // namespace
// EOF
