/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:11:19 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/03 18:49:20 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

void	ambient_computation(t_ambient *amb)
{
	amb->color.r *= amb->ratio;
	amb->color.g *= amb->ratio;
	amb->color.b *= amb->ratio;
}

t_vector	convert_amb_vec(t_ambient *amb)
{
	t_vector	amb_vec;

	amb_vec.x = (float)amb->color.r;
	amb_vec.y = (float)amb->color.g;
	amb_vec.z = (float)amb->color.b;
	return (amb_vec);
}
