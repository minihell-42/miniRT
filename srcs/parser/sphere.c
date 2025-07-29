#include "miniRT.h"

void	parse_sphere(char *line, t_data *data)
{
	char	**tokens;
	t_vector	center;
	float	radius;
	// t_color	color;

	(void)data;
	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
		exit_free_all("Invalid sphere line format", data, tokens);
	if (!validate_coordinates(tokens[1], &center))
		exit_free_all("Invalid coordinates format for sphere", data, tokens);
	if (!validate_positive_float(tokens[2], &radius))
		exit_free_all("Sphere radius must be positive", data, tokens);
	// if (!validate_color(tokens[3], &color))
	// 	exit_free_all("Invalid color format for sphere", data, tokens);
	data->sphere->center = center;
	data->sphere->radius = radius;
	free_array(tokens);
}
