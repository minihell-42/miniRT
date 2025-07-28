#include "render.h"

int plane_intersection(t_inter *hit, const t_plane *pl)
{
  float     denom;
  float     t_val;
  t_vector  diff;

  denom = vec_dot(hit->ray.direction, pl->normal);
  if (fabsf(denom) < EPSILON)
    return (0);
  diff = vec_sub(pl->point, hit->ray.origin);
  t_val = vec_dot(diff, pl->normal) / denom;
  if (t_val <= RAY_T_MIN || t_val >= hit->t)
    return (0);
  hit->t = t_val;
  return (1);
}

t_vector  plane_normal(const t_plane *pl, t_vector hit_point)
{
  (void)hit_point;
  return (pl->normal);
}