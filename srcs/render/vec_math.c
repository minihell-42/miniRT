/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:44:36 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/03 18:17:05 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"
#include "render.h"

t_vector	vec_add(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	return (new);
}

t_vector	vec_sub(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	new.z = v1.z - v2.z;
	return (new);
}

t_vector	vec_mult(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x * v2.x;
	new.y = v1.y * v2.y;
	new.z = v1.z * v2.z;
	return (new);
}

t_vector	vec_scalar_mult(t_vector v, float scalar)
{
	t_vector	new;

	new.x = v.x * scalar;
	new.y = v.y * scalar;
	new.z = v.z * scalar;
	return (new);
}

t_vector	vec_div(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x / v2.x;
	new.y = v1.y / v2.y;
	new.z = v1.z / v2.z;
	return (new);
}

// TODO: Needs an exit when scalar < RAY_DIST_MIN (close to zero)
// current implementation is temporary
t_vector	vec_scalar_div(t_vector v, float scalar)
{
	t_vector	new;

	if (scalar < RAY_DIST_MIN)
		return ((t_vector){0.0f, 0.0f, 0.0f});
	new.x = v.x / scalar;
	new.y = v.y / scalar;
	new.z = v.z / scalar;
	return (new);
}
