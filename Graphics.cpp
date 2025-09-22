#include "Graphics.h"
#include "winerror.h"
#include "Window.h"

namespace wrl = Microsoft::WRL;

Graphics::Graphics()
{
	D3D_FEATURE_LEVEL pFeatureLevels[] = {
		D3D_FEATURE_LEVEL_9_1,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_11_0
	};

	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = Window::GetHWnd();
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	D3D_FEATURE_LEVEL* pFeatureLevelResult = nullptr;

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		pFeatureLevels,
		6,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&pSwapChain,
		&pDevice,
		pFeatureLevelResult,
		&pDeviceContext
	);

	wrl::ComPtr<ID3D11Resource> pBB;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBB);
	pDevice->CreateRenderTargetView(pBB.Get(), nullptr, &pRTV);
};

void Graphics::ClearRTV(Color c) {
	const float color[] = { c.r, c.g, c.b, 1.f };
	pDeviceContext->ClearRenderTargetView(pRTV.Get(), color);
}

void Graphics::EndFrame(HWND hWnd) {
	HRESULT hr;
	if (FAILED(hr = pSwapChain->Present(1u, 0u)))
	{
		MessageBox(hWnd, L"Presenting failed", L"Exception Caught", 0);
	}
}

Graphics::~Graphics() {
};
