/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:49 by cumoncoq          #+#    #+#             */
/*   Updated: 2023/12/03 14:02:33 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "count.h"

/*
**	I don't know how to do it better yet :(
*/
int	ft_spelled(char *line)
{
	if (ft_strncmp(line, "one", 3) == 0)
		return (1);
	if (ft_strncmp(line, "two", 3) == 0)
		return (2);
	if (ft_strncmp(line, "three", 5) == 0)
		return (3);
	if (ft_strncmp(line, "four", 4) == 0)
		return (4);
	if (ft_strncmp(line, "five", 4) == 0)
		return (5);
	if (ft_strncmp(line, "six", 3) == 0)
		return (6);
	if (ft_strncmp(line, "seven", 5) == 0)
		return (7);
	if (ft_strncmp(line, "eight", 5) == 0)
		return (8);
	if (ft_strncmp(line, "nine", 4) == 0)
		return (9);
	return (0);
}

int	ft_add_both(char *line)
{
	int i = 0;
	int s = 0;
	int first = 0;
	int last = 0;

	while(line[i])
	{
		if (ft_isdigit(line[i]))
		{
			first = (line[i] - 48) * 10;
			break ;
		}
		s = ft_spelled(line + i);
		if (s)
		{
			first = s * 10;
			break ;
		}
		i++;
	}
	while(line[i])
	{
		if (ft_isdigit(line[i]))
		{
			last = (line[i] - 48);
		}
		s = ft_spelled(line + i);
		if (s)
			last = s;
		i++;
	}
	return (first + last);
}

int main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	int	fd = open(av[1], O_RDONLY);
	char *line = get_next_line(fd);
	int total_file = 0;
	while (line)
	{
		total_file += ft_add_both(line);
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("total_file = %d\n", total_file);
	return (0);
}
