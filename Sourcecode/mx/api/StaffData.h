// MusicXML Class Library v0.3.0
// Copyright (c) 2015 - 2016 by Matthew James Briggs

#pragma once

#include "mx/api/MeasureData.h"

#include <string>
#include <vector>

namespace mx
{
    namespace api
    {
        class StaffData
        {
        public:
            std::vector<MeasureData> measures;
        };
    }
}