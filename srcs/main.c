/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:05:21 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:17:59 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	correct_extension(char *str)
{
	int	len;

	len = ft_strlen(str) - 3;
	if (!ft_strncmp(str + len, ".rt", 3))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
    t_data *data;

    if (argc != 2)
        error_exit("Invalid number of arguments");
    if (!correct_extension(argv[1]))
        error_exit("Invalid extension of file");
    data = malloc(sizeof(t_data));
    if (!data)
        error_exit("Allocation failure");
    init_minirt(argv[1]);
    render(data);
    mlx_hook(data->app->mlw_window, 17, 0, clean_exit_wrapper, data);
	mlx_key_hook(data->app->mlw_window, handle_key, data->app);
	mlx_loop(data->app->mlx_connection);
	clean_exit(data);
    return (0);
}
