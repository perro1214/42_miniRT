#include "miniRT.h"

#include <stdio.h>
void vec3_print(t_vec3 v) {
    printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}

int main(){
    t_vec3 v1 = vec3_init(1.0f, 2.0f, 3.0f);
    t_vec3 v2 = vec3_init(4.0f, 5.0f, 6.0f);
    printf("Vector v1: ");
    vec3_print(v1);
    printf("Vector v2: ");
    vec3_print(v2);

    t_vec3 v_add = vec3_add(v1, v2);
    t_vec3 v_sub = vec3_sub(v1, v2);
    t_vec3 v_cross = vec3_cross(v1, v2);
    double dot_product = vec3_dot(v1, v2);
    t_vec3 v_normalized = vec3_normalize(v1);

    printf("v1 + v2 = ");
    vec3_print(v_add);
    printf("v1 - v2 = ");
    vec3_print(v_sub);
    printf("v1 x v2 = ");
    vec3_print(v_cross);
    printf("v1 . v2 = %f\n", dot_product);
    printf("Normalized v1 = ");
    vec3_print(v_normalized);

    return 0;
}
