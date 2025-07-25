#include "render.h"

float vec_len(t_vector v)
{
  return (sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

float vec_dot(t_vector v1, t_vector v2)
{
  return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector  vec_cross(t_vector v1, t_vector v2)
{
  t_vector  new;

  new.x = (v1.y * v2.z) - (v1.z * v2.y);
  new.y = (v1.z * v2.x) - (v1.x * v2.z);
  new.z = (v1.x * v2.y) - (v1.y * v2.x);
  return (new);
}

t_vector  vec_normalize(t_vector v)
{
  t_vector  new;
  float length;

  length = vec_len(v);
  if (length == 0.0f)
  {
    new.x = 0;
    new.y = 0;
    new.z = 0;
    return (new);
  }
  new = vec_scalar_div(v, length);
  return (new);
}

t_vector  vec_negate(t_vector v)
{
  t_vector new;

  new.x = -v.x;
  new.y = -v.y;
  new.z = -v.z;
  return (new);
}

t_vector  vec_reflect(t_vector v, t_vector n)
{
  float d;

  d = vec_dot(v, n);
  return (vec_sub(v, vec_scalar_mult(n, 2.0f * d)));
}

t_vector  vec_clamp(t_vector v, float min, float max)
{
  t_vector  new;

  new.x = fminf(fmaxf(v.x, min), max);
  new.y = fminf(fmaxf(v.y, min), max);
  new.z = fminf(fmaxf(v.z, min), max);
  return (new);
}
