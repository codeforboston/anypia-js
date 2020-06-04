#ifndef __ANYPIAJS_APPLICATION_H__
#define __ANYPIAJS_APPLICATION_H__

#include "age.h"
#include "anypiatestdoc.h"


class Application
{
public:
	Application();
	~Application();

	void Initialize();

	Age GetAge();
	std::string Calc();

protected:
	Age m_age;
	AnypiaTestDoc* m_pDoc;
};

#endif
