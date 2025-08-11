/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:16:31 by samcasti          #+#    #+#             */
/*   Updated: 2025/08/11 14:02:54 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	setup_events(t_data *data)
{
	mlx_hook(data->app->mlx_window, DestroyNotify, StructureNotifyMask,
		on_close, data);
	mlx_hook(data->app->mlx_window, KeyPress, KeyPressMask, on_key_press, data);
	mlx_hook(data->app->mlx_window, 17, 0, on_mouse_exit, data);
}
