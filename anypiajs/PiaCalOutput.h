#pragma once

#include "PiaCalAny.h"
#include "json.hpp"
#include "WageIndNonFreeze.h"

class PiaCalOutput
{
private:
    PiaCalOutput(const PiaCalAny& piaCal);

public:
    static std::string ToJson(const PiaCalAny& piaCal);
    static void PrintPageDetails(const PiaCalAny& piaCal);
    static std::string GetWindwfallType(const PiaCalAny& piaCal);
    std::string GetPIAMethodType(const PiaMethod* pMethod);

protected:
    json::JSON GetAppInfo();
    json::JSON GetEarnings();
    json::JSON GetComputationYears();
    json::JSON GetAIME();

    json::JSON GetBenefit();
	void AddWageBenefit(json::JSON& parent, const WageInd* wageInd, const WorkerDataGeneral& workerData);


private:
    const PiaCalAny& m_piaCal;
    const WorkerDataGeneral& m_workerData;
    const PiaData& m_piaData;
    const PiaParams& m_piaParams;
	const PiaMethod* m_pMethod;
    const WageIndNonFreeze* m_pWageIndNonFreeze;
};