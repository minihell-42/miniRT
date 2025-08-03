#include "miniRT.h"

void	translate_camera(int key, t_data *data)
{
	float move_amount;

	move_amount = 0.1;
	if (key == XK_a)
		data->camera->coordinates.x -= move_amount;
	if (key == XK_d)
		data->camera->coordinates.x += move_amount;
	if (key == XK_w)
		data->camera->coordinates.y += move_amount;
	if (key == XK_s)
		data->camera->coordinates.y -= move_amount;
}

void	translate_light(int key, t_data *data)
{
	int move_amount;

	move_amount = 1;
	if (key == XK_t)
		data->light->coordinates.y += move_amount;
	if (key == XK_f)
		data->light->coordinates.x -= move_amount;
	if (key == XK_g)
		data->light->coordinates.y -= move_amount;
	if (key == XK_h)
		data->light->coordinates.x += move_amount;
	if (key == XK_y)
		data->light->coordinates.z -= move_amount;
	if (key == XK_u)
		data->light->coordinates.z += move_amount;
}

static void	translate_sphere(int key, t_sphere *sphere, float move_amount)
{
	if (key == XK_Left)
		sphere->center.x -= move_amount;
	else if (key == XK_Right)
		sphere->center.x += move_amount;
	else if (key == XK_Up)
		sphere->center.y += move_amount;
	else if (key == XK_Down)
		sphere->center.y -= move_amount;
	else if (key == 43)
		sphere->center.z += move_amount;
	else if (key == 45)
		sphere->center.z -= move_amount;
}

static void	translate_plane(int key, t_plane *plane, float move_amount)
{
	if (key == XK_Left)
		plane->point.x -= move_amount;
	else if (key == XK_Right)
		plane->point.x += move_amount;
	else if (key == XK_Up)
		plane->point.y += move_amount;
	else if (key == XK_Down)
		plane->point.y -= move_amount;
	else if (key == 43)
		plane->point.z += move_amount;
	else if (key == 45)
		plane->point.z -= move_amount;
}

static void	translate_cylinder(int key, t_cylinder *cylinder, float move_amount)
{
	if (key == XK_Left)
		cylinder->center.x -= move_amount;
	else if (key == XK_Right)
		cylinder->center.x += move_amount;
	else if (key == XK_Up)
		cylinder->center.y += move_amount;
	else if (key == XK_Down)
		cylinder->center.y -= move_amount;
	else if (key == 43)
		cylinder->center.z += move_amount;
	else if (key == 45)
		cylinder->center.z -= move_amount;
}

void	translate_object(int key, t_data *data)
{
	t_shape	*current;
	float	move_amount;

	current = data->shapes;
	move_amount = 0.5;
	while (current)
	{
		if (current->shape_type == SPHERE)
			translate_sphere(key, (t_sphere *)current->object, move_amount);
		else if (current->shape_type == PLANE)
			translate_plane(key, (t_plane *)current->object, move_amount);
		else if (current->shape_type == CYLINDER)
			translate_cylinder(key, (t_cylinder *)current->object, move_amount);
		current = current->next;
	}
}
