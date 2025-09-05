/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:56:42 by samcasti          #+#    #+#             */
/*   Updated: 2025/09/05 18:09:10 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"
#include "render.h"

static void	app_init(t_data *data)
{
	data->app->mlx_connection = mlx_init();
	if (!data->app->mlx_connection)
		exit_free_data("Unable to create mlx connection", data);
	data->app->mlx_window = mlx_new_window(data->app->mlx_connection, WIDTH,
			HEIGHT, "MiniRT");
	if (!data->app->mlx_window)
		exit_free_data("Unable to create mlx window", data);
	data->app->image->img_ptr = mlx_new_image(data->app->mlx_connection, WIDTH,
			HEIGHT);
	if (!data->app->image->img_ptr)
		exit_free_data("Unable to create mlx image", data);
	data->app->image->buffer = mlx_get_data_addr(data->app->image->img_ptr,
			&data->app->image->bpp, &data->app->image->length,
			&data->app->image->endian);
}

static void	data_init(t_data *data)
{
	data->app = malloc(sizeof(t_app));
	data->app->image = malloc(sizeof(t_image));
	data->ambient = malloc(sizeof(t_ambient));
	data->light = malloc(sizeof(t_light));
	data->camera = malloc(sizeof(t_camera));
	if (!data->app || !data->ambient || !data->light || !data->camera
		|| !data->app->image)
		exit_message("Allocation failure");
	app_init(data);
	data->shapes = NULL;
	data->shape_count = 0;
	data->ambient->is_set = 0;
	data->camera->is_set = 0;
	data->light->is_set = 0;
	data->light->specular = (t_vector){255.0f, 255.0f, 255.0f};
}

void	init_minirt(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_message("Allocation failure");
	data_init(data);
	read_file(file, data);
	render(data);
	write(1, "Rendering finalized\n", 21);
	setup_events(data);
	mlx_loop(data->app->mlx_connection);
}
