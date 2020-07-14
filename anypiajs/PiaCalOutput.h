#pragma once

#include "PiaCalAny.h"

namespace PiaCalOutput
{
    std::string ToJson(const PiaCalAny& piaCal);

    void PrintPageDetails(const PiaCalAny& piaCal);
}