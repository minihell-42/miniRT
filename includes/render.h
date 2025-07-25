#include "minirt.h"
#include <math.h>

#ifndef RENDER_H
# define RENDER_H

# ifndef M_PI
#   define M_PI 3.14159265358979323846264338327950288f
# endif

// In order to prevent bouncing rays self-intersecting
#define RAY_T_MIN 0.0001f

// 'Infinite' distance, used as a default value
#define RAY_T_MAX 1.0e30f

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

typedef struct s_color
{
  int r;
  int g;
  int b;
}              t_color;

typedef enum  s_type
{
  SPHERE,
  PLANE,
  CYLINDER
}             t_type;

typedef struct s_shape
{
  t_type  shape_type;
  void    *object;

}              t_shape;

typedef struct s_ray
{
  float     t_max;
  t_vector  origin;
  t_vector  direction;
}              t_ray;

typedef struct s_inter
{
  float   t;
  t_ray   ray;
  t_shape *shape;
  t_color color;
}              t_inter;

// VECTOR UTILS
float     vec_len(t_vector v);
float     vec_dot(t_vector v1, t_vector v2);
t_vector  vec_cross(t_vector v1, t_vector v2);
t_vector  vec_normalize(t_vector v);
t_vector  vec_negate(t_vector v);
t_vector  vec_reflect(t_vector v, t_vector n);
t_vector  vec_clamp(t_vector v, float min, float max);


// VECTOR MATH
t_vector  vec_add(t_vector v1, t_vector v2);
t_vector  vec_sub(t_vector v1, t_vector v2);
t_vector  vec_mult(t_vector v1, t_vector v2);
t_vector  vec_scalar_mult(t_vector v, float scalar);
t_vector  vec_div(t_vector v1, t_vector v2);
t_vector  vec_scalar_div(t_vector v, float scalar);

// RAY
t_ray     ray_init(t_vector origin, t_vector direction, float t_max);
t_ray     ray_init_default(t_vector origin, t_vector direction);
t_vector  ray_at(const t_ray *r, float t);

// INTERSECTION
t_inter   inter_init(const t_ray *r);
t_vector  inter_pos(const t_inter *i);
int       inter_hit(const t_inter *i);

#endif

