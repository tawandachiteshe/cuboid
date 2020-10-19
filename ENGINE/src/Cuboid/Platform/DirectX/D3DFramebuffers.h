#pragma once

#include "Cuboid/Renderer/FrameBuffer.h"
#include <wrl.h>
#include <d3d11.h>

//TODO dont forget to put macro guards

namespace Cuboid
{

	class D3DFramebuffers : public FrameBuffer
	{
	public:
		D3DFramebuffers(const FrameBufferSpecification& spec);
		virtual ~D3DFramebuffers();

		void Create();

	private:

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pFrameBufferTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pFrameBufferID;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetFrameBuffer;

		void Release();

		void* m_pRendererID;

		FrameBufferSpecification m_fbFrameBufferSpec;


	public:

		// Inherited via FrameBuffer
		virtual const FrameBufferSpecification& GetSpecification() const override;


		// Inherited via FrameBuffer
		virtual void Bind() const override;

		virtual void UnBind() const override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void* GetColorAttachmentRenderID() const override { return m_pRendererID; };
	};

}