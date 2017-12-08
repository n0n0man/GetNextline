/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschwarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 13:39:47 by nschwarz          #+#    #+#             */
/*   Updated: 2017/12/08 15:45:24 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_open(int const fd, char **stock)
{
	int		i;
	char	*str;
	char	buf[BUFF_SIZE];

	i = read(fd, buf, BUFF_SIZE);
	if (i > 0)
	{
		buf[i] = '\0';
		if(!*stock)
			*stock = ft_strdup(buf);
		else
		{
			str = ft_strjoin(*stock, buf);
			free(*stock);
			*stock = str;
		}
	}
	return (i);
}

int				get_next_line(int const fd, char **line)
{
	static char	*s = NULL;
	char		*op = NULL;
	int			i;

	if (!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	if (s)
		op = ft_strchr(s, '\n');
	while (op == NULL)
	{
		i = ft_open(fd, &s);
		if (i == 0)
		{
			if (ft_strlen(s) == 0)
				return (0);
			s = ft_strjoin(s, "\n");
		}
		if (i < 0)
			return (-1);
		else
			op = ft_strchr(s, '\n');
	}
	*line = ft_strsub(s, 0, ft_strlen(s) - ft_strlen(op));
	s = ft_strdup(op + 1);
	return (1);
}
