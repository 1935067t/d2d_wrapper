#pragma once
#include "Direct2DWrapper.h"
namespace Wrapper {
    class Application : public Direct2DWrapper
    {
    public:

        void Start();
        void Update();
    };
}

