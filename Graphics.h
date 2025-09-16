#pragma once

#include "WindowsFiltered.h"
#include "d3d11.h"
#include "DirectXColors.h"

struct Color {
	float r, g, b;
};

class Graphics {
public:
	Graphics();
	~Graphics();

	Graphics(const Graphics&) = delete;
	Graphics(Graphics&&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	Graphics& operator=(Graphics&&) = delete;

	void EndFrame();
	void ClearRTV(Color);
private:
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;
	IDXGISwapChain* pSwapChain;
	ID3D11RenderTargetView* pRTV;
};