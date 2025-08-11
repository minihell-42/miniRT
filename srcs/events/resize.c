/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:22:00 by samcasti          #+#    #+#             */
/*   Updated: 2025/08/11 13:22:01 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	resize_cylinder(int key, t_cylinder *cylinder, float size)
{
	if (key == XK_1)
	{
		if (cylinder->radius - size > 0)
			cylinder->radius -= size;
		if (cylinder->height - size > 0)
			cylinder->height -= size;
	}
	else if (key == XK_2)
	{
		cylinder->radius += size;
		cylinder->height += size;
	}
}

static void	resize_sphere(int key, t_sphere *sphere, float size)
{
	if (key == XK_1)
		sphere->radius -= size;
	else if (key == XK_2)
		sphere->radius += size;
}

void	resize_object(int key, t_data *data)
{
	t_shape		*current;
	float		size;

	current = data->shapes;
	size = 1;
	while (current)
	{
		if (current->shape_type == CYLINDER)
			resize_cylinder(key, (t_cylinder *)current->object, size);
		else if (current->shape_type == SPHERE)
			resize_sphere(key, (t_sphere *)current->object, size);
		current = current->next;
	}
}
