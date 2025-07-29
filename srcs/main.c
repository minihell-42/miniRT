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

void	print_parsed_data(t_data *data)
{
	if (!data)
		return ;
	
	ft_printf("\n=== PARSED SCENE DATA ===\n");
	
	// Print Ambient data
	if (data->ambient)
	{
		ft_printf("AMBIENT:\n");
		printf("  Ratio: %0.2f\n", (data->ambient->ratio));
		ft_printf("  Color: R=%d, G=%d, B=%d\n", 
			data->ambient->color.r, data->ambient->color.g, data->ambient->color.b);
	}
	else
		ft_printf("AMBIENT: Not defined\n");
	
	// Print Light data
	if (data->light)
	{
		ft_printf("LIGHT:\n");
		ft_printf("  Coordinates: (%d, %d, %d)\n", 
			(int)data->light->coordinates.x, (int)data->light->coordinates.y, (int)data->light->coordinates.z);
		printf("  Ratio: %0.2f\n", (data->light->ratio));
	}
	else
		ft_printf("LIGHT: Not defined\n");
	
	// Print Camera data
	if (data->camera)
	{
		ft_printf("CAMERA:\n");
		ft_printf("  Coordinates: (%d, %d, %d)\n", 
			(int)data->camera->coordinates.x, (int)data->camera->coordinates.y, (int)data->camera->coordinates.z);
		ft_printf("  Normalized: (%d, %d, %d)\n", 
			(int)data->camera->normalized.x, (int)data->camera->normalized.y, (int)data->camera->normalized.z);
		ft_printf("  FOV: %d degrees\n", (int)data->camera->fov);
	}
	else
		ft_printf("CAMERA: Not defined\n");

	if (data->cylinder)
	{
		ft_printf("CYLINDER:\n");
		ft_printf("  Center: (%d, %d, %d)\n", 
			(int)data->cylinder->center.x, (int)data->cylinder->center.y, (int)data->cylinder->center.z);
		ft_printf("  Normal: (%d, %d, %d)\n", 
			(int)data->cylinder->normal.x, (int)data->cylinder->normal.y, (int)data->cylinder->normal.z);
		ft_printf("  Radius: %d \n", (int)data->cylinder->radius);
		ft_printf("  Height: %d \n", (int)data->cylinder->height);
	}
	else
		ft_printf("CYLINDER: Not defined\n");

	if (data->plane)
	{
		ft_printf("PLANE:\n");
		ft_printf("  Point: (%d, %d, %d)\n", 
			(int)data->plane->point.x, (int)data->plane->point.y, (int)data->plane->point.z);
		ft_printf("  Normal: (%d, %d, %d)\n", 
			(int)data->plane->normal.x, (int)data->plane->normal.y, (int)data->plane->normal.z);
	}
	else
		ft_printf("PLANE: Not defined\n");

	if (data->sphere)
	{
		ft_printf("SPHERE:\n");
		ft_printf("  Center: (%d, %d, %d)\n", 
			(int)data->sphere->center.x, (int)data->sphere->center.y, (int)data->sphere->center.z);
		ft_printf("  Radius: %d \n", (int)data->sphere->radius);
	}
	else
		ft_printf("CYLINDER: Not defined\n");

	ft_printf("========================\n\n");
}

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
		exit_message("Invalid file extension");
	init_minirt(argv[1]);
	return (0);
}
