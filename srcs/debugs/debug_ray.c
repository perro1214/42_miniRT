#include "miniRT.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_ray	ray = ray_init(
		vec3_init(0,0,0),
		vec3_init(1,0,0)
	);
	t_vec3 p = ray_at(ray, 5.0);
	printf("Ray at t=5.0: (%f, %f, %f)\n", p.x, p.y, p.z);
	return (0);
}
