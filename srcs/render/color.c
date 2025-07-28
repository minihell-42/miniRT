#include "render.h"

t_color   color_add(t_color c1, t_color c2)
{
  t_color new;

  new.r = c1.r + c2.r;
  new.g = c1.g + c2.g;
  new.b = c1.b + c2.b;
  return (new);
}

t_color   color_mult(t_color c1, t_color c2)
{
  t_color new;

  new.r = c1.r * c2.r;
  new.g = c1.g * c2.g;
  new.b = c1.b * c2.b;
  return (new);
}

t_color   color_scalar_mult(t_color c, float scalar)
{
  t_color new;

  new.r = c.r * scalar;
  new.g = c.g * scalar;
  new.b = c.b * scalar;
  return (new);
}

t_color apply_gamma_correction(t_color c, float exposure, float gamma)
{
  t_color new;

  new.r = powf(c.r * exposure, gamma);
	new.g = powf(c.g * exposure, gamma);
	new.b = powf(c.b * exposure, gamma);
  return (new);
}