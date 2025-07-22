/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:05:21 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/22 17:14:27 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int correct_extension(char *str)
{
    int len;

    len = ft_strlen(str) - 3;
    if (!ft_strncmp(str + len, ".rt", 3))
        return (1);
    return (0);
}

int	main(int argc, char **argv)
{
    if (argc == 2)
    {
        if (!correct_extension(argv[1]))
        {
            ft_putendl_fd("Error: Invalid extension of file", 2);
            return (1);
        }
        // INIT DATA AND PARSE
        return (0);
    }
    ft_putendl_fd("Error: Incorrect number or arguments", 2);
	return (1);
}
