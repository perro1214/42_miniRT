#include "miniRT.h"

void    test_intersection(void)
{
    // 球のテスト
    t_sphere sp;
    sp.center = vec3_init(0, 0, 5);
    sp.radius = 1.0;

    t_ray ray = ray_init(
        vec3_init(0, 0, 0),
        vec3_init(0, 0, 1)
    );

    double t = hit_sphere(&sp, ray);
    printf("Sphere hit at t=%.2f\n", t);
    // → 期待値: t=4.0 (中心5、半径1なので 5-1=4)

    // 平面のテスト
    t_plane pl;
    pl.point = vec3_init(0, -1, 0);
    pl.normal = vec3_init(0, 1, 0);

    t_ray ray2 = ray_init(
        vec3_init(0, 0, 0),
        vec3_init(0, -1, 0)
    );

    t = hit_plane(&pl, ray2);
    printf("Plane hit at t=%.2f\n", t);
    // → 期待値: t=1.0
}

int     main(void)
{
	test_intersection();
	return (0);
}
