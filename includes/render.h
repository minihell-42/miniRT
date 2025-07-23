#include "minirt.h"
#include <math.h>

#ifndef RENDER_H
# define RENDER_H

# ifndef M_PI
#   define M_PI 3.14159265358979323846264338327950288f
# endif

typedef struct s_vector
{
  float x;
  float y;
  float z;
}              t_vector;

typedef struct s_vector2d
{
  float u;
  float v;
}              t_vector2d;

// UTILS
float vec_len(t_vector v);
float vec_dot(t_vector v1, t_vector v2);
t_vector  vec_cross(t_vector v1, t_vector v2);
t_vector  vec_normalize(t_vector v);
t_vector  vec_negate(t_vector v);
t_vector  vec_reflect(t_vector v, t_vector n);
t_vector  vec_clamp(t_vector v, float min, float max);


// MATH
t_vector  vec_add(t_vector v1, t_vector v2);
t_vector  vec_sub(t_vector v1, t_vector v2);
t_vector  vec_mult(t_vector v1, t_vector v2);
t_vector  vec_scalar_mult(t_vector v, float scalar);
t_vector  vec_div(t_vector v1, t_vector v2);
t_vector  vec_scalar_div(t_vector v, float scalar);

#endif

