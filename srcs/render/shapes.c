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