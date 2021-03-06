#pragma once

#ifndef VEC3_H
#define VEC3_H



#include <cmath>
#include <iostream>



using std::sqrt;

class vec3 {
public:

    

    double e[3];
    vec3() : e{ 0,0,0 } {}
    vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    // giving operations when 2 classes of Vec3 are undergoing addtion , subtration etc.

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // for subtraction( basically we are adding a negative number)
    
    double operator[](int i) const { return e[i]; } // when a particular coordinate is asked
    
    double& operator[](int i) { return e[i]; } // when using with pointers

    vec3& operator+= (const vec3& v) { // for addtion

        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }

    vec3& operator*=(const double t) { // for multiplication

        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) { // for divisiont

        return *this *= 1 / t;

    }

    double length() const { // to get the length of the vector
        return sqrt(length_squared());
    }

    double length_squared() const { // square of each coordinate
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    inline static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

};

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

#endif // !VEC_H

// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    // if this class is asked to print( used to debug
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    // when asking the sum

    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    //when asking for subtraction

    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    //when asking for multiplicaton between 2 vec classes

    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    // when asking for muliiplication between a vec3 classs and a constant

    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    // commutative rule
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    // when asking for division
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    //dot producti
    
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    //cross product

    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    // geting the unit vector
    return v / v.length();
}



vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}
vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}
vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}
vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}