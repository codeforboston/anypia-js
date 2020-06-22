#include "Application.h"
#include "age.h"
#include "anypiabdoc.h"


const std::string strPiaDoc = "01123450020006221952\n\
031072014\n\
0619662010\n\
12   1500.00062010\n\
16Sample 20\n\
20000000000000000000000000000000000000011111110\n\
22     800.00    4100.00    4000.00    3700.00    4600.00    7300.00    9000.00   10800.00   12000.00   11700.00\n\
23   14100.00    6400.00   11600.00    5000.00       0.00       0.00       0.00       0.00       0.00       0.00\n\
24       0.00       0.00       0.00       0.00       0.00       0.00       0.00       0.00       0.00       0.00\n\
25       0.00       0.00       0.00       0.00       0.00       0.00   20000.00  104400.00  105480.00  108000.00\n\
26  113040.00  117000.00  122400.00  128160.00   35000.00\n\
95 40 40";

Application::Application()
{
	m_pDoc = new AnypiaTestDoc();
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

std::string Application::Calc()
{
	std::string strResult;

	AnypiabDoc doc;
	strResult = doc.calculate(strPiaDoc);

	//strResult = m_pDoc->calculate();

	return strResult;
}
