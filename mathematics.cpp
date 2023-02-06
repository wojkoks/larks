#include "mathematics.h"
#include "raylib.h"
#include <cmath>
#include <cstdarg>

namespace math {

    Vector2 getLineMax(Vector2 start, Vector2 end, float MAX_DISTANCE) {

        //if distance between two points > MAX_DISTANCE cut the line otherwise return regular end vector coords
        //if MAX_DISTANCE < 1 then theres no point in calculating this shit so also return end
        if (getDistanceV(start, end)<=MAX_DISTANCE || MAX_DISTANCE < 1) return end;
        //std::cout << start.x << " " << end.x << " " << start.y << " " << end.y << std::endl;
        double a,b;
        a = (start.y-end.y)/(start.x-end.x);
        b = start.y - (a * start.x);
        //std::cout << "a: " << a << " b: " << b << std::endl;
        //y=a*x+b we have our line equation ready

        //I have done a circle equation for our first point (x-start.x)^2 + (y-start.y)^2 = r^2 and
        //put in y=a*x+b we did earlier into it, equation when expanded turns into a regular quadratic equation
        //we solve it with delta and pick an point closer to the mouse
        //oh my fucking god
        Vector2 candidate[2];
        double DA, DB, DC;
        DA = (a*a+1);
        DB = (-2*start.x+2*a*b-2*a*start.y);
        DC = b*b+start.x*start.x+start.y*start.y-MAX_DISTANCE*MAX_DISTANCE-2*b*start.y;

        if (DA!=0) {

        double SQdelta = sqrt(DB*DB-4*DA*DC);
        candidate[0].x = (-DB-SQdelta)/(2*DA);
        candidate[1].x = (-DB+SQdelta)/(2*DA);
        candidate[0].y = a * candidate[0].x + b;
        candidate[1].y = a * candidate[1].x + b;
        double dist[2];
        for (int i = 0; i < 2; i++) {
            //dist[i] = sqrt((end.x-candidate[i].x)*(end.x-candidate[i].x)+(end.y-candidate[i].y)*(end.y-candidate[i].y));
            dist[i] = getDistanceV(end, candidate[i]);
        }
        if (dist[0]>dist[1]) return candidate[1];
        }
        if (DA==0) {
            //a linear equation
            candidate[0].x = -DC/DB;
            candidate[0].y = 0.0f;
        }
        return candidate[0];
    }

    rectangle::rectangle(Vector2 pts[4], double angle) {
        //zeroing out the center
        this->center = {0.0f, 0.0f};

        for (int i = 0; i < 4; i++) { 
            this->base_points[i] = pts[i];
            this->points[i] = pts[i];
            this->center.x += pts[i].x;
            this->center.y += pts[i].y;
        }
        //finalizing the mean x and y value of points for rectangle center
        this->center.x/=4;
        this->center.y/=4;
        this->rotatedCenter = center;
        this->angle = angle;
    }

    rectangle::rectangle(Vector2 center, double size, double angle) {
        //constructor when we want to create a square around a given point
        //
        this->center = center;
        this->base_points[0] = {center.x - size/2, center.y - size/2};  // corner top left
        this->base_points[1] = {center.x + size/2, center.y - size/2};  // corner top right
        this->base_points[2] = {center.x + size/2, center.y + size/2};  // corner bottom right
        this->base_points[3] = {center.x - size/2, center.y + size/2};  // corner bottom left
        this->angle = angle;
    }
    
    void rectangle::rotate(const Vector2 R, const double theta) {
        this->angle += theta; // updating angle by angle change
        if (this->angle > 2*PI) this->angle-=2*PI; //if our angle goes over 360 degrees/2*PI radians we reset it by 2*PI to keep calculations a little quicker i guess
        for (int i = 0; i < 4; i++) { points[i] = rotateAaroundRbyB(base_points[i], R, angle); } // rotating all original points by new angle in a loop
        // since there are 4 points in a rectangle
    }

}

float getDistanceV(Vector2 A, Vector2 B) {
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

float gravityForce(float M1, float M2, float dist) {
    if (dist==0) return 0;
    return (GRAV_CONST*M1*M2)/(dist*dist);
}

Vector2 rotateAaroundRbyB(Vector2 A, Vector2 R, double B) {
    float sinB = std::sin(B);
    float cosB = std::cos(B);
    Vector2 aux = {A.x-R.x, A.y-R.y};
    A.x = (aux.x*cosB - aux.y*sinB)+R.x;
    A.y = (aux.y*cosB + aux.x*sinB)+R.y;
    return A;
}


