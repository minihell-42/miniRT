/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:18:54 by samcasti          #+#    #+#             */
/*   Updated: 2025/08/11 13:35:55 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

static void	rotate_cylinder(int key, t_cylinder *cylinder, double radians)
{
	t_vector	old_vec;

	if (key == XK_z || key == XK_x)
	{
		old_vec.x = cylinder->normal.x;
		old_vec.y = cylinder->normal.y;
		cylinder->normal.x = old_vec.x * cos(radians)
			- old_vec.y * sin(radians);
		cylinder->normal.y = old_vec.x * sin(radians)
			+ old_vec.y * cos(radians);
		cylinder->normal = vec_normalize(cylinder->normal);
	}
}

static void	rotate_plane(t_plane *plane, double radians)
{
	t_vector	old_vec;

	if ((fabs(plane->normal.x) < 0.0001
			&& fabs(plane->normal.y) < 0.0001)
		&& (fabs(plane->normal.z - 1.0) < 0.0001
			|| fabs(plane->normal.z + 1.0) < 0.0001))
	{
		old_vec = plane->normal;
		plane->normal.y = old_vec.y * cos(radians)
			- old_vec.z * sin(radians);
		plane->normal.z = old_vec.y * sin(radians)
			+ old_vec.z * cos(radians);
	}
	else
	{
		old_vec = plane->normal;
		plane->normal.x = old_vec.x * cos(radians)
			- old_vec.y * sin(radians);
		plane->normal.y = old_vec.x * sin(radians)
			+ old_vec.y * cos(radians);
		plane->normal.z = old_vec.z;
	}
	plane->normal = vec_normalize(plane->normal);
}

void	rotate_object(int key, t_data *data)
{
	double		radians;
	t_shape		*current;
	float		angle;

	current = data->shapes;
	angle = 10.0;
	if (key == XK_v || key == XK_z)
		radians = angle * M_PI / 180.0;
	else if (key == XK_c || key == XK_x)
		radians = -angle * M_PI / 180.0;
	while (current)
	{
		if (current->shape_type == CYLINDER)
			rotate_cylinder(key, (t_cylinder *)current->object, radians);
		else if (current->shape_type == PLANE && (key == XK_c || key == XK_v))
			rotate_plane((t_plane *)current->object, radians);
		current = current->next;
	}
}
