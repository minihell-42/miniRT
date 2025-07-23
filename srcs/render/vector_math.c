#include "render.h"

t_vector  vec_add(t_vector v1, t_vector v2)
{
  t_vector new;

  new.x = v1.x + v2.x;
  new.y = v1.y + v2.y;
  new.z = v1.z + v2.z;
  return (new);
}

t_vector  vec_sub(t_vector v1, t_vector v2)
{
  t_vector new;

  new.x = v1.x - v2.x;
  new.y = v1.y - v2.y;
  new.z = v1.z - v2.z;
  return (new);
}

t_vector  vec_mult(t_vector v1, t_vector v2)
{
  t_vector new;

  new.x = v1.x * v2.x;
  new.y = v1.y * v2.y;
  new.z = v1.z * v2.z;
  return (new);
}

t_vector  vec_scalar_mult(t_vector v, float scalar)
{
  t_vector new;

  new.x = v.x * scalar;
  new.y = v.y * scalar;
  new.z = v.z * scalar;
  return (new);
}

t_vector  vec_div(t_vector v1, t_vector v2)
{
  t_vector new;

  new.x = v1.x / v2.x;
  new.y = v1.y / v2.y;
  new.z = v1.z / v2.z;
  return (new);
}

t_vector  vec_scalar_div(t_vector v, float scalar)
{
  t_vector new;

  new.x = v.x / scalar;
  new.y = v.y / scalar;
  new.z = v.z / scalar;
  return (new);
}