#include <string>
#include <vector>
#include <functional>

#include "Test.h"

namespace test {
	class TestMenu :public Test
	{
	private:
		Test*& m_currentTest;
		std::vector<std::pair< std::string, std::function<Test*()>>> m_Tests;
	public:
		TestMenu(Test*& test);
		~TestMenu();

		virtual void onUpdate(float deltaTime) override;
		virtual void onRender() override;
		virtual void onImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
}