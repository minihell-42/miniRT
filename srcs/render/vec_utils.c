/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:44:41 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/10 10:58:02 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"
#include "render.h"

float	vec_len(t_vector v)
{
	return (sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

float	vec_dot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	vec_cross(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = (v1.y * v2.z) - (v1.z * v2.y);
	new.y = (v1.z * v2.x) - (v1.x * v2.z);
	new.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (new);
}

t_vector	vec_normalize(t_vector v)
{
	t_vector	new;
	float		length;

	length = vec_len(v);
	if (length == 0.0f)
	{
		new.x = 0;
		new.y = 0;
		new.z = 0;
		return (new);
	}
	new = vec_scalar_div(v, length);
	return (new);
}

t_vector	vec_negate(t_vector v)
{
	t_vector	new;

	new.x = -v.x;
	new.y = -v.y;
	new.z = -v.z;
	return (new);
}
