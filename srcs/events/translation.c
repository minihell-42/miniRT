/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:11:49 by samcasti          #+#    #+#             */
/*   Updated: 2025/08/11 13:12:35 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	translate_camera(int key, t_data *data)
{
	float	move_amount;

	move_amount = 2.0;
	if (key == XK_a)
		data->camera->coordinates.x -= move_amount;
	if (key == XK_d)
		data->camera->coordinates.x += move_amount;
	if (key == XK_w)
		data->camera->coordinates.y += move_amount;
	if (key == XK_s)
		data->camera->coordinates.y -= move_amount;
}

void	translate_light(int key, t_data *data)
{
	float	move_amount;

	move_amount = 1.0;
	if (key == XK_t)
		data->light->coordinates.y += move_amount;
	if (key == XK_f)
		data->light->coordinates.x -= move_amount;
	if (key == XK_g)
		data->light->coordinates.y -= move_amount;
	if (key == XK_h)
		data->light->coordinates.x += move_amount;
	if (key == XK_y)
		data->light->coordinates.z -= move_amount;
	if (key == XK_u)
		data->light->coordinates.z += move_amount;
}
