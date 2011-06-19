#pragma once

namespace Virgin
{
class Environment
{
private:
    Environment();  // Singleton

public:
    // Singleton Instance
    static Environment& Instance()
    {
        static Environment instance;
        return instance;
    }

private:
    
};
}
