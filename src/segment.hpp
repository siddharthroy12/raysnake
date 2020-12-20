#include "constants.hpp"
#include "raylib.h"

class Segment
{
    public:
    float x = 5.0f * ((float)550/(float)ROW_COL);
    float y = 5.0f * ((float)550/(float)ROW_COL);
    Vector2 velocity = { 0.0, 0.0 };

    float height = (float)550/ROW_COL;
    float width = (float)550/ROW_COL;

};