/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:56:42 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:21:30 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"
#include "render.h"

int	init_mlx(t_app *app)
{
	app->mlx_connection = mlx_init();
	if (app->mlx_connection == NULL)
		return(0);
	app->mlx_window = mlx_new_window(app->mlx_connection, WIDTH, HEIGHT, "MiniRT");
	if (app->mlx_window == NULL)
	{
		mlx_destroy_display(app->mlx_connection);
		free(app->mlx_connection);
		return (0);
	}
	app->image->img_ptr = mlx_new_image(app->mlx_connection, WIDTH, HEIGHT);
	if (app->image->img_ptr == NULL)
		return (0);
	app->image->buffer = mlx_get_data_addr(app->image->img_ptr, &app->image->bpp,
			&app->image->length, &app->image->endian);
	return (1);
}

void	data_init(t_data *data)
{
	data->app = malloc(sizeof(t_app));
	data->app->image = malloc(sizeof(t_image));
	data->ambient = malloc(sizeof(t_ambient));
	data->light = malloc(sizeof(t_light));
	data->camera = malloc(sizeof(t_camera));
	if (!data->app || !data->ambient || !data->light || !data->camera
		|| !data->app->image)
		exit_message("Allocation failure");
	data->shapes = NULL;
	data->shape_count = 0;
	if (!init_mlx(data->app))
		exit_message("Mlx initiation failure");
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
	mlx_hook(data->app->mlx_window, 17, 0, free_data_wrapper, data);
	mlx_key_hook(data->app->mlx_window, handle_key, data->app);
	mlx_loop(data->app->mlx_connection);
	free_data(data);
}