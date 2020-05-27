#include "Application.h"
#include "age.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::Initialize()
{
	m_age = Age(75, 6);// Temp. Remove when things actually work
}

// Temp. Remove when things actually work
Age Application::GetAge()
{
	return m_age;

}

