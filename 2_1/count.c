/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:49 by cumoncoq          #+#    #+#             */
/*   Updated: 2023/12/02 14:52:39 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "count.h"

int ft_isblue(char *line)
{
	if (ft_strncmp(line, "blue", 4) == 0)
		return (1);
	return (0);
}

int ft_isred(char *line)
{
	if (ft_strncmp(line, "red", 3) == 0)
		return (1);
	return (0);
}

int ft_isgreen(char *line)
{
	if (ft_strncmp(line, "green", 5) == 0)
		return (1);
	return (0);
}

int ft_is_impossible(char *line, int i, char color)
{
	int count = 0;

	while (line[i - 1] == ' ')
		i--;
	while (ft_isdigit(line[i - 1]))
		i--;
	count = ft_atoi(line + i);
	if (color == 'r')
		if (count > 12)
			return (1);
	if (color == 'g')
		if (count > 13)
			return (1);
	if (color == 'b')
		if (count > 14)
			return (1);
	return (0);
}

int	ft_add_game(char *line)
{
	int i = 0;
	int game = 0;
	int impossible = 0;

	while (!ft_isdigit(line[i]))
		i++;
	game = ft_atoi(line + i);
	while (line[i] != ':')
		i++;
	while(line[i])
	{
		if (ft_isred(line + i))
		{
			impossible |= ft_is_impossible(line, i, 'r');
			i += 3;
		}
		else if (ft_isgreen(line + i))
		{
			impossible |= ft_is_impossible(line, i, 'g');
			i += 5;
		}
		else if (ft_isblue(line + i))
		{
			impossible |= ft_is_impossible(line, i, 'b');
			i += 4;
		}
		else
			i++;
	}
	if (!impossible)
		return (game);
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int	fd = open(av[1], O_RDONLY);
	char *line = get_next_line(fd);
	int total_file = 0;
	while (line)
	{
		total_file += ft_add_game(line);
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("total_file = %d\n", total_file);
}