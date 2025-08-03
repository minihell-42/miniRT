/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:13:28 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/03 18:13:29 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

int	free_data_wrapper(void *param)
{
	free_data((t_data *)param);
	exit(EXIT_SUCCESS);
}

int	handle_key(int keysym, t_app *app)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(app->mlx_connection, app->mlx_window);
		mlx_destroy_display(app->mlx_connection);
		free(app->mlx_connection);
		exit(1);
	}
	return (0);
}
