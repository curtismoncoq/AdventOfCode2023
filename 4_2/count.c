/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:49 by cumoncoq          #+#    #+#             */
/*   Updated: 2023/12/04 18:32:19 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "count.h"

int ft_len_num(char* line)
{
	int i = 0;
	while (ft_isdigit(line[i]))
		i++;
	return (i);
}

int ft_is_worth(char *line, int i)
{
	int count = 0;

	while (line[i - 1] == ' ')
		i--;
	while (ft_isdigit(line[i - 1]))
		i--;
	count = ft_atoi(line + i);
	return (count);
}

int ft_is_present(char *line, int num)
{
	int i = 0;
	
	while (line[i] != '|')
		i++;
	while(line[i] && line[i] != '\n')
	{
		if (ft_isdigit(line[i]))
		{
			if (num == ft_atoi(line + i))
				return (1);
			i += ft_len_num(line + i);
		}
		else
			i++;
	}
	return (0);
}

int	ft_add_game(char *line)
{
	int i = 0;
	int worth = 0;

	while (line[i] != ':')
		i++;
	while(line[i] && line[i] != '|')
	{
		if (ft_isdigit(line[i]))
		{
			if (ft_is_present(line, ft_atoi(line + i)))
			{
					worth++;
			}
			i += ft_len_num(line + i);
		}
		else
			i++;
	}
	return (worth);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int	fd = open(av[1], O_RDONLY);
	char *line = get_next_line(fd);
	int total_file = 0;
	int i = 0;
	int j = 0;
	int game = 0;
	int *tab = (int *)ft_calloc(sizeof(int), NB_GAMES);
	while (i < NB_GAMES)
		tab[i++] = 1;
	i = 0;
	while (line)
	{
		game = ft_add_game(line);
		ft_printf("game %d: %d, tabi: %d  \n", i, game, tab[i]);
		total_file += tab[i];
		while (j < game && i + j < NB_GAMES)
			tab[i + j++ + 1] += tab[i];
		free(line);
		line = get_next_line(fd);
		j = 0;
		i++;
	}
	ft_printf("total_file = %d\n", total_file);
	return (0);
}