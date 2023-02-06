#pragma once
#include "raylib.h"
#include <cmath>
//Default earth acceleration
#define GRAVITY 9.81
#define GRAV_CONST 6.673
namespace math {

    Vector2 getLineMax(Vector2 start, Vector2 end, float MAX_DISTANCE = 100.0f);
    class rectangle {
            public:
                Vector2 base_points[4];
                Vector2 points[4];
                Vector2 center;
                Vector2 rotatedCenter;
                //points are used for rotation, base_points are original points that only get translated (for now, unless i change it for whatever reason)
                //its just a draft idea anyway
                double angle;
                rectangle(Vector2 pts[4], double angle = 0.0);
                rectangle(Vector2 center, double size, double angle = 0.0);
                void rotate(const Vector2 R, const double theta);
        };

}

float getDistanceV(Vector2 A, Vector2 B);

float gravityForce(float M1, float M2, float dist);

Vector2 rotateAaroundRbyB(Vector2 A, Vector2 R, double B);