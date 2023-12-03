/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:49 by cumoncoq          #+#    #+#             */
/*   Updated: 2023/12/03 17:59:51 by cumoncoq         ###   ########.fr       */
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
		if (ft_isdigit(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_back_and_atoi(char *line, int i)
{
	while (i && ft_isdigit(line[i - 1]))
		i--;
	return (ft_atoi(line + i));
}

int *ft_around(char **tab, int line, int i)
{
	int *added = (int *)ft_calloc(sizeof(int), 8);
	if (line)
	{
		if (i && ft_isdigit(tab[line - 1][i - 1]))
			added[0] = 1;
		if (ft_isdigit(tab[line - 1][i]) && !ft_isdigit(tab[line - 1][i - 1]))
			added[1] = 1;
		if (ft_isdigit(tab[line - 1][i + 1]) && !ft_isdigit(tab[line - 1][i]))
			added[2] = 1;
	}
	if (i && ft_isdigit(tab[line][i - 1]))
		added[3] = 1;
	if (ft_isdigit(tab[line][i + 1]))
		added[4] = 1;
	if (line < MAP_SIZE - 1)
	{
		if (i && ft_isdigit(tab[line + 1][i - 1]))
			added[5] = 1;
		if (ft_isdigit(tab[line + 1][i]) && !ft_isdigit(tab[line + 1][i - 1]))
			added[6] = 1;
		if (ft_isdigit(tab[line + 1][i + 1]) && !ft_isdigit(tab[line + 1][i]))
			added[7] = 1;
	}
	return (added);
}

size_t ft_is_adjacent(char ** tab, int line, int col)
{
	int i = 0;
	size_t adj = 0;
	int *added;

	added = ft_around(tab, line, col);
	while (i < 8)
	{
		if (added[i])
			adj++;
		i++;
	}
	if (adj != 2)
		return (0);
	adj = 1;
	if (added[0])
		adj *= ft_back_and_atoi(tab[line - 1], col - 1);
	if (added[1])
		adj *= ft_back_and_atoi(tab[line - 1], col);
	if (added[2])
		adj *= ft_back_and_atoi(tab[line - 1], col + 1);
	if (added[3])
		adj *= ft_back_and_atoi(tab[line], col - 1);
	if (added[4])
		adj *= ft_back_and_atoi(tab[line], col + 1);
	if (added[5])
		adj *= ft_back_and_atoi(tab[line + 1], col - 1);
	if (added[6])
		adj *= ft_back_and_atoi(tab[line + 1], col);
	if (added[7])
		adj *= ft_back_and_atoi(tab[line + 1], col + 1);
	free(added);
	return (adj);
}


int ft_len_num(char* line)
{
	int i = 0;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}
size_t	ft_add_game(char **tab)
{
	int i = 0;
	int j = 0;
	size_t game = 0;
	while (j < MAP_SIZE)
	{
		while (i < MAP_SIZE)
		{
			if (ft_issymbol(tab[j][i]))
				game += ft_is_adjacent(tab, j, i);
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
	ft_printf("MAP_SIZE = %d\n", MAP_SIZE);
	if (ac != 2)
		return (1);
	char	**tab = (char **)malloc(sizeof(char *) * MAP_SIZE);
	int		fd = open(av[1], O_RDONLY);
	size_t		total_file = 0;
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
	ft_free_tab(tab);
	return (0);
}