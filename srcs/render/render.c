#include "render.h"

static void	put_pixel(t_image *image, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * image->length) + (x * (image->bpp / 8));
	*(unsigned int *)(image->buffer + offset) = color;
}

void  normalize_coord(t_viewpt *vp, float x, float y)
{
  vp->u = (2.0f * (x + 0.5f) / (float)WIDTH  - 1.0f) * vp->half_width;
	vp->v = (1.0f - 2.0f * (y + 0.5f) / (float)HEIGHT) * vp->half_height;
}

void	render(t_data *data)
{
	int		  x;
	int		  y;
	t_ray	  ray;
  t_inter hit;
	t_color	pixel_color;
  t_shape *curr_shape;

  // Precompute viewport dimensions */
	define_viewpt(&data->camera->view_port, data->camera->fov);
  // Build camera basis
  build_orth_basis(data->camera);
	// Loop over every pixel
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			// Compute normalized device coords [0,1] → screen coords [-1,1]
			normalize_coord(&data->camera->view_port, x, y);
			// Build ray in world space
      ray = ray_init_default(data->camera->coordinates, data->camera->normalized);
      ray.direction = vec_add(vec_add(vec_scalar_mult(data->camera->right, data->camera->view_port.u), vec_scalar_mult(data->camera->up, data->camera->view_port.v)), data->camera->normalized);
      hit = inter_init(&ray);
      curr_shape = data->shapes;
      while (curr_shape)
      {
        shape_intersect(&hit, curr_shape);
        if (inter_hit(&hit))
        {
          put_pixel(&data->app->image, x, y, 0xFFFF0000); // paint white until color and shadowing is implemented
        }
        curr_shape = curr_shape->next;
      }
		}
	}
	mlx_put_image_to_window(data->app->mlx_connection, data->app->mlw_window,
      data->app->image.img_ptr, 0, 0);
}