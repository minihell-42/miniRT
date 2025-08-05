#include "miniRT.h"

void	setup_events(t_data *data)
{
	mlx_hook(data->app->mlx_window, DestroyNotify, StructureNotifyMask,
			on_close, data);
	mlx_hook(data->app->mlx_window, KeyPress, KeyPressMask, on_key_press, data);
	mlx_hook(data->app->mlx_window, ButtonPress, ButtonPressMask,
			on_mouse_scroll, data);
	mlx_hook(data->app->mlx_window, 17, 0, on_mouse_exit, data);
}