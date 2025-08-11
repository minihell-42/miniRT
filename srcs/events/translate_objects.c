/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:15:37 by samcasti          #+#    #+#             */
/*   Updated: 2025/08/11 13:45:12 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	translate_sphere(int key, t_sphere *sphere, float move_amount)
{
	if (key == XK_Left)
		sphere->center.x -= move_amount;
	else if (key == XK_Right)
		sphere->center.x += move_amount;
	else if (key == XK_Up)
		sphere->center.y += move_amount;
	else if (key == XK_Down)
		sphere->center.y -= move_amount;
	else if (key == XK_plus)
		sphere->center.z += move_amount;
	else if (key == XK_minus)
		sphere->center.z -= move_amount;
}

static void	translate_plane(int key, t_plane *plane, float move_amount)
{
	if (key == XK_Left)
		plane->point.x -= move_amount;
	else if (key == XK_Right)
		plane->point.x += move_amount;
	else if (key == XK_Up)
		plane->point.y += move_amount;
	else if (key == XK_Down)
		plane->point.y -= move_amount;
	else if (key == XK_plus)
		plane->point.z += move_amount;
	else if (key == XK_minus)
		plane->point.z -= move_amount;
}

static void	translate_cylinder(int key, t_cylinder *cylinder, float move_amount)
{
	if (key == XK_Left)
		cylinder->center.x -= move_amount;
	else if (key == XK_Right)
		cylinder->center.x += move_amount;
	else if (key == XK_Up)
		cylinder->center.y += move_amount;
	else if (key == XK_Down)
		cylinder->center.y -= move_amount;
	else if (key == XK_plus)
		cylinder->center.z += move_amount;
	else if (key == XK_minus)
		cylinder->center.z -= move_amount;
}

void	translate_object(int key, t_data *data)
{
	t_shape	*current;
	float	move_amount;

	current = data->shapes;
	move_amount = 1.0;
	while (current)
	{
		if (current->shape_type == SPHERE)
			translate_sphere(key, (t_sphere *)current->object, move_amount);
		else if (current->shape_type == PLANE)
			translate_plane(key, (t_plane *)current->object, move_amount);
		else if (current->shape_type == CYLINDER)
			translate_cylinder(key, (t_cylinder *)current->object, move_amount);
		current = current->next;
	}
}
