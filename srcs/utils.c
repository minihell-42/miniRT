#include "miniRT.h"

static int skip_spaces(char *line, int i)
{
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

static char	*normalize_line(char *line)
{
	int i;
	int j;
	int in_token;

	i = 0;
	j = 0;
	in_token = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			if (in_token)
				line[j++] = '\t';
			in_token = 0;
			i = skip_spaces(line, i);
		}
		else
		{
			line[j++] = line[i++];
			in_token = 1;
		}
	}
	line[j] = '\0';
	return (line);
}

char	*clean_line(char *line)
{
	int	i;

	if (!line)
		return (NULL);
	normalize_line(line);
	i = 0;
	while (line[i] && line[i] != '#')
		i++;
	line[i] = '\0';
	i = ft_strlen(line) - 1;
	while (i >= 0 && ft_isspace(line[i]))
	{
		line[i] = '\0';
		i--;
	}
	return (line);
}
