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
    if (argc != 2)
        exit_message("Invalid number of arguments");
    if (!correct_extension(argv[1]))
        exit_message("Invalid extension of file");
    init_minirt(argv[1]);
    return (0);
}
