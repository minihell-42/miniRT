#include "render.h"

t_inter   inter_init(const t_ray *r)
{
  t_inter i;

  i.ray = *r;
  i.t = r->t_max;
  i.shape = NULL;
  return (i);
}

t_vector  inter_pos(const t_inter *i)
{
  return (ray_at(&i->ray, i->t));
}

int inter_hit(const t_inter *i)
{
  return (i->shape != NULL);
}