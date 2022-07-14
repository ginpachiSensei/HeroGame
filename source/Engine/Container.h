#pragma once

class Vector
{
public:
    float x, y;
    Vector(float x, float y);
    Vector(int x, int y) : x((float)x), y((float)y){};
    Vector();
};
