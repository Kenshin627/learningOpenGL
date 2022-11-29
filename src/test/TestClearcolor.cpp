#include <GL/glew.h>
#include <imgui/imgui.h>

#include "TestClearcolor.h"

namespace test {
	TestClearcolor::TestClearcolor() :m_ClearColor{ 1.0f, 0.5f, 0.5f, 1.0f } {}
	TestClearcolor::~TestClearcolor() {}

	void TestClearcolor::onUpdate(float deltaTime) {}
	void TestClearcolor::onRender() 
	{
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearcolor::onImGuiRender()
	{
		ImGui::ColorEdit4("clearColor", m_ClearColor);
	}
}