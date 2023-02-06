#include "raylib.h"
#include "objects.h"
#include "mathematics.h"
#include <iostream>
object::object(Vector2 pos, Vector2 vel, Color clr) {
    position = pos;
    velocity = vel;
    color = clr;
} 

circle::circle(Vector2 pos, Vector2 vel, Color clr, float radius) {
    position = pos;
    velocity = vel;
    color = clr;
    bounceDampening = 0.1f;
    active = false;
    this->radius=radius;
}

void object::velocityUpdate(float deltaTime) {
    velocity.y+=deltaTime*GRAVITY;
    return;
}

void object::velocityUpdate(Vector2 A, Vector2 B, float vMax, float MAX_DISTANCE) {
    float Dx = (A.x-B.x);
    float Dy = (A.y-B.y);
    //std::cout << "Dx: " << Dx << " Dy: " << Dy << std::endl;
    float scalar = 0.5*getDistanceV(A, B) / MAX_DISTANCE;
    //std::cout << "Scalar: " << scalar << std::endl;
    float Vx = Dx * scalar;
    float Vy = Dy * scalar;
    velocity.x-=Vx;
    velocity.y-=Vy;
    //std::cout << "Vx: " << Vx << " Vy: " << Vy << std::endl;
    return;
}

void object::positionUpdate(void) {
    position.x+=velocity.x;
    position.y+=velocity.y;
    return;
}

bool circle::isClicked(Vector2 mousePos, bool LMB_ON, float hitBox) {
    //we check if we're clicking on the circle - we can also expand or shrink the hitbox in the following range: [-radius .. float upper limit]
    if (hitBox < (-1*radius)) hitBox = (-1)*radius;
    if (getDistanceV(this->position, mousePos)<=(radius + hitBox) && LMB_ON==true) return true;
    return false;
}

void circle::velocityUpdateOnGravityPull(Vector2 CoordM1, Vector2 CoordM2, float M1, float M2) {
    float r = getDistanceV(CoordM1, CoordM2);
    float F = gravityForce(M1, M2, r);
    float Vx, Vy;
    std::cout << "F: " << F << std::endl;
    Vector2 forceEndCoords = math::getLineMax(CoordM1, CoordM2, F);
    std::cout << "posX: " << position.x << " posY: " << position.y << std::endl;
    std::cout << "FECX: " << forceEndCoords.x << " FECY: " << forceEndCoords.y << std::endl;
    Vx = abs(position.x - forceEndCoords.x);
    Vy = abs(position.y - forceEndCoords.y);

    this->velocity.x-=Vx;
    this->velocity.y-=Vy;
    
    std::cout << "Vx: " << Vx << " Vy: " << Vy << std::endl;
    return;
}

int checkWindowBorderCollision(circle *circle, int W, int H) {
    /*Return values:
    0 - No collision
    1 - Ceiling collision
    2 - Right side collision
    3 - Floor collision
    4 - Left side collision
    */
   //Ceiling
   if (circle->position.y<=circle->radius) return 1;
   if (circle->position.y>=H-circle->radius) return 3;
   if (circle->position.x<=circle->radius) return 4;
   if (circle->position.x>=W-circle->radius) return 2;
   return 0;
}

void preventClipping(circle* circle, int side, int W, int H) {
    //1 - Ceiling collision
    //2 - Right side collision
    //3 - Floor collision
    //4 - Left side collision
    if (side==0) return;
    if (side==1) circle->position.y = circle->radius+1;
    if (side==2) circle->position.x = W - circle->radius-1;
    if (side==3) circle->position.y = H - circle->radius-1;
    if (side==4) circle->position.x = circle->radius+1;
    if (side%2==0) onCollisionX(circle);
    else onCollisionY(circle);
    return;
}

void onCollisionX(circle* circle) {
    circle->velocity.x*=-(1-circle->bounceDampening);
}
void onCollisionY(circle* circle) {
    circle->velocity.y*=-(1-circle->bounceDampening);
}
