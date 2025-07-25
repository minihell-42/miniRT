#include "miniRT.h"

void data_init(t_data *data)
{
	data->app = malloc(sizeof(t_app));
	data->ambient = malloc(sizeof(t_ambient));
	data->light = malloc(sizeof(t_light));
	data->camera = malloc(sizeof(t_camera));
}