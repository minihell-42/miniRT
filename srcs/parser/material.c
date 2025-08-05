#include "miniRT.h"
#include "render.h"

t_material  build_material(t_color color)
{
  t_material mat;
  t_vector  byte_col;

  byte_col = convert_col_vec(color);
  mat.diffuse = vec_scalar_div(byte_col, 255.0f);
  mat.specular = (t_vector){1.0f, 1.0f, 1.0f};
  mat.shininess = SHININESS;
  return (mat);
}