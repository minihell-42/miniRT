/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:42:59 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/07/28 11:43:12 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"

typedef enum s_type
{
	SPHERE,
	PLANE,
	CYLINDER
}				t_type;

typedef struct s_shape
{
	t_type		shape_type;
	void		*object;
	t_color		color;

}				t_shape;

typedef struct s_sphere
{
	t_vector	center;
	float		radius;
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	float		radius;
	float		height;
}				t_cylinder;

typedef struct s_quadratic
{
	float		a;
	float		b;
	float		c;
	float		dist0;
	float		dist1;
	float		square;
	int			sol_count;
}				t_quadratic;

typedef struct s_ray
{
	float		dist_max;
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_inter
{
	float		dist;
	t_ray		ray;
	t_shape		*shape;
	t_color		color;
}				t_inter;

// VECTOR UTILS
float			vec_len(t_vector v);
float			vec_dot(t_vector v1, t_vector v2);
t_vector		vec_cross(t_vector v1, t_vector v2);
t_vector		vec_normalize(t_vector v);
t_vector		vec_negate(t_vector v);
t_vector		vec_reflect(t_vector v, t_vector n);

// VECTOR MATH
t_vector		vec_add(t_vector v1, t_vector v2);
t_vector		vec_sub(t_vector v1, t_vector v2);
t_vector		vec_mult(t_vector v1, t_vector v2);
t_vector		vec_scalar_mult(t_vector v, float scalar);
t_vector		vec_div(t_vector v1, t_vector v2);
t_vector		vec_scalar_div(t_vector v, float scalar);

// RAY
t_ray			ray_init(t_vector origin, t_vector direction, float dist_max);
t_ray			ray_init_default(t_vector origin, t_vector direction);
t_vector		ray_at(const t_ray *ray, float dist);

// INTERSECTION
t_inter			inter_init(const t_ray *ray);
t_vector		inter_pos(const t_inter *inter);
int				inter_hit(const t_inter *inter);

//  SHAPES
int				shape_intersect(t_inter *hit, const t_shape *shape);
int				sphere_intersection(t_inter *hit, const t_sphere *sp);
int				plane_intersection(t_inter *hit, const t_plane *pl);
int				cylinder_intersection(t_inter *hit, const t_cylinder *cy);
int				solve_quad(t_quadratic *quad);
float			pick_quad_root(const t_quadratic *quad, float dist_min,
					float dist_max);
t_vector		shape_normal(const t_shape *shape, t_vector hit_point);
t_vector		sphere_normal(const t_sphere *sp, t_vector hit_point);
t_vector		plane_normal(const t_plane *pl, t_vector hit_point);
t_vector		cylinder_normal(const t_cylinder *cy, t_vector hit_point);

// COLOR
t_color			color_add(t_color c1, t_color c2);
t_color			color_mult(t_color c1, t_color c2);
t_color			color_scalar_mult(t_color c, float scalar);
t_color			apply_gamma_correction(t_color c, float exposure, float gamma);
t_vector		vec_clamp(t_vector v, float min, float max);
#endif
