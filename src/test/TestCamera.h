#pragma once

#include "Test.h"

namespace test {
	class TestCamera : public test::Test
	{
	public:
		TestCamera();
		~TestCamera();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	};
}