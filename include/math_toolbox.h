#pragma once

#define M_PI 3.14159F

typedef class float2
{
    public:
        float2(float _x=0, float _y=0) { x = _x; y = _y; };
        ~float2() {};
        float x = 0;
        float y = 0;
        void randomize();
}vector ;

struct float4
{
    float x;
    float y;
    float h;
    float w;
};

namespace Math
{
    float degToRadian(float angle);
    float square(float number);
    void randomize(float& f, int min, int max);
    void randomize(int& f, int min, int max);
};

namespace Vector 
{
    vector create(float x, float y);
    vector substract(vector vec1, vector vec2);
    float  length(vector vec);
    bool   compare(vector vec1, vector vec2, float epsilon);
};

class Timer 
{
    public:
        Timer(float time);
        ~Timer() {};

        void  update(float deltaTime);
        void  reset();
        void  end();
        bool  isDone() const { return m_value >= m_maxValue; }
        float get()    const { return m_value; }

    private:
        float m_value = 0.f;
        float m_maxValue = 0.f;
};

