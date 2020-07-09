#include "star.h"

Star::Star(double x, double y, double vx, double vy, double angle, double rotate, double ldistance,
           double ratio) {
    this->center   = {x, y};
    this->velocity = {vx, vy};
    this->angle    = RAD(fmod(angle, 72.0));
    this->rotate   = RAD(rotate);
    this->ldist    = ldistance;
    this->ratio    = ratio;
}

Star::Star(COLOR color, double x, double y, double vx, double vy, double angle, double rotate,
           double ldistance, double ratio) {
    this->color    = color;
    this->center   = {x, y};
    this->velocity = {vx, vy};
    this->angle    = RAD(fmod(angle, 72.0));
    this->rotate   = RAD(rotate);
    this->ldist    = ldistance;
    this->ratio    = ratio;
}

template <typename T>
TPoint<T> *Star::get_tpoints() const {
    TPoint<T> points[10] = {};

    for (int i = 0; i < 10; i += 2) {
        points[i] = TPoint<T>{static_cast<T>(ldist * std::cos(angle + RAD(72.0) * i) + center.x),
                              static_cast<T>(ldist * std::sin(angle + RAD(72.0) * i) + center.y)};

        points[i + 1] = TPoint<T>{
            static_cast<T>(ldist * ratio * std::cos(angle + RAD(72.0) * i + RAD(36.0)) + center.x),
            static_cast<T>(ldist * ratio * std::sin(angle + RAD(72.0) * i + RAD(36.0)) + center.y)};
    }

    return points;
}

template <>
Star::dPoint *Star::get_tpoints() const {
    dPoint points[10] = {};

    for (int i = 0; i < 10; i += 2) {
        points[i] = dPoint{ldist * std::cos(angle + RAD(72.0) * i) + center.x,
                           ldist * std::sin(angle + RAD(72.0) * i) + center.y};

        points[i + 1] =
            dPoint{ldist * ratio * std::cos(angle + RAD(72.0) * i + RAD(36.0)) + center.x,
                   ldist * ratio * std::sin(angle + RAD(72.0) * i + RAD(36.0)) + center.y};
    }

    return points;
}

Star::Point *Star::get_points() const { return this->get_tpoints<long>(); }

bool Star::check_inside(dPoint point) const {
    dPoint *polygon = this->get_tpoints<double>();
    int count       = 0;

    for (int i = 0; i < 10; i++) {
        int i_next = (i + 1) % 10;

        if ((polygon[i].y < point.y) != (polygon[i_next].y < point.y)) {
            double x = (polygon[i_next].x - polygon[i].x) * (point.y - polygon[i].y) /
                           (polygon[i_next].y - polygon[i].y) +
                       polygon[i].x;

            if (point.x < x) {
                ++count;
            }
        }
    }

    return (count % 2) > 0;
}

/* Helper function for the Class Star from here */

Star *make_star(double x, double y, double vx, double vy, double angle, double rotate,
                double ldistance, double ratio) {
    return new Star(x, y, vx, vy, angle, rotate, ldistance, ratio);
}

Star *make_colored_star(COLOR color, double x, double y, double vx, double vy, double angle,
                        double rotate, double ldistance, double ratio) {
    return new Star(color, x, y, vx, vy, angle, rotate, ldistance, ratio);
}

void delete_star(Star *p_star) { delete p_star; }

void star_neg_vx(Star *p_star) { p_star->neg_velocity_x(); }

void star_neg_vy(Star *p_star) { p_star->neg_velocity_y(); }

void star_move_for_time(Star *p_star, const double time) { p_star->move(time); }

double star_get_center_x(const Star *const p_star) { return p_star->get_center_x(); }

double star_get_center_y(const Star *const p_star) { return p_star->get_center_y(); }

COLOR star_get_color(const Star *const p_star) { return p_star->get_color(); }

Star::Point *star_get_points(const Star *const p_star) { return p_star->get_points(); }

bool star_check_inside(const Star *const p_star, double x, double y) {
    return p_star->check_inside(Star::dPoint{x, y});
}