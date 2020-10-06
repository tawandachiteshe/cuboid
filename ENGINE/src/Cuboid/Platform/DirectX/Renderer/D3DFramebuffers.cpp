#include "Cuboidpch.h"
#include "D3DFramebuffers.h"
#include "InitializeD3Devices.h"

namespace Cuboid
{



	D3DFramebuffers::D3DFramebuffers(const FrameBufferSpecification& spec):
		m_fbFrameBufferSpec(spec)
	{
		Create();
	}

	D3DFramebuffers::~D3DFramebuffers()
	{
	}

	void D3DFramebuffers::Create()
	{

		HRESULT hr = S_OK;

		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = m_fbFrameBufferSpec.Width;
		desc.Height = m_fbFrameBufferSpec.Height;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.MiscFlags = 0;
		desc.ArraySize = 1;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		hr = GraphicsEngine()->GetDevice()->CreateTexture2D(&desc, NULL, m_pFrameBufferTexture.GetAddressOf());

		if (FAILED(hr))
		{
			CUBOID_CORE_ERROR("COULD NOT CREATE FRAMEBUFFER TEXTURE");
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));


		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;

		hr = GraphicsEngine()->GetDevice()->CreateShaderResourceView(m_pFrameBufferTexture.Get(), &srvDesc, m_pFrameBufferID.GetAddressOf());

		m_pRendererID = m_pFrameBufferID.Get();


		if (FAILED(hr))
		{
			CUBOID_CORE_ERROR("COULD NOT CREATE FRAMEBUFFER SHADER RESOURCE");
		}

		hr = GraphicsEngine()->GetDevice()->CreateRenderTargetView(m_pFrameBufferTexture.Get(), NULL, m_pRenderTargetFrameBuffer.GetAddressOf());

		if (FAILED(hr))
		{
			CUBOID_CORE_CRITICAL("Could not create framebuffer render target view");
		}



	}

	void D3DFramebuffers::Release()
	{
		if (m_pFrameBufferTexture)
		{

			m_pFrameBufferTexture.Reset();
		}


		if (m_pFrameBufferID)
		{

			m_pFrameBufferID.Reset();
		}

		if (m_pRenderTargetFrameBuffer)
		{

			m_pRenderTargetFrameBuffer.Reset();
		}
	}

	const FrameBufferSpecification& D3DFramebuffers::GetSpecification() const
	{
	
		return m_fbFrameBufferSpec;

	}

	void D3DFramebuffers::Bind() const
	{
		GraphicsEngine()->GetContext()->ClearRenderTargetView(m_pRenderTargetFrameBuffer.Get(), m_fbFrameBufferSpec.BufferClearColor);

		GraphicsEngine()->GetContext()->OMSetRenderTargets(1, m_pRenderTargetFrameBuffer.GetAddressOf(), NULL);

	}

	void D3DFramebuffers::UnBind() const
	{
		
	}

	void D3DFramebuffers::Resize(uint32_t width, uint32_t height)
	{

		m_fbFrameBufferSpec.Width = width;
		m_fbFrameBufferSpec.Height = height;

		Release();

		Create();

	}

}