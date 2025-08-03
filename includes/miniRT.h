/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:05:11 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:42:22 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include "../minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288f
# endif

// In order to prevent bouncing rays self-intersecting
# define RAY_DIST_MIN 1e-6f

// 'Infinite' distance, used as a default value
# define RAY_DIST_MAX 1.0e30f

// Default screen size
# define HEIGHT 700
# define WIDTH 700

// Vector struct
typedef struct s_vector
{
	float				x;
	float				y;
	float				z;
}						t_vector;

// Color structx
typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

// Ambient struct
typedef struct s_ambient
{
	float				ratio;
	t_color				color;
	int					is_set;
}						t_ambient;

typedef struct s_viewpt
{
	float				aspect_ratio;
	float				theta;
	float				half_height;
	float				half_width;
	float				u;
	float				v;
}						t_viewpt;

// Camera struct
typedef struct s_camera
{
	t_vector			coordinates;
	t_vector			normalized;
	t_vector			up;
	t_vector			right;
	t_viewpt			view_port;
	float				fov;
	int					is_set;
}						t_camera;

// Light struct
typedef struct s_light
{
	float				ratio;
	t_vector			coordinates;
	int					is_set;
}						t_light;

// MLX Image struct
typedef struct s_image
{
	void				*img_ptr;
	char				*buffer;
	int					bpp;
	int					length;
	int					endian;
}						t_image;

// MLX struct
typedef struct s_app
{
	void				*mlx_connection;
	void				*mlx_window;
	t_image				*image;
}						t_app;

typedef enum s_type
{
	SPHERE,
	PLANE,
	CYLINDER
}						t_type;

typedef struct s_shape	t_shape;

typedef struct s_shape
{
	t_type				shape_type;
	void				*object;
	t_color				color;
	t_shape				*next;
}						t_shape;

typedef struct s_sphere
{
	t_vector			center;
	float				radius;
}						t_sphere;

typedef struct s_plane
{
	t_vector			point;
	t_vector			normal;
}						t_plane;

typedef struct s_cylinder
{
	t_vector			center;
	t_vector			normal;
	float				radius;
	float				height;
}						t_cylinder;

typedef struct s_quadratic
{
	float				a;
	float				b;
	float				c;
	float				dist0;
	float				dist1;
	float				square;
	int					sol_count;
}						t_quadratic;

typedef struct s_ray
{
	float				dist_max;
	t_vector			origin;
	t_vector			direction;
}						t_ray;

typedef struct s_inter
{
	float				dist;
	t_ray				ray;
	t_shape				*shape;
	t_color				color;
}						t_inter;

typedef struct s_data
{
	t_app				*app;
	t_ambient			*ambient;
	t_camera			*camera;
	t_light				*light;
	t_shape				*shapes;
	int					shape_count;
}						t_data;

// INIT
void					init_minirt(char *file);
void					data_init(t_data *data);

// READ & PARSE
char					*read_file(char *file, t_data *data);
void					parse_ambient(char *line, t_data *data);
void					parse_light(char *line, t_data *data);
void					parse_camera(char *line, t_data *data);
void					parse_sphere(char *line, t_data *data);
void					parse_plane(char *line, t_data *data);
void					parse_cylinder(char *line, t_data *data);

// UTILS
char					*clean_line(char *line);
int						parse_float(char *str, float *result);
int						parse_int(char *str, int *result);

// VALIDATIONS
int						validate_coordinates(char *str, t_vector *coords);
int						validate_color(char *str, t_color *color);
int						validate_ratio(char *str, float *ratio);
int						validate_fov(char *str, float *fov);
int						validate_positive_float(char *str, float *value);

// SHAPE CREATION
t_shape					*create_node(t_type type, void *shape, t_data *data);
void					append_node(t_data *data, t_shape *new_shape);
int						create_sphere(t_data *data, t_vector center,
							float radius, t_color color);
int						create_plane(t_data *data, t_vector point,
							t_vector normal, t_color color);
int						create_cylinder(t_data *data, t_cylinder *cylinder,
							t_color color);

// ERRORS
void					exit_message(char *msg);
void					exit_free_array(char *msg, char **array);
void					exit_free_data(char *msg, t_data *data);

// FREE
void					free_array(char **array);
void					free_shapes(t_shape *shapes);
void					free_data(t_data *data);
void					exit_free_all(char *msg, t_data *data, char **array);

#endif