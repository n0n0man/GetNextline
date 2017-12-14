/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschwarz <nschwarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:42:21 by nschwarz          #+#    #+#             */
/*   Updated: 2017/12/14 14:42:26 by nschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(const int fd, char **to_read, int *i)
{
	char	tmp[BUFF_SIZE + 1];
	char	*stock;

	*i = read(fd, tmp, BUFF_SIZE);
	tmp[*i] = '\0';
	stock = to_read[fd];
	to_read[fd] = ft_strjoin(stock, tmp);
	ft_memdel((void**)&stock);
	return (to_read[fd]);
}

int		get_next_line(const int fd, char **line)
{
	static char *s[4096];
	int			ret;
	char		*str;

	if (!(line) || fd < 0 || fd > 4096)
		return (-1);
	if ((ret = 1) && !(s[fd]))
		s[fd] = ft_strnew(0);
	while (ret > 0)
	{
		if ((s[fd] = ft_read(fd, s, &ret)) && ret < 0)
			return (-1);
		if ((str = ft_memchr(s[fd], '\n', ft_strlen(s[fd]))))
		{
			*str = '\0';
			*line = ft_strdup(s[fd]);
			ft_memmove(s[fd], str + 1, ft_strlen(str + 1) + 1);
			return (1);
		}
	}
	if ((*s[fd]) && (*line = ft_strdup(s[fd])))
		if ((str = ft_memchr(s[fd], '\0', ft_strlen(s[fd]) + 1)) &&
			(ft_memmove(s[fd], str + 1, ft_strlen(str + 1) + 1)))
			return (1);
	return (0);
}
