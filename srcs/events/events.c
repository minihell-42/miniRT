#include "miniRT.h"

int	on_close(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	on_key_press(int key, t_data *data)
{
	if (key == KEY_ESC)
		return (on_close(data));
	return (0);
}