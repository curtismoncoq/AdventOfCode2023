/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:49 by cumoncoq          #+#    #+#             */
/*   Updated: 2023/12/03 14:02:17 by cumoncoq         ###   ########.fr       */
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

int	ft_add_game(char *line)
{
	int i = 0;
	int worth = 0;
	int max_r = 0;
	int max_g = 0;
	int max_b = 0;

	while (!ft_isdigit(line[i]))
		i++;
	while (line[i] != ':')
		i++;
	while(line[i])
	{
		if (ft_isred(line + i))
		{
			worth = ft_is_worth(line, i);
			if (worth > max_r)
				max_r = worth;
			i += 3;
		}
		else if (ft_isgreen(line + i))
		{
			worth = ft_is_worth(line, i);
			if (worth > max_g)
				max_g = worth;
			i += 5;
		}
		else if (ft_isblue(line + i))
		{
			worth = ft_is_worth(line, i);
			if (worth > max_b)
				max_b = worth;
			i += 4;
		}
		else
			i++;
	}
	return (max_r * max_g * max_b);
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
	return (0);
}