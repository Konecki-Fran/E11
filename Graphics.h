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
	Graphics();
	~Graphics();

	Graphics(const Graphics&) = delete;
	Graphics(Graphics&&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	Graphics& operator=(Graphics&&) = delete;

	void DrawTestTriangle()
	{
		namespace wrl = Microsoft::WRL;

		struct Vertex { float x, y; };
		const Vertex vertices[]{ {0.f, .5f},{.5f, -.5f},{-.5f, -.5f} };

		wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
		D3D11_BUFFER_DESC vbDesc{};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.Usage = D3D11_USAGE_DEFAULT;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.ByteWidth = sizeof(vertices);
		vbDesc.StructureByteStride = sizeof(Vertex);

		D3D11_SUBRESOURCE_DATA sRsrcDataDesc{};
		sRsrcDataDesc.pSysMem = vertices;

		// Should be wrapped for error checking
		pDevice->CreateBuffer(&vbDesc, &sRsrcDataDesc, &pVertexBuffer);

		const UINT strides[]{ sizeof(Vertex) };
		const UINT offsets[]{ 0 };

		pDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, strides, offsets);

		pDeviceContext->Draw(3, 0);
	}

	void EndFrame(HWND);
	void ClearRTV(Color);

private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice; // allocate shit
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext; // issue draw calls
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRTV;
};