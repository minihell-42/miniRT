# include "miniRT.h"
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
	int		  	x;
	int		  	y;
	int				pixel;
	int				ir;
	int				ig;
	int				ib;
	t_ray	  	ray;
  t_inter 	hit;
  t_shape 	*curr_shape;
	t_vector	P;
	t_vector	N;
	t_vector	Ldir;
	t_vector	color;
	t_vector	base_color;
  t_vector  amb;
	float			diff;

	define_viewpt(&data->camera->view_port, data->camera->fov);
  build_orth_basis(data->camera);
	ambient_computation(data->ambient);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			normalize_coord(&data->camera->view_port, x, y);
      ray = ray_init_default(data->camera->coordinates, data->camera->normalized);
      ray.direction = vec_add(vec_add(vec_scalar_mult(data->camera->right, data->camera->view_port.u), vec_scalar_mult(data->camera->up, data->camera->view_port.v)), data->camera->normalized);
      hit = inter_init(&ray);
      curr_shape = data->shapes;
      while (curr_shape)
      {
        shape_intersect(&hit, curr_shape);
        curr_shape = curr_shape->next;
      }
			if (inter_hit(&hit))
			{
				/* Hit point & normal */
        P = inter_pos(&hit);
        N = shape_normal(hit.shape, P);
        /* Light direction (assume white light) */
        Ldir = vec_normalize(vec_sub(data->light->coordinates, P));
        diff = fmaxf(vec_dot(N, Ldir), 0.0f);
        /* Base object color in [0,255] */
        base_color = (t_vector){
          hit.color.r * data->light->ratio * diff,
          hit.color.g * data->light->ratio * diff,
          hit.color.b * data->light->ratio * diff
        };
        amb.x = (float)data->ambient->color.r;
        amb.y = (float)data->ambient->color.g;
        amb.z = (float)data->ambient->color.b;
        /* Combine ambient + diffuse */
        color = vec_add(amb, base_color);
        /* Clamp to [0,255] */
        color = vec_clamp(color, 0.0f, 255.0f);
        /* Optional gamma correction (γ = 2.2) */
        color.x = powf(color.x / 255.0f, 1.0f / 2.2f) * 255.0f;
        color.y = powf(color.y / 255.0f, 1.0f / 2.2f) * 255.0f;
        color.z = powf(color.z / 255.0f, 1.0f / 2.2f) * 255.0f;
        /* Final integer color */
        ir = (int)fminf(fmaxf(color.x, 0.0f), 255.0f);
        ig = (int)fminf(fmaxf(color.y, 0.0f), 255.0f);
        ib = (int)fminf(fmaxf(color.z, 0.0f), 255.0f);
        pixel = (ir << 16) | (ig << 8) | ib;
			}
			else
				pixel = 0x000000;
			put_pixel(data->app->image, x, y, pixel);
		}
	}
	mlx_put_image_to_window(data->app->mlx_connection, data->app->mlx_window,
      data->app->image->img_ptr, 0, 0);
}