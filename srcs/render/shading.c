#include "miniRT.h"
#include "render.h"

int	shade_pixel(t_inter *hit, t_data *data)
{
	t_vector P;
	t_vector N;
	t_vector Ldir;
	t_vector base;
	t_vector amb;
	t_vector col;
	float diff;
	int ir;
	int ig;
	int ib;

	if (!inter_hit(hit))
		return (0x000000);
	P = inter_pos(hit);
	N = shape_normal(hit->shape, P);
	Ldir = vec_normalize(vec_sub(data->light->coordinates, P));
	diff = fmaxf(vec_dot(N, Ldir), 0.0f);
	base.x = hit->color.r * data->light->ratio * diff;
	base.y = hit->color.g * data->light->ratio * diff;
	base.z = hit->color.b * data->light->ratio * diff;
	amb.x = (float)data->ambient->color.r;
	amb.y = (float)data->ambient->color.g;
	amb.z = (float)data->ambient->color.b;
	col = vec_clamp(vec_add(amb, base), 0.0f, 255.0f);
	col.x = powf(col.x / 255.0f, 1 / 2.2f) * 255.0f;
	col.y = powf(col.y / 255.0f, 1 / 2.2f) * 255.0f;
	col.z = powf(col.z / 255.0f, 1 / 2.2f) * 255.0f;
	ir = (int)fminf(fmaxf(col.x, 0.0f), 255.0f);
	ig = (int)fminf(fmaxf(col.y, 0.0f), 255.0f);
	ib = (int)fminf(fmaxf(col.z, 0.0f), 255.0f);
	return ((ir << 16) | (ig << 8) | ib);
}