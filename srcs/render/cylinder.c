#include "render.h"

// intersect one disk cap at cap_center, return t or -1
static float cap_intersect(const t_ray *ray, const t_cylinder *cy, t_vector cap_center)
{
  t_vector point;
  float denom;
  float r2;
  float t;

  denom = vec_dot(ray->direction, cy->normal);
  if (fabsf(denom) < EPSILON)
    return (-1.0f);
  t = vec_dot(vec_sub(cap_center, ray->origin), cy->normal) / denom;
  if (t <= RAY_T_MIN)
    return (-1.0f);
  point = ray_at(ray, t);
  r2 = cy->radius * cy->radius;
  if (vec_dot(vec_sub(point, cap_center), vec_sub(point, cap_center)) <= r2)
    return (t);
  return (-1.0f);
}

// Computes intersection with the infinite cylindrical side
static float  cylinder_side_intersection(const t_ray *ray, const t_cylinder *cy, float t_max)
{
  t_vector    oc;
  t_vector    dp;
  t_quadratic q;
  float       t_side;
  float       h;

  oc = vec_sub(ray->origin, cy->center);
  dp = vec_sub(ray->direction, vec_scalar_mult(cy->normal, vec_dot(ray->direction, cy->normal)));
  q.a = vec_dot(dp, dp);
  q.b = 2.0f * vec_dot(dp, vec_sub(oc, vec_scalar_mult(cy->normal, vec_dot(oc, cy->normal))));
  q.c = vec_dot(oc, oc) - (cy->radius * cy->radius);
  if (!solve_quad(&q))
    return (-1.0f);
  t_side = pick_quad_root(&q, RAY_T_MIN, t_max);
  if (t_side <= 0.0f)
    return (-1.0f);
  h = vec_dot(vec_sub(ray_at(ray, t_side), cy->center), cy->normal);
  if (h < 0.0f || h > cy->height)
    return (-1.0f);
  return (t_side);
}

// Main intersection just composes side and caps
int cylinder_intersection(t_inter *hit, const t_cylinder *cy)
{
  t_vector    top_center;
  float       t_top;
  float       t_bott;
  float       t_side;

  t_side = cylinder_side_intersect(&hit->ray, cy, hit->t);
  if (t_side > 0.0f)
    hit->t = t_side;
  t_bott = cap_intersect(&hit->ray, cy, cy->center);
  if (t_bott > 0.0f && t_bott < hit->t)
    hit->t = t_bott;
  top_center = vec_add(cy->center, vec_scalar_mult(cy->normal, cy->height));
  t_top = cap_intersect(&hit->ray, cy, top_center);
  if (t_top > 0.0f && t_top < hit->t)
    hit->t = t_top;
  return (hit->t < hit->ray.t_max);
}

t_vector  cylinder_normal(const t_cylinder *cy, t_vector hit_point)
{
  t_vector  cp;
  t_vector  proj;
  float     d;

  cp = vec_sub(hit_point, cy->center);
  d = vec_dot(cp, cy->normal);
  if (d < RAY_T_MIN)
    return(vec_negate(cy->normal));
  if (d > cy->height - RAY_T_MIN)
    return (cy->normal);
  proj = vec_scalar_mult(cy->normal, d);
  return (vec_normalize(vec_sub(cp, proj)));
}