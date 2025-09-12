#include <Windows.h>

LRESULT CustomWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    switch(uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(69);
        break;
    case WM_KEYDOWN:
        if(wParam == 'F') {
            SetWindowTextA(hWnd, "F");
        }
    default:
        return DefWindowProcA(hWnd, uMsg, wParam, lParam);
    }

}
BOOL TranslateMessage(MSG *lpMsg) {};
LRESULT DispatchMessage(MSG *lpMsg) {};

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPWSTR lpCmdLine, int nCmdShow) {
  WNDCLASS wc = {0};
  LPCSTR className = "E11 Window Class";
  LPCWSTR classNameL = L"E11 Window Class";

  wc.lpfnWndProc = CustomWindowProc;
  wc.hInstance = hInstance;
  wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wc.lpszClassName = className;
  wc.hCursor = 0;
  wc.hIcon = 0;
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;

  RegisterClassA(&wc);
  HWND hWnd =
      CreateWindowExW(WS_OVERLAPPED | WS_MINIMIZEBOX, classNameL, "E11 Window",
                      0, 200, 200, 400, 400, nullptr, 0, hInstance, 0);
  ShowWindow(hWnd, SW_SHOW);

  MSG msg;
  BOOL result;
  while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  if (result == -1) {
    return -1;
  } else {
    return msg.wParam;
  }

  return 0;
}
