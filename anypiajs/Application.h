#ifndef __ANYPIAJS_APPLICATION_H__
#define __ANYPIAJS_APPLICATION_H__

#include "age.h"

class Application
{
public:
	Application();
	~Application();

	void Initialize();

	Age GetAge();

protected:
	Age m_age;
};

#endif
