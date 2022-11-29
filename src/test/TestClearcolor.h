#pragma once

#include "Test.h"

namespace test {
	class TestClearcolor : public test::Test
	{
	public:
		TestClearcolor();
		~TestClearcolor();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}