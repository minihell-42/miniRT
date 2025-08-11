/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:16:00 by samcasti          #+#    #+#             */
/*   Updated: 2025/08/11 14:03:06 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

int	on_close(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	on_key_press(int key, t_data *data)
{
	if (key == XK_Escape)
		return (on_close(data));
	if (key == XK_Left || key == XK_Right || key == XK_Up || key == XK_Down
		|| key == 45 || key == 43)
		translate_object(key, data);
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
		translate_camera(key, data);
	if (key == XK_t || key == XK_f || key == XK_g || key == XK_h || key == XK_y
		|| key == XK_u)
		translate_light(key, data);
	if (key == XK_z || key == XK_x || key == XK_c || key == XK_v)
		rotate_object(key, data);
	if (key == XK_1 || key == XK_2)
		resize_object(key, data);
	render(data);
	return (0);
}

int	on_mouse_exit(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}
