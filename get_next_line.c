/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschwarz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 13:39:47 by nschwarz          #+#    #+#             */
/*   Updated: 2017/12/05 14:22:21 by nono             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_open(int const fd, char **stock)
{
	int		i;
	char	*str;
	char	*buf;

	if (!(buf = (char *)malloc(sizeof(*buf) * (BUFF_SIZE + 1))))
		return (-1);
	i = read(fd, buf, BUFF_SIZE);
	if (i > 0)
	{
		buf[i] = '\0';
		str = ft_strjoin(*stock, buf);
		free(*stock);
		*stock = str;
	}
	free(buf);
	return (i);
}

int				get_next_line(int const fd, char **line)
{
	static char	*s = NULL;
	char		*op;
	int			i;

	if ((!s && (s = (char *)malloc(sizeof(*s))) == NULL) || !line
			|| fd < 0 || BUFF_SIZE < 0)
		return (-1);
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
