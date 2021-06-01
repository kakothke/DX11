#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include "Singleton.h"
#include "ConstantBuffer.h"
#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "D3D11.lib")

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	void drawStart();
	void drawEnd();
	//@}

	void setUpContext(const ShaderData* aShaderData);
	void setTexture(ID3D11ShaderResourceView* aTexture);

	/// @name �A�N�Z�T
	//@{
	/// �f�o�C�X��Ԃ�
	ID3D11Device* getDevice() const;
	/// �R���e�L�X�g��Ԃ�
	ID3D11DeviceContext* getContext() const;
	/// �R���X�^���g�o�b�t�@�[���Q�Ƃ���
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
	ID3D11RenderTargetView* mRenderTargetView;
	/// �[�x�X�e���V���r���[
	ID3D11DepthStencilView* mDepthStencilView;
	/// �[�x�X�e���V���r���[�𐶐�����ׂ̃e�N�X�`��
	ID3D11Texture2D* mDepthStencilTexture;
	/// �[�x�X�e���V���X�e�[�g
	ID3D11DepthStencilState* mDepthStencilState;
	/// �e�N�X�`���T���v���[
	ID3D11SamplerState* mSamplerState;
	/// �R���X�^���g�o�b�t�@�[
	ConstantBuffer mConstantBuffer;
	//@}

};

} // namespace
// EOF
