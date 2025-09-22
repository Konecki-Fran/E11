#pragma once

class IApp {
	class App {
		friend IApp;

		App() = default;
		~App() = default;

		App(const App&) = delete;
		App(App&&) = delete;
		App& operator=(const App&) = delete;
		App& operator=(App&&) = delete;

		int result = 0;
		bool isRunning = true;

	};

public:
	static int Start();
	static void Alert(const char* title, const char* msg);
	static void Stop() { instance->isRunning = false; }
	static bool IsRunning() { return instance->isRunning; }
	static int GetResult() { return instance->result; }
	static void CleanUp() { delete instance; }

private:
	IApp() = delete;
	~IApp() = delete;

private:
	inline static App* instance = new App();

};
