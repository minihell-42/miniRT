/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:42:59 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/03 19:10:55 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"

void		render(t_data *data);

// VECTOR UTILS
float		vec_len(t_vector v);
float		vec_dot(t_vector v1, t_vector v2);
t_vector	vec_cross(t_vector v1, t_vector v2);
t_vector	vec_normalize(t_vector v);
t_vector	vec_negate(t_vector v);
t_vector  vec_reflect(t_vector v1, t_vector v2);

// VECTOR MATH
t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_sub(t_vector v1, t_vector v2);
t_vector	vec_mult(t_vector v1, t_vector v2);
t_vector	vec_scalar_mult(t_vector v, float scalar);
t_vector	vec_scalar_div(t_vector v, float scalar);

// RAY
t_ray		ray_init(t_vector origin, t_vector direction, float dist_max);
t_ray		ray_init_default(t_vector origin, t_vector direction);
t_ray		generate_ray(t_camera *cam, t_viewpt *vp, int x, int y);
t_vector	ray_at(t_ray *ray, float dist);

// INTERSECTION
int			inter_hit(t_inter *inter);
t_inter		inter_init(t_ray *ray);
t_vector	inter_pos(t_inter *inter);
t_inter		cast_ray(t_ray *ray, t_shape *shapes);

//  SHAPES
int			shape_intersect(t_inter *hit, t_shape *shape);
int			sphere_intersection(t_inter *hit, t_sphere *sp);
int			plane_intersection(t_inter *hit, t_plane *pl);
int			cylinder_intersection(t_inter *hit, t_cylinder *cy);
int			solve_quad(t_quadratic *quad);
float		pick_quad_root(t_quadratic *quad, float dist_min, float dist_max);
t_vector	shape_normal(t_shape *shape, t_vector hit_point);
t_vector	sphere_normal(t_sphere *sp, t_vector hit_point);
t_vector	plane_normal(t_plane *pl, t_vector hit_point);
t_vector	cylinder_normal(t_cylinder *cy, t_vector hit_point);

// COLOR
int			shade_pixel(t_inter *hit, t_data *data);
t_color		color_add(t_color c1, t_color c2);
t_color		color_mult(t_color c1, t_color c2);
t_color		color_scalar_mult(t_color c, float scalar);
t_vector	apply_gamma_correction(t_vector c);
t_vector	vec_clamp(t_vector v, float min, float max);

// CAMERA
void		build_orth_basis(t_camera *cam);
void		define_viewpt(t_viewpt *vp, float fov);
void		normalize_coord(t_viewpt *vp, float x, float y);

// AMBIENT LIGHT
t_vector	convert_col_vec(t_color col);
t_vector	calc_diffuse(t_inter *hit, t_light *light);

#endif
