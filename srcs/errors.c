/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:55:54 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:11:30 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	exit_message(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	exit_free_array(char *msg, char **array)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	free_array(array);
	exit(EXIT_FAILURE);
}

void	exit_free_data(char *msg, t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	free_data(data);
	exit(EXIT_FAILURE);
}

void	exit_free_all(char *msg, t_data *data, char **array)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	free_array(array);
	free_data(data);
	exit(EXIT_FAILURE);
}
