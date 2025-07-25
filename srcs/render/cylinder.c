#include "render.h"

int cylinder_intersection(t_inter *hit, const t_cylinder *cy);

t_vector  cylinder_normal(const t_cylinder *cy, t_vector hit_point)
{
  t_vector  ca;
  t_vector  v;
  t_vector  proj;
  float     d;

  ca = cy->normal;
  v = vec_sub(hit_point, cy->center);
  d = vec_dot(v, ca);
  if (d < RAY_T_MIN)
    return(vec_negate(ca));
  if (d > cy->height - RAY_T_MIN)
    return (ca);
  proj = vec_scalar_mult(ca, d);
  return (vec_normalize(vec_sub(v, proj)));
}