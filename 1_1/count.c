/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:41:49 by cumoncoq          #+#    #+#             */
/*   Updated: 2023/12/01 21:12:29 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "count.h"

int	ft_add_both(char *line)
{
	int i = 0;
	int first = 0;
	int last = 0;

	while(line[i])
	{
		if (ft_isdigit(line[i]))
		{
			first = i;
			break ;
		}
		i++;
	}
	while(line[i])
	{
		if (ft_isdigit(line[i]))
		{
			last = i;
		}
		i++;
	}
	return (((line[first] - 48) * 10) + (line[last] - 48));
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
}