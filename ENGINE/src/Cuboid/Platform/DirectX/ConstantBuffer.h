#pragma once

#include "Cuboid/Renderer/Buffer.h"
#include <d3d11.h>
#include "InitializeD3Devices.h"

namespace Cuboid
{

	class ConstantBuffer
	{
	public:
		enum class ConstantBufferType
		{
			VERTEX_SHADER_CONSTANT_BUFFER,
			PIXEL_SHADER_CONSTANT_BUFFER
		};

	public:

		template<typename T>
		void AddConstantBuffer(const std::string& constantbuffer_name, const ConstantBufferType& type);

		template<typename T, typename Func>
		void SetConstantBufferData(const std::string& constbuffer_name, const Func& func);

		std::vector<ID3D11Buffer*>& GetVertexConstantBuffers() { return m_VertexConstantBuffers;  }
		std::vector<ID3D11Buffer*>& GetPixelConstantBuffers() { return m_PixelConstantBuffers; }

	private:

		std::unordered_map<std::string, ID3D11Buffer*> m_ConstantBufferMap;
		std::vector<ID3D11Buffer*> m_VertexConstantBuffers;
		std::vector<ID3D11Buffer*> m_PixelConstantBuffers;


	};

    template<typename T>
    inline void ConstantBuffer::AddConstantBuffer(const std::string& constantbuffer_name, const ConstantBufferType& type)
    {

        
        HRESULT hr = S_OK;

        ID3D11Buffer* buffer;

        D3D11_BUFFER_DESC desc;
        desc.ByteWidth = sizeof(T);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        hr = GraphicsEngine()->GetDevice()->CreateBuffer(&desc, NULL, &buffer);

        if (type == ConstantBufferType::VERTEX_SHADER_CONSTANT_BUFFER)
            m_VertexConstantBuffers.push_back(buffer);
        else
            m_PixelConstantBuffers.push_back(buffer);

        m_ConstantBufferMap.insert({ constantbuffer_name, buffer });
    }

    template<typename T, typename Func>
    inline void ConstantBuffer::SetConstantBufferData(const std::string& constbuffer_name, const Func& func)
    {
        
        D3D11_MAPPED_SUBRESOURCE mapped_resource;

        auto constbuffer = m_ConstantBufferMap.at(constbuffer_name);

        if (GraphicsEngine()->GetContext()->Map(constbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource) != S_OK)
            CUBOID_CORE_ERROR("FAILED TO MAP VERTEX SHADER CONSTANT BUFFER");

        T* constant_buffer = (T*)mapped_resource.pData;

        func(constant_buffer);

        GraphicsEngine()->GetContext()->Unmap(constbuffer, 0);

    }

}