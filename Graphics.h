#pragma once

#include "WindowsFiltered.h"
#include "d3d11.h"
#include "DirectXColors.h"
#include "E11Exception.h"
#include "wrl.h"

struct Color {
	float r, g, b;
};

class Graphics {
	class Exception : public E11Exception {};

public:
	Graphics(HWND hWnd);
	~Graphics();

	Graphics(const Graphics&) = delete;
	Graphics(Graphics&&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	Graphics& operator=(Graphics&&) = delete;

	void EndFrame(HWND);
	void ClearRTV(Color);
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTV;
};