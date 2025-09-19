#include "WindowsFiltered.h"
#include "App.h"
#include "E11Exception.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, int nCmdShow) {

	try {
		App::Start();
	}
	catch (E11Exception e) {
		App::Alert("E11Exception", e.what());
	}
	catch (std::exception e) {
		App::Alert("Std exception", e.what());
	}
	catch (...) {
		App::Alert("Unknown exception", "No details available");
	}

	return 0;
}
