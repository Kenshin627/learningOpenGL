#pragma once

namespace test
{
	class Test
	{
	private:
	public:
		Test() {};
		virtual~Test() {};
		virtual void onUpdate(float detaTIme) {};
		virtual void onRender() {};
		virtual void onImGuiRender() {};
	};
}