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
	data->app = malloc(sizeof(t_app));
	data->ambient = malloc(sizeof(t_ambient));
	data->light = malloc(sizeof(t_light));
	data->camera = malloc(sizeof(t_camera));
	if (!data->app || !data->ambient || !data->light || !data->camera)
		return ;
}

void	init_minirt(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		system_error("Allocation failure");
	data_init(data);
	read_file(file);
}

