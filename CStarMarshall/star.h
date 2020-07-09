#pragma once

#include <cmath>
#include <vector>
//#include <Windows.h>  // not suitable for this project.

typedef unsigned long COLOR;

const double PI = std::acos(-1.0);

#define RAD(deg) deg *PI / 180.0
#define DEG(rad) rad * 180.0 / PI

#ifndef RGB
#define RGB(r, g, b)                                                \
    ((unsigned char)r | ((unsigned short)((unsigned char)g) << 8) | \
     ((unsigned long)((unsigned char)b) << 16))
#endif

template <class T>
struct TPoint
{ T x, y; };

class Star
{
   public:
    using dPoint = TPoint<double>;
    using Point  = TPoint<long>;

   private:
    COLOR color     = RGB(0, 0, 0);
    dPoint center   = {};
    dPoint velocity = {};
    double angle    = 0.0;
    double rotate   = 0.0;
    double ldist    = 0.0;
    double ratio    = 0.0;

   public:
    Star(double x, double y, double vX, double vY, double angle, double rotate, double ldistance,
         double ratio = 0.36);

    Star(COLOR color, double x, double y, double vX, double vY, double angle, double rotate,
         double ldistance, double ratio = 0.36);

    ~Star() {}

    void neg_velocity_x() { velocity.x = -velocity.x; }

    void neg_velocity_y() { velocity.y = -velocity.y; }

    void move(const double time) {
        center.x += velocity.x * time;
        center.y += velocity.y * time;
        angle += rotate * time;
        angle = fmod(angle, RAD(72.0));
    }

    double get_center_x() const { return center.x; }

    double get_center_y() const { return center.y; }

    COLOR get_color() const { return color; }

    template <typename T>
    TPoint<T> *get_tpoints() const;

    template <>
    dPoint *get_tpoints() const;

    Point *get_points() const;

    bool check_inside(dPoint point) const;
};

extern "C" {
__declspec(dllexport) Star *make_star(double x, double y, double vx, double vy, double angle,
                                      double rotate, double ldistance, double ratio = 0.36);

__declspec(dllexport) Star *make_colored_star(COLOR color, double x, double y, double vx, double vy,
                                              double angle, double rotate, double ldistance,
                                              double ratio = 0.36);

__declspec(dllexport) void delete_star(Star *p_star);

__declspec(dllexport) void star_neg_vx(Star *p_star);
__declspec(dllexport) void star_neg_vy(Star *p_star);
__declspec(dllexport) void star_move_for_time(Star *p_star, const double time);

__declspec(dllexport) double star_get_center_x(const Star *const p_star);
__declspec(dllexport) double star_get_center_y(const Star *const p_star);
__declspec(dllexport) COLOR star_get_color(const Star *const p_star);
__declspec(dllexport) Star::Point *star_get_points(const Star *const p_star);

__declspec(dllexport) bool star_check_inside(const Star *const p_star, double x, double y);
}