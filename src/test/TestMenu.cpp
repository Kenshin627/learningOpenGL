#include <imgui/imgui.h>

#include "TestMenu.h"

namespace test {
	TestMenu::TestMenu(Test*& test):m_currentTest(test) {}
	TestMenu::~TestMenu() {}

	void TestMenu::onUpdate(float deltaTime) {}

	void TestMenu::onRender() 
	{
	}

	void TestMenu::onImGuiRender() 
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_currentTest = test.second();
			}
		}
	}
}