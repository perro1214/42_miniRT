#include "vec3.h"

t_vec3 vec3_init(float x, float y, float z) {
    t_vec3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b) {
    return vec3_init(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b) {
    return vec3_init(a.x - b.x, a.y - b.y, a.z - b.z);
}

t_vec3 vec3_scale(t_vec3 v, float scalar) {
    return vec3_init(v.x * scalar, v.y * scalar, v.z * scalar);
}

double vec3_dot(t_vec3 a, t_vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b) {
    return vec3_init(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

double vec3_norm(t_vec3 v) {
    return sqrt(vec3_dot(v, v));
}

t_vec3 vec3_normalize(t_vec3 v) {
    double norm = vec3_norm(v);
    if (norm == 0) {
        return vec3_init(0, 0, 0); //正規化できない場合はゼロベクトルを返す
    }
    return vec3_scale(v, 1.0 / norm);
}
