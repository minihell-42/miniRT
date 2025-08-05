#include "miniRT.h"
#include "render.h"

static void	rotate_cylinder(int key, t_cylinder *cylinder, float angle)
{
	double	radians;
	t_vector old_vec;

	if (key == XK_z || key == XK_x)
	{
		if (key == XK_z)
			radians = angle * M_PI / 180.0;
		else
			radians = -angle * M_PI / 180.0;
		old_vec.x = cylinder->normal.x;
		old_vec.y = cylinder->normal.y;
		cylinder->normal.x = old_vec.x * cos(radians) - old_vec.y * sin(radians);
		cylinder->normal.y = old_vec.x * sin(radians) + old_vec.y * cos(radians);
		cylinder->normal = vec_normalize(cylinder->normal);
	}
}

static void	rotate_plane(int key, t_plane *plane, float angle)
{
	double	radians;
	t_vector old_vec;

	if (key == XK_c || key == XK_v)
	{
		if (key == XK_v)
			radians = angle * M_PI / 180.0;
		else
			radians = -angle * M_PI / 180.0;
		if ((fabs(plane->normal.x) < 0.0001 && fabs(plane->normal.y) < 0.0001) && 
			(fabs(plane->normal.z - 1.0) < 0.0001 || fabs(plane->normal.z + 1.0) < 0.0001))
		{
			old_vec = plane->normal;
			plane->normal.y = old_vec.y * cos(radians) - old_vec.z * sin(radians);
			plane->normal.z = old_vec.y * sin(radians) + old_vec.z * cos(radians);
		}
		else
		{
			old_vec = plane->normal;
			plane->normal.x = old_vec.x * cos(radians) - old_vec.y * sin(radians);
			plane->normal.y = old_vec.x * sin(radians) + old_vec.y * cos(radians);
			plane->normal.z = old_vec.z;
		}
		plane->normal = vec_normalize(plane->normal);
	}
}

void	rotate_object(int key, t_data *data)
{
	t_shape *current;
	float angle;

	current = data->shapes;
	angle = 10.0;
	while (current)
	{
		if (current->shape_type == CYLINDER)
			rotate_cylinder(key, (t_cylinder *)current->object, angle);
		else if (current->shape_type == PLANE)
			rotate_plane(key, (t_plane *)current->object, angle);
		current = current->next;
	}
}