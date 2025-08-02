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
	data->ambient->is_set = 0;
	data->camera->is_set = 0;
	data->light->is_set = 0;
}

void	init_minirt(char *file)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_message("Allocation failure");
	data_init(data);
	read_file(file, data);
	// AQUI IRIA EL RESTO 
	
	free_data(data);
}