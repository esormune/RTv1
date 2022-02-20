/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 22:15:36 by esormune          #+#    #+#             */
/*   Updated: 2021/05/17 12:50:31 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_done(char **line)
{
	*line = NULL;
	return (0);
}

static char	*check_end(char ptr, char *str)
{
	if (ptr == '\0')
		return (NULL);
	else
		return (str);
}

static int	new_line(char **save, int fd, int ret, char **line)
{
	char		*temp;
	size_t		len;

	len = 0;
	if (ret < 0)
		return (-1);
	while (save[fd][len] != '\0' && (save[fd][len] != '\n'))
		len++;
	if (save[fd][len] == '\n')
	{
		*line = ft_strsub(save[fd], 0, len);
		temp = ft_strdup(&save[fd][len + 1]);
		free(save[fd]);
		save[fd] = check_end(*temp, temp);
		if (*temp == '\0')
			free(temp);
	}
	else if (save[fd][len] == '\0')
	{
		*line = ft_strdup(save[fd]);
		ft_strdel(&save[fd]);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	char		*temp;
	int			ret;
	static char	*save[4096];

	ret = 0;
	if (fd < 0 || BUFF_SIZE <= 0 || line == NULL || fd > 4096)
		return (-1);
	while (1)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret <= 0)
			break ;
		buf[ret] = '\0';
		temp = ft_strjoin(save[fd], buf);
		if (!temp)
			return (-1);
		free(save[fd]);
		save[fd] = temp;
		if (ft_strchr(save[fd], '\n'))
			break ;
	}
	if (ret == 0 && save[fd] == NULL)
		return (return_done(line));
	return (new_line(save, fd, ret, line));
}
