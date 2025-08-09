/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:10:59 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/03 18:16:23 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

void	define_viewpt(t_viewpt *vp, float fov)
{
	vp->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	vp->theta = fov * (M_PI / 180.0f);
	vp->half_height = tanf(vp->theta / 2.0f);
	vp->half_width = vp->aspect_ratio * vp->half_height;
}

void	build_orth_basis(t_camera *cam)
{
	t_vector	world_up;

	world_up = (t_vector){0.0f, 1.0f, 0.0f};
	if (fabsf(vec_dot(cam->normalized, world_up)) > 0.999f)
		world_up = (t_vector){1.0f, 0.0f, 0.0f};
	cam->right = vec_normalize(vec_cross(cam->normalized, world_up));
	cam->up = vec_cross(cam->right, cam->normalized);
	vec_normalize(cam->up);
}
