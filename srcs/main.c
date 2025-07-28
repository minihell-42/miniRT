/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:05:21 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/25 14:04:43 by samcasti         ###   ########.fr       */
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
		error_exit("Invalid number of arguments");
	if (!correct_extension(argv[1]))
		error_exit("Invalid file extension");
	init_minirt(argv[1]);
	return (0);
}
