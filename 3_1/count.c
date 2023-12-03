/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:49 by cumoncoq          #+#    #+#             */
/*   Updated: 2023/12/03 14:04:44 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "count.h"

int ft_issymbol(char c)
{
	if (c == '.' || ft_isdigit(c) || c == '\n')
		return (0);
	return (1);
}

int ft_in_line(char *line, int low, int up)
{
	int i = low;
	while (i <= up)
	{
		if (ft_issymbol(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int ft_is_adjacent(char ** tab, int line, int low, int up)
{
	if(line == 0)
		return(ft_in_line(tab[line], low, up) + ft_in_line(tab[line + 1], low, up));
	if(line == MAP_SIZE - 1)
		return(ft_in_line(tab[line], low, up) + ft_in_line(tab[line - 1], low, up));
	return(ft_in_line(tab[line], low, up) + ft_in_line(tab[line + 1], low, up) + ft_in_line(tab[line - 1], low, up));
}


int ft_len_num(char* line)
{
	int i = 0;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}
int	ft_add_game(char **tab)
{
	int i = 0;
	int j = 0;
	int adj = 0;
	int game = 0;
	while (j < MAP_SIZE)
	{
		while (i < MAP_SIZE)
		{
			if (ft_isdigit(tab[j][i]))
			{
				if (i)
					adj = ft_is_adjacent(tab, j, i - 1, i + ft_len_num(tab[j] + i));
				else
					adj = ft_is_adjacent(tab, j, i, i + ft_len_num(tab[j] + i));
				if (adj)
					game += ft_atoi(tab[j] + i);
				adj = 0;
				i += ft_len_num(tab[j] + i);
			}
			else
				i++;
		}
		i = 0;
		j++;
	}
	return (game);
}

void ft_free_tab(char **tab)
{
	int i = 0;
	while (i < MAP_SIZE)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	char	**tab = (char **)malloc(sizeof(char *) * MAP_SIZE);
	int		fd = open(av[1], O_RDONLY);
	int		total_file = 0;
	char	*line;
	int		i = 0;
	while (i < MAP_SIZE)
	{
		line = get_next_line(fd);
		tab[i] = line;
		if (!line)
		{
			ft_free_tab(tab);
			return (1);
		}
		i++;
	}
	total_file = ft_add_game(tab);
	ft_printf("total_file = %d\n", total_file);
	return (0);
}