#pragma once

#include <d3d11.h>

#include "Cuboid/Core/Core.h"

#include "DxHelper.h"

namespace Cuboid
{
	class InitializeD3Devices
	{
	protected:
		template<typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

		static InitializeD3Devices::ComPtr<ID3D11Device>			m_pDevice;
		static InitializeD3Devices::ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;
		static InitializeD3Devices::ComPtr<IDXGISwapChain>			m_pSwapChain;
		static InitializeD3Devices::ComPtr<ID3D11DeviceContext>		m_pDeviceContext;
		static InitializeD3Devices::ComPtr<ID3D11Texture2D>			m_pBackBuffer;

		bool m_bEnableVsync{ true };

	public:
		InitializeD3Devices() = default;
		void CreateRenderTarget();
		void CleanupDeviceD3D();
		void CleanupRenderTarget();

	private:
		static Cuboid::Ref<InitializeD3Devices> initDevices;


	public:

		void DestroyAll();
		~InitializeD3Devices();

		void InitD3D(HWND hwnd, uint32_t width, uint32_t height, uint32_t bpp);

		ComPtr<IDXGISwapChain> GetSwapChain() { return m_pSwapChain; }

		ComPtr<ID3D11Device> GetDevice()
		{

			return m_pDevice;

		}

		ComPtr<ID3D11DeviceContext> GetContext() { return m_pDeviceContext; }


		void Present();

		void Clear(const float(&colClear)[4]);

		static Cuboid::Ref<InitializeD3Devices> GetDevices()
		{
			return initDevices;
		}

		void SetVSync(bool enabled) { m_bEnableVsync = enabled; }

		static void Create(HWND hWnd, uint32_t width, uint32_t height);

	};

	inline Cuboid::Ref<InitializeD3Devices> GraphicsEngine()
	{
		return InitializeD3Devices::GetDevices();
	}

}