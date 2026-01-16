#include "miniRT.h"

void	test_intersection(void)
{
	t_object	sphere_obj;
	t_object	plane_obj;
	t_ray		ray;
	t_ray		ray2;
	double		t;

	// 球のテスト (t_objectを使用)
	sphere_obj.type = SPHERE;
	sphere_obj.point = vec3_init(0, 0, 5);
	sphere_obj.data.sp.radius = 1.0;
	ray = ray_init(vec3_init(0, 0, 0), vec3_init(0, 0, 1));
	t = hit_sphere(&sphere_obj, ray);
	printf("Sphere hit at t=%.2f\n", t);
	// → 期待値: t=4.0 (中心5、半径1なので 5-1=4)

	// 平面のテスト (t_objectを使用)
	plane_obj.type = PLANE;
	plane_obj.point = vec3_init(0, -1, 0);
	plane_obj.data.pl.normal = vec3_init(0, 1, 0);
	ray2 = ray_init(vec3_init(0, 0, 0), vec3_init(0, -1, 0));
	t = hit_plane(&plane_obj, ray2);
	printf("Plane hit at t=%.2f\n", t);
	// → 期待値: t=1.0
}

int	main(void)
{
	test_intersection();
	return (0);
}
