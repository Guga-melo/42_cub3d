/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:22:18 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/17 12:19:01 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	**convert_texture(char **texture_line, char **hex_color, int i, int j)
{
	int		**texture;
	char	*texture_char;
	char	**buffer;

	texture = malloc(sizeof(int *) * 64);
	buffer = hex_color;
	while (*texture_line)
	{
		texture[++i] = malloc(sizeof(int) * 64);
		texture_char = *texture_line;
		j = -1;
		while (*texture_char && ++j < 64)
		{
			hex_color = buffer;
			while (*hex_color)
			{
				if (*texture_char == *hex_color[0])
					texture[i][j] = ft_atoi_base(&(*hex_color)[1], 16);
				hex_color++;
			}
			texture_char++;
		}
		texture_line++;
	}
	return (texture);
}

int	rgb_to_hex(char *rgb)
{
	char	**buffer;
	int		*rgb_value;
	int		hex_value;
	int		i;

	rgb_value = malloc(3 * sizeof(int));
	buffer = ft_split(rgb, ',');
	i = -1;
	while (++i < 3)
		rgb_value[i] = ft_atoi(buffer[i]);
	free_charpp(buffer);
	hex_value = (rgb_value[0] << 16) | (rgb_value[1] << 8) | rgb_value[2];
	free(rgb_value);
	return (hex_value);
}

void	getting_hex_colors(char **line, char **hex_line, int fd)
{
	char	*aux;

	*line = check_line(*line);
	aux = ft_strjoin(*hex_line, *line);
	free(*hex_line);
	*hex_line = ft_strdup(aux);
	free(aux);
	free(*line);
	*line = get_next_line(fd);
}

void	check_commas(char *floor, char *ceiling)
{
	int	i;

	i = -1;
	if (floor[0] == ',')
		exit_error("Invalid floor value");
	while (floor[++i])
		if (floor[i] == ',' && floor[i + 1] == ',')
			exit_error("Invalid floor value");
	if (floor[i - 1] == ',')
		exit_error("Invalid floor value");
	i = -1;
	if (ceiling[0] == ',')
		exit_error("Invalid ceiling value");
	while (ceiling[++i])
		if (ceiling[i] == ',' && ceiling[i + 1] == ',')
			exit_error("Invalid ceiling value");
	if (ceiling[i - 1] == ',')
		exit_error("Invalid ceiling value");
}

void	check_floor_and_ceiling(char *floor, char *ceiling)
{
	char	**buffer;
	int		i;

	check_commas(floor, ceiling);
	buffer = ft_split(floor, ',');
	i = -1;
	while (buffer[++i])
	{
		if (ft_atoi(buffer[i]) < 0 || ft_atoi(buffer[i]) > 255)
			exit_error("Invalid floor value");
	}
	if (i != 3)
		exit_error("Invalid floor value");
	free_charpp(buffer);
	buffer = ft_split(ceiling, ',');
	i = -1;
	while (buffer[++i])
	{
		if (ft_atoi(buffer[i]) < 0 || ft_atoi(buffer[i]) > 255)
			exit_error("Invalid ceiling value");
	}
	if (i != 3)
		exit_error("Invalid ceiling value");
	free_charpp(buffer);
}
