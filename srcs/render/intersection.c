/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:43:46 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/07/28 11:43:48 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_inter	inter_init(const t_ray *ray)
{
	t_inter	inter;

	inter.ray = *ray;
	inter.t = ray->dist_max;
	inter.shape = NULL;
	return (inter);
}

t_vector	inter_pos(const t_inter *inter)
{
	return (ray_at(&inter->ray, inter->dist));
}

int	inter_hit(const t_inter *inter)
{
	return (inter->shape != NULL);
}
