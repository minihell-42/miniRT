/*
#include "miniRT.h"
#include <stdio.h>

static void	print_vector(char *name, t_vector v)
{
	printf("    %s: (%f, %f, %f)\n", name, v.x, v.y, v.z);
}

static void	print_color(char *name, t_color c)
{
	printf("    %s: (R:%d, G:%d, B:%d)\n", name, c.r, c.g, c.b);
}

static void	print_ambient(t_ambient *amb)
{
	if (!amb->is_set)
	{
		printf("Ambient: <not set>\n");
		return ;
	}
	printf("Ambient:\n");
	printf("  ratio: %f\n", amb->ratio);
	print_color("color", amb->color);
}

static void	print_light(t_light *light)
{
	if (!light->is_set)
	{
		printf("Light: <not set>\n");
		return ;
	}
	printf("Light:\n");
	printf("  ratio: %f\n", light->ratio);
	print_vector("position", light->coordinates);
}

static void	print_camera(t_camera *cam)
{
	if (!cam->is_set)
	{
		printf("Camera: <not set>\n");
		return ;
	}
	printf("Camera:\n");
	printf("  fov: %f\n", cam->fov);
	print_vector("position", cam->coordinates);
	print_vector("forward", cam->normalized);
	print_vector("up", cam->up);
	print_vector("right", cam->right);
	printf("  viewport:\n");
	printf("    aspect_ratio: %f\n", cam->view_port.aspect_ratio);
	printf("    half_width:   %f\n", cam->view_port.half_width);
	printf("    half_height:  %f\n", cam->view_port.half_height);
}

static void	print_shapes(const t_shape *sh)
{
	int			i;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	i = 0;
	while (sh)
	{
		printf("Shape #%d:\n", ++i);
		switch (sh->shape_type)
		{
		case SPHERE:
		{
			sp = (t_sphere *)sh->object;
			printf("  Type: Sphere\n");
			print_vector("  center", sp->center);
			printf("  radius: %f\n", sp->radius);
			break ;
		}
		case PLANE:
		{
			pl = (t_plane *)sh->object;
			printf("  Type: Plane\n");
			print_vector("  point", pl->point);
			print_vector("  normal", pl->normal);
			break ;
		}
		case CYLINDER:
		{
			cy = (t_cylinder *)sh->object;
			printf("  Type: Cylinder\n");
			print_vector("  center", cy->center);
			print_vector("  axis", cy->normal);
			printf("  radius: %f\n", cy->radius);
			printf("  height: %f\n", cy->height);
			break ;
		}
		}
		print_color("  material color", sh->color);
		sh = sh->next;
	}
	if (i == 0)
		printf("No shapes parsed.\n");
}

void	print_data(t_data *data)
{
	if (!data)
	{
		printf("No data to print.\n");
		return ;
	}
	// Ambient light
	print_ambient(data->ambient);
	// Main light
	print_light(data->light);
	// Camera
	print_camera(data->camera);
	// Shapes list
	printf("Parsed shapes (count = %d):\n", data->shape_count);
	print_shapes(data->shapes);
}
*/