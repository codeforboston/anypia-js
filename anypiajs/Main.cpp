#include <iostream>

#include "Application.h"

//#define WEB_ASSEMBLY

#ifdef WEB_ASSEMBLY

Application* g_pApp = 0;


extern "C"
{
	void InitalizeApplication()
	{
		if (g_pApp)
		{
			std::cout << "g_pApp is already been created. InitalizeApplication exiting" << std::endl;
		}
		else
		{
			g_pApp = new Application();
			g_pApp->Initialize();
		}
	}


	const char* GetAge()
	{
		return g_pApp->GetAge().toString().c_str();
	}
}

#else

int main(int ac, char** av)
{
	Application app;
	app.Initialize();

	Age age = app.GetAge();

	std::cout << "Age: " << age.toString() << std::endl;

	system("pause");

	return 0;
}
#endif