/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:56:34 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:39:19 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_app(t_data *data)
{
	if (data->app->image)
	{
		if (data->app->image->img_ptr)
			mlx_destroy_image(data->app->mlx_connection,
				data->app->image->img_ptr);
		free(data->app->image);
	}
	if (data->app->mlx_window)
		mlx_destroy_window(data->app->mlx_connection, data->app->mlx_window);
	if (data->app->mlx_connection)
		mlx_destroy_display(data->app->mlx_connection);
	free(data->app->mlx_connection);
	free(data->app);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free(data->ambient);
	free(data->camera);
	free(data->light);
	if (data->app)
		free_app(data);
	free(data->cylinder);
	free(data->sphere);
	free(data->plane);
	free(data);
}
