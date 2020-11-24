#include "math_toolbox.h"

#include <math.h>
#include <cstdlib>

#include "game_utils.h"

namespace Math
{
    float degToRadian(float angle)
    {
        return (float) (angle * (M_PI / 180.f));
    }

    float square(float number) 
    {
        return number * number;
    }

    void randomize(float& f, int min, int max)
    {
        int range = max - min + 1;
        f = (float) (rand() % range + min);
    }

    void randomize(int& f, int min, int max)
    {
        int range = max - min + 1;
        f = (rand() % range + min);
    }
}

namespace Vector
{
    vector create(float x, float y) 
    {
        return {x, y};
    }

    float length(vector vec) 
    {
        return sqrtf(Math::square(vec.x) + Math::square(vec.y));
    }
    vector substract(vector vec1, vector vec2) 
    {
        return create(vec1.x - vec2.x, vec1.y - vec2.y);
    }

    bool compare(vector vec1, vector vec2, float epsilon)
    {
        return (vec1.x > vec2.x - epsilon && vec1.x < vec2.x + epsilon) && (vec1.y > vec2.y - epsilon && vec1.y < vec2.y + epsilon);
    }
}

void float2::randomize()
{
    x = (float) (LEFT_BORDER + rand() % ((RIGHT_BORDER + 1) - LEFT_BORDER));
    y = (float) (TOP_BORDER + rand() % ((BOT_BORDER + 1) - TOP_BORDER));
}

Timer::Timer(float time) 
{
    m_maxValue = time;
}

void Timer::reset() 
{
    m_value = 0.f;
}

void Timer::end() 
{
    m_value = 2 * m_maxValue;
}

void Timer::update(float deltaTime) 
{
    m_value += deltaTime;
}
