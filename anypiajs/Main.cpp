#include <iostream>
#include "Application.h"
#include "FormatString.h"

void AfxFormatString1(std::string& result, unsigned int rsc,
	const std::string& filler)
{
	return;
}

void AfxFormatString2(std::string& result, unsigned int rsc,
	const std::string& filler1, const std::string& filler2)
{
	return;
}

#ifdef WEB_ASSEMBLY
extern "C"
{
	Application* g_pApp = 0;


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

		std::cout << "Application Intitalized" << std::endl;
	}

	const char* GetAge()
	{
		return g_pApp->GetAge().toString().c_str();
	}

	const char* GetCalc()
	{
		return  g_pApp->Calc().c_str();
	}

	int GetYears()
	{
		int iNumYears = g_pApp->GetAge().getYears();
		std::cout << iNumYears << std::endl;
		return iNumYears;
	}
}

//
//#else
//	void InitalizeApplication();
//	const char* GetAge();
//	const char* GetCal();
#endif



#ifndef WEB_ASSEMBLY
int main(int ac, char** av)
{
	Application app;
	app.Initialize();
	std::cout << app.Calc() << std::endl;
	std::cout << "Age: " << app.GetAge().toString() << std::endl;

	system("pause");

	return 0;
}
#endif