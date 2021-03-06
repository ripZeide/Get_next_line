/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/11 22:19:50 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 21:22:28 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		past_line(char **str, char **line, const int fd)
{
	int		i;

	i = 0;
	if (str[fd][i])
	{
		if (ft_strchr(str[fd], '\n'))
		{
			while (str[fd][i] != '\n' && str[fd][i])
				i++;
			if (!(*line = ft_strsub(str[fd], 0, i)))
				return (-1);
			str[fd] = &str[fd][i + 1];
			return (1);
		}
		if (!(*line = ft_strdup(str[fd])))
			return (-1);
		str[fd][0] = '\0';
	}
	return (-1);
}

int		get_next_line(const int fd, char **line)
{
	int				ret;
	char			buff[BUFF_SIZE + 1];
	static char		*str[10240];
	char			*tmp;

	if (fd < 0 || !line || read(fd, buff, 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (!str[fd])
		str[fd] = ft_strnew(0);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		tmp = str[fd];
		if (!(str[fd] = ft_strjoin(tmp, buff)))
			return (-1);
		if (ft_strlen(tmp))
			free(tmp);
		if (ret < 0)
			return (-1);
	}
	if (str[fd][0] == '\0')
		return (0);
	past_line(str, line, fd);
	return (1);
}

int		main(int argc, char **argv)
{
	int	fd;
	char*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	if (argc == 2)
		close(fd);
}
