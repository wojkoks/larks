#pragma once
#include "raylib.h"
#include "mathematics.h"
#include <iostream>
class object {
    public:
        Vector2 position;
        Vector2 velocity;
        Color color;
    object(Vector2 pos = {0.0f, 0.0f}, Vector2 vel = {0.0f, 0.0f}, Color clr = WHITE);

    void velocityUpdate(float deltaTime);
    void velocityUpdate(Vector2 A, Vector2 B, float vMax = 32.0f, float MAX_DISTANCE = 100.0f);
    void positionUpdate(void);

};

class circle: public object {
    //Circle class, it has a position, velocity, color and radius!
    public:
        float radius;
        float bounceDampening;
        bool active;
        circle(Vector2 pos = {0.0f, 0.0f}, Vector2 vel = {0.0f, 0.0f}, Color clr = WHITE, float radius = 10.0f);
    bool isClicked(Vector2 mousePos, bool LMB_ON, float hitBox = 0);
    void velocityUpdateOnGravityPull(Vector2 CoordM1, Vector2 CoordM2, float M1, float M2);
};

int checkWindowBorderCollision(circle *circle, int W, int H);
void preventClipping(circle* circle, int side, int W, int H);
void onCollisionX(circle* circle);
void onCollisionY(circle* circle);