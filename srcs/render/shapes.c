#include "render.h"

int shape_intersect(t_inter *hit, const t_shape *shape)
{
  int did_hit = 0;

  if (shape->shape_type == SPHERE)
    did_hit = sphere_intersection(hit, (t_sphere *)shape->object);
  else if (shape->shape_type == PLANE)
    did_hit = plane_intersection(hit, (t_plane *)shape->object);
  else
    did_hit = cylinder_intersection(hit, (t_cylinder *)shape->object);
  if (did_hit)
  {
    hit->shape = (t_shape *)shape;
    hit->color = shape->color;
  }
  return (did_hit);
}

t_vector  shape_normal(const t_shape *shape, t_vector hit_point)
{
  
  if (shape->shape_type == SPHERE)
    return sphere_normal((t_sphere *)shape->object, hit_point);
  else if (shape->shape_type == PLANE)
    return plane_normal((t_plane *)shape->object, hit_point);
  else
    return cylinder_normal((t_cylinder *)shape->object, hit_point);
  return ((t_vector){0, 0, 0});
}

void  ft_swap(float *a, float *b)
{
  float tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

int solve_quad(t_quadratic *q)
{
  float disc;

  disc = q->b * q->b - 4.0f * q->a * q->c;
  if (disc < 0.0f)
  {
    q->sol_count = 0;
    return (0);
  }
  else if (disc == 0.0f)
  {
    q->t0 = -q->b / (2.0f * q->a);
    q->t1 = q->t0;
    q->sol_count = 1; 
  }
  else
  {
    q->square = sqrtf(disc);
    q->t0 = (-q->b - q->square) / (2.0f * q->a);
    q->t1 = (-q->b + q->square) / (2.0f * q->a);
    if (q->t0 > q->t1)
      ft_swap(&q->t0, &q->t1);
    q->sol_count = 2;
  }
  return (q->sol_count);
}

float pick_quad_root(const t_quadratic *q, float t_min, float t_max)
{
  if (q->sol_count == 0)
    return (-1.0f);
  else if (q->sol_count == 1)
  {
    if (q->t0 > t_min && q->t0 < t_max)
      return (q->t0);
    else
      return (-1.0f);
  }
  if (q->t0 > t_min && q->t0 < t_max)
    return (q->t0);
  if (q->t1 > t_min && q->t1 < t_max)
    return (q->t1);
  return (-1.0f);
}