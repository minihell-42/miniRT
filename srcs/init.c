#include "miniRT.h"


int	init_mlx(t_app *app)
{
	app->mlx_connection = mlx_init();
	if (app->mlx_connection == NULL)
		return(0);
	app->mlw_window = mlx_new_window(app->mlx_connection, WIDTH, HEIGHT, "MiniRT");
	if (app->mlw_window == NULL)
	{
		mlx_destroy_display(app->mlx_connection);
		free(app->mlx_connection);
		return (0);
	}
	app->image.img_ptr = mlx_new_image(app->mlx_connection, WIDTH, HEIGHT);
	if (app->image.img_ptr == NULL)
		return (0);
	app->image.buffer = mlx_get_data_addr(app->image.img_ptr, &app->image.bpp,
			&app->image.length, &app->image.endian);
	return (1);
}

void data_init(t_data *data)
{
	data->app = malloc(sizeof(t_app));
	data->ambient = malloc(sizeof(t_ambient));
	data->light = malloc(sizeof(t_light));
	data->camera = malloc(sizeof(t_camera));
	data->shapes = NULL;
	data->shape_count = 0;
	if (!init_mlx(data->app))
		exit(EXIT_FAILURE); // needs an exit function
}