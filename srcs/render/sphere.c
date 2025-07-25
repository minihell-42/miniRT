#include "render.h"

int sphere_intersection(t_inter *hit, const t_sphere *sp)
{
  t_vector    oc;
  t_quadratic q;
  float       t_cand;

  oc = vec_sub(hit->ray.origin, sp->center);
  q.a = vec_dot(hit->ray.direction, hit->ray.direction);
  q.b = 2.0f * vec_dot(oc, hit->ray.direction);
  q.c = vec_dot(oc, oc) - (sp->radius * sp->radius);
  if (!solve_quad(&q))
    return (0);
  t_cand = pick_quad_root(&q, RAY_T_MIN, hit->t);
  if (t_cand < 0.0f)
    return (0);
  hit->t = t_cand;
  return (1);
}

t_vector  sphere_normal(const t_sphere *sp, t_vector hit_point)
{
  return (vec_normalize(vec_sub(hit_point, sp->center)));
}
