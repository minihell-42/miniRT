/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:22:43 by samcasti          #+#    #+#             */
/*   Updated: 2025/08/11 13:22:45 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_shape	*create_node(t_type type, void *shape, t_data *data)
{
	t_shape	*new_shape;

	new_shape = malloc(sizeof(t_shape));
	if (!new_shape)
		return (NULL);
	new_shape->shape_type = type;
	new_shape->object = shape;
	new_shape->next = NULL;
	data->shape_count++;
	return (new_shape);
}

void	append_node(t_data *data, t_shape *new_shape)
{
	t_shape	*current;

	if (!data->shapes)
		data->shapes = new_shape;
	else
	{
		current = data->shapes;
		while (current->next)
			current = current->next;
		current->next = new_shape;
	}
}
