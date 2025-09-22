#include "WindowsFiltered.h"
#include "App.h"
#include "E11Exception.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, int nCmdShow) {

	try {
		IApp::Start();
	}
	catch (E11Exception e) {
		IApp::Alert("E11Exception", e.what());
	}
	catch (std::exception e) {
		IApp::Alert("Std exception", e.what());
	}
	catch (...) {
		IApp::Alert("Unknown exception", "No details available");
	}

	IApp::CleanUp();
	return 0;
}
