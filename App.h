#pragma once

class App {
public:
	static void Start();
	static void Alert(const char* title, const char* msg);

private:
	App() = default;
	~App() = default;

	App(const App&) = delete;
	App(App&&) = delete;
	App& operator=(const App&) = delete;
	App& operator=(App&&) = delete;
};