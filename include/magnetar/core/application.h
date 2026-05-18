#pragma once
#include <vector>
#include "magnetar/core/base.h"

namespace magnetar
{
    class MAGNETAR_API Application
    {
    public:
        Application(int argc, char** argv);

        static int runApp(int argc, char** argv);

    private:
        std::vector<std::string> m_command_line_args;

        int run();
    };
}