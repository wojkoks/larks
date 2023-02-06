// #include "raylib.h"
// #include "objects.h"
// int main(void)
// {
//     static int Width = 1920/2;
//     static int Height = 1080/2;
//     InitWindow(Width, Height, "advanced");

//     bool drawing = false;
//     bool Vdrawing = false;

//     Vector2 mousePos[2];

//     //spawn a circle which we will control!
//     circle C1({(float)Width/2, (float)Height/2,}, {0,0}, WHITE, 20);

//     SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//     //---------------------------------------------------------------------------------------

//     // Main game loop
//     while (!WindowShouldClose())    // Detect window close button or ESC key
//     {
//         // Detect if we are clicking currently
//         if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
//             drawing = true;
//             mousePos[0] = GetMousePosition();
            
//             // Let's see if we are clicking on our ball, if yes - Vdrawing = true
//             if (C1.isClicked(GetMousePosition(), drawing, 10.0f)) Vdrawing = true;
//         }

//         if (drawing) mousePos[1] = GetMousePosition();

//                 // If we release LMB
//         if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
//             drawing = false;
//                 // If we were holding the ball - calculate it's  velocity!
//             if (Vdrawing) {
//                 C1.velocity.x = 0;
//                 C1.velocity.y = 0;
//                 C1.velocityUpdate(mousePos[0], math::getLineMax(mousePos[0], mousePos[1]));
//                 Vdrawing = false;
//             }
//         }

//         if (!Vdrawing) {
//             //C1.velocityUpdateOnGravityPull(C1.position, {(float)Width/2, (float)Height/2}, 32, 32);
//             C1.velocityUpdate(GetFrameTime());
//             C1.positionUpdate();
//         }
        
//         preventClipping(&C1, checkWindowBorderCollision(&C1, Width, Height), Width, Height);

//         BeginDrawing();

//         ClearBackground(DARKBLUE);
//         if (drawing) DrawLineV(mousePos[0], math::getLineMax(mousePos[0], mousePos[1]), WHITE);
//         if (drawing) {
//             //std::cout << "M0x: " << mousePos[0].x << " M0y: " << mousePos[0].y << " M1x: " << mousePos[1].x << " M1y: " << mousePos[1].y << std::endl;
//         }
//         DrawCircleV(C1.position, C1.radius, C1.color);
//         EndDrawing();
//         //----------------------------------------------------------------------------------
//     }
//     // De-Initialization
//     //--------------------------------------------------------------------------------------
//     CloseWindow();        // Close window and OpenGL context
//     //--------------------------------------------------------------------------------------
//     char c;
//     std::cin >> c;
//     return 0;
// }

#include "raylib.h"
#include "objects.h"
#include <iostream>

Vector2 rotateA_aroundR_byB(Vector2 A, Vector2 R, float B) {
    float sinB = std::sin(B);
    float cosB = std::cos(B);
    Vector2 aux = {A.x-R.x, A.y-R.y};
    A.x = (aux.x*cosB - aux.y*sinB)+R.x;
    A.y = (aux.y*cosB + aux.x*sinB)+R.y;
    return A;
}

int main(void) {

    static int WIN_HEIGHT = 1080/2;
    static int WIN_WIDTH = 1920/2;
    float distance_from_center_of_screen = 100;

    float degreesPerFrame = 1.5;
    double degree = 0.0;
    const int FPS = 60;
    Vector2 pointOfRotation = {WIN_WIDTH/2, WIN_HEIGHT/2};

    Vector2 A = {pointOfRotation.x-distance_from_center_of_screen, pointOfRotation.y-distance_from_center_of_screen};
    Vector2 B = {A.x-distance_from_center_of_screen, A.y};
    Vector2 C = {B.x, B.y-distance_from_center_of_screen};
    Vector2 D = {C.x+distance_from_center_of_screen, C.y};
    Vector2 arr[4] = {A, B, C, D};
    math::rectangle tommy(arr);

    Vector2 a_cpy;

    InitWindow(WIN_WIDTH, WIN_HEIGHT, "WINDOW_TITLE");

    SetTargetFPS(FPS);

    while(!WindowShouldClose()) {

        a_cpy = rotateA_aroundR_byB(A, pointOfRotation, degree);

        degree=degree+(PI/180);
        if (degree>2*PI) degree = degree - 2*PI;

        std::string len = "LEN="+std::to_string(getDistanceV(a_cpy, pointOfRotation));
        std::string result = "SIN_SQ+COS_SQ="+std::to_string(sin(degree)*sin(degree)+cos(degree)*cos(degree));
        std::string deg = "DEG="+std::to_string(180*degree/PI);
        
        // rotateA_aroundR_byB(A, pointOfRotation, PI/180*degreesPerFrame);
        // rotateA_aroundR_byB(B, pointOfRotation, PI/180*degreesPerFrame);
        // rotateA_aroundR_byB(C, pointOfRotation, PI/180*degreesPerFrame);
        // rotateA_aroundR_byB(D, pointOfRotation, PI/180*degreesPerFrame);
        tommy.rotate(pointOfRotation, PI/180*degreesPerFrame);
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawLineV(tommy.points[0], tommy.points[1], WHITE);
            DrawLineV(tommy.points[1], tommy.points[2], WHITE);
            DrawLineV(tommy.points[2], tommy.points[3], WHITE);
            DrawLineV(tommy.points[3], tommy.points[0], WHITE);
           // DrawLineV(a_cpy, pointOfRotation, WHITE);
           // DrawLineV(A, pointOfRotation, RED);
            DrawText(result.c_str(), 0, 0, 10, WHITE);
            DrawText(deg.c_str(), 0, 10, 10, WHITE);
            DrawText(len.c_str(), 0, 20, 10, WHITE);
        EndDrawing();
    }

    return 0;
}

