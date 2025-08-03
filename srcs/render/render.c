#include "miniRT.h"
#include "render.h"

static void	put_pixel(t_image *image, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * image->length) + (x * (image->bpp / 8));
	*(unsigned int *)(image->buffer + offset) = color;
}

void	normalize_coord(t_viewpt *vp, float x, float y)
{
	vp->u = (2.0f * (x + 0.5f) / (float)WIDTH - 1.0f) * vp->half_width;
	vp->v = (1.0f - 2.0f * (y + 0.5f) / (float)HEIGHT) * vp->half_height;
}

void	render(t_data *data)
{
	int x;
	int y;
	int pixel;
	t_ray ray;
	t_inter hit;

	define_viewpt(&data->camera->view_port, data->camera->fov);
	build_orth_basis(data->camera);
	ambient_computation(data->ambient);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray = generate_ray(data->camera, &data->camera->view_port, x, y);
			hit = cast_ray(&ray, data->shapes);
			pixel = shade_pixel(&hit, data);
			put_pixel(data->app->image, x, y, pixel);
		}
	}
	mlx_put_image_to_window(data->app->mlx_connection, data->app->mlx_window,
		data->app->image->img_ptr, 0, 0);
}