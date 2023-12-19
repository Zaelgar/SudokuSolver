// Jaidon van Herwaarden June 2023

#pragma once

#include "Debug.hpp"

#include <Windows.h>
#include <imgui.h>

#include <map>
#include <memory>
#include <string>

class ApplicationState;

struct AppConfig
{
	AppConfig() = default;
	AppConfig(std::wstring name)
		:appName(std::move(name))
	{}
	AppConfig(std::wstring name, uint32_t windowWidth, uint32_t windowHeight)
		:appName(std::move(name))
	{
		if (windowWidth < 800 || windowWidth > 1920)
			mWindowWidth = 1280;
		else
			mWindowWidth = windowWidth;
		if (windowHeight < 600 || windowHeight > 1080)
			mWindowHeight = 720;
		else
			mWindowHeight = windowHeight;
	}


	bool mMaximized = false;
	bool mImGuiDocking = false;

	std::wstring appName = L"APPLICATION_NAME";
	uint32_t mWindowWidth = 1920;//1280;
	uint32_t mWindowHeight = 1080;//720;
};

class Application
{
public:

	void Run(AppConfig appConfig);

	template <class StateType>
	void AddState(std::string name);

	void ChangeState(std::string name);

	ImVec2 GetWindowSize() const;

private:
	HWND* mHWND;

	AppConfig mAppConfig;
	std::map<std::string, std::unique_ptr<ApplicationState>> mApplicationStates;
	ApplicationState* mCurrentState = nullptr;
	ApplicationState* mNextState = nullptr;
};

template <class StateType>
void Application::AddState(std::string name)
{
	mApplicationStates.emplace(std::move(name), std::make_unique<StateType>());
}