#include "render.h"

t_ray ray_init(t_vector origin, t_vector direction, float t_max)
{
  t_ray r;

  r.origin = origin;
  r.direction = vec_normalize(direction);
  r.t_max = t_max;
  return (r);
}

t_ray     ray_init_default(t_vector origin, t_vector direction)
{
  return (ray_init(origin, direction, RAY_T_MAX));
}

t_vector  ray_at(const t_ray *r, float t)
{
  return (vec_add(r->origin, vec_scalar_mult(r->direction, t)));
}

