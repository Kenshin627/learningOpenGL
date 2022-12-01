#pragma once

#include "glm/glm.hpp"
#include "imgui/imgui.h"

namespace test
{
	class Test
	{
	private:
		glm::vec2 viewport;
	public:
		Test(const ImVec2& viewport) :viewport(viewport[0], viewport[1]) {}
		virtual~Test() {};
		virtual void onUpdate(float detaTIme) {};
		virtual void onRender() {};
		virtual void onImGuiRender() {};
		inline glm::vec2& getViewport() { return  viewport; }
	};
}