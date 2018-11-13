#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable {
    public: 
        sphere() {}
        sphere(vec3 cen, float r) : center(cen), radius(r) {};
        virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
        vec3 center;
        float radius;
};

bool sphere::hit(const ray &r, float tmin, float tmax, hit_record &rec) const {
    // second grade equation variables
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius; 

    // simplified cancelling two's from the original equation
    float discriminant = b*b - a*c;

    if (discriminant > 0 ) {
        float temp = (-b - sqrt(b*b-a*c))/a;
        
        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.point = r.point_at_parameter(rec.t);
            rec.normal = (rec.point - center) / radius;
            return true;
        }

        temp = (-b + sqrt(b*b-a*c)) / a;

        if(temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.point = r.point_at_parameter(rec.t);

            // normal's magnitud and radius magnitud is the same so
            //  this makes the normal a unit vector.
            rec.normal = (rec.point - center) / radius;
            return true;
        }
    }

    return false;
}

#endif