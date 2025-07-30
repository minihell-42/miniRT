#include "render.h"

void	clean_exit(t_data *data)
{
  t_shape *curr;

  curr = data->shapes;
  while(curr)
  {
    if (curr->object)
      free(curr->object);
    free(curr);
    curr = curr->next;
  }
  if (data->camera)
    free(data->camera);
  if (data->light)
    free(data->light);
  if (data->ambient)
    free(data->ambient);
  if (data->app)
  {
    mlx_destroy_image(data->app->mlx_connection, data->app->image.img_ptr);
    mlx_destroy_window(data->app->mlx_connection, data->app->mlw_window);
    mlx_destroy_display(data->app->mlx_connection);
    free(data->app);
  }
  free(data);
	exit(EXIT_SUCCESS);
}

int	clean_exit_wrapper(void *param)
{
	clean_exit((t_data *)param);
	return (0);
}

int	handle_key(int keysym, t_app *app)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(app->mlx_connection, app->mlw_window);
		mlx_destroy_display(app->mlx_connection);
		free(app->mlx_connection);
		exit(1);
	}
	return (0);
}