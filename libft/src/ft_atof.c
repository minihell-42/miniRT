/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:54:54 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 17:55:29 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atof_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static double	ft_atof_frac(const char *str, int *i)
{
	double	frac;
	double	divisor;

	frac = 0.0;
	divisor = 1.0;
	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
		{
			frac = frac * 10.0 + (str[(*i)++] - '0');
			divisor *= 10.0;
		}
	}
	return (frac / divisor);
}

double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	result;

	i = 0;
	result = 0.0;
	while (ft_isspace(str[i]))
		i++;
	sign = ft_atof_sign(str, &i);
	while (ft_isdigit(str[i]))
		result = result * 10.0 + (str[i++] - '0');
	result += ft_atof_frac(str, &i);
	return (sign * result);
}
