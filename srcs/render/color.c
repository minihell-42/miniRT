/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:43:29 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/07/28 11:53:14 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"
#include "render.h"

t_color	color_add(t_color c1, t_color c2)
{
	t_color	new;

	new.r = c1.r + c2.r;
	new.g = c1.g + c2.g;
	new.b = c1.b + c2.b;
	return (new);
}

t_color	color_mult(t_color c1, t_color c2)
{
	t_color	new;

	new.r = c1.r * c2.r;
	new.g = c1.g * c2.g;
	new.b = c1.b * c2.b;
	return (new);
}

t_color	color_scalar_mult(t_color c, float scalar)
{
	t_color	new;

	new.g = c.g * scalar;
	new.r = c.r * scalar;
	new.b = c.b * scalar;
	return (new);
}

t_color	apply_gamma_correction(t_color c, float exposure, float gamma)
{
	t_color	new;

	new.r = powf(c.r * exposure, gamma);
	new.g = powf(c.g * exposure, gamma);
	new.b = powf(c.b * exposure, gamma);
	return (new);
}

t_vector	vec_clamp(t_vector v, float min, float max)
{
	t_vector	new;

	new.x = fminf(fmaxf(v.x, min), max);
	new.y = fminf(fmaxf(v.y, min), max);
	new.z = fminf(fmaxf(v.z, min), max);
	return (new);
}
