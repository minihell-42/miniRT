/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:05:11 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/25 13:52:34 by samcasti         ###   ########.fr       */
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
# include <stdbool.h>
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
	float		x;
	float		y;
	float		z;
}				t_vector;

// Color struct
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

// Ambient struct
typedef struct s_ambient
{
	float		ratio;
	t_color		color;
}				t_ambient;

// Camera struct
typedef struct s_camera
{
	t_vector	coordinates;
	t_vector	normalized;
	float		fov;
}				t_camera;

// Light struct
typedef struct s_light
{
	float		ratio;
	t_vector	coordinates;

}				t_light;

// MLX Image struct
typedef struct s_image
{
	void		*img_ptr;
	char		*buffer;
	int			bpp;
	int			length;
	int			endian;
}				t_image;

// MLX struct
typedef struct s_app
{
	void	*mlx_connection;
	void	*mlw_window;
	t_image	*image;
}		t_app;

typedef struct s_data
{
	t_app		*app;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
}			t_data;

// ERRORS
void	error_exit(char *msg);
void	system_error(char *msg);

// INIT
void	init_minirt(char *file);
void	data_init(t_data *data);

// Read
char	*read_file(char *file);

// FREEE
void free_data(t_data *data);

#endif
