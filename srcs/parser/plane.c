#include "miniRT.h"

void	parse_plane(char *line, t_data *data)
{
	char	**tokens;
	t_vector	point;
	t_vector	normal;
	// t_color	color;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
		exit_free_all("Invalid plane line format", data, tokens);
	if (!validate_coordinates(tokens[1], &point))
		exit_free_all("Invalid coordinates format for plane", data, tokens);
	if (!validate_coordinates(tokens[2], &normal))
		exit_free_all("Invalid normalized vector format for plane", data, tokens);
	// if (!validate_color(tokens[3], &color))
	// 	exit_free_all("Invalid color format for plane", data, tokens);
	data->plane->point = point;
	data->plane->normal = normal;
	free_array(tokens);
}
