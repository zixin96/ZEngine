#pragma once

// A helper class for calculating delta time.

namespace ZE
{
    class Timestep
    {
    public:
        Timestep(float time = 0.0f)
            : m_TimeInSeconds(time)
        {}
        float GetSeconds() const { return m_TimeInSeconds; }
        float GetMilliseconds() const { return m_TimeInSeconds * 1000.0f; }
        operator float() const { return m_TimeInSeconds; } // overloading typecasts: https://www.learncpp.com/cpp-tutorial/overloading-typecasts/

    private:
        float m_TimeInSeconds;
    };
}
