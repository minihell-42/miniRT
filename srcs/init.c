/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:56:42 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/25 13:56:55 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	data_init(t_data *data)
{
	data->cylinder = malloc(sizeof(t_cylinder));
	data->sphere = malloc(sizeof(t_sphere));
	data->plane = malloc(sizeof(t_plane));
	data->app = malloc(sizeof(t_app));
	data->app->image = malloc(sizeof(t_image));
	data->ambient = malloc(sizeof(t_ambient));
	data->light = malloc(sizeof(t_light));
	data->camera = malloc(sizeof(t_camera));
	if (!data->cylinder || !data->plane || !data->sphere)
		exit_message("Allocation shape failure");
	if (!data->app || !data->ambient || !data->light || !data->camera || !data->app->image)
		exit_message("Allocation failure");
}

void	init_minirt(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_message("Allocation failure");
	data_init(data);
	read_file(file, data);
	print_parsed_data(data);
}

