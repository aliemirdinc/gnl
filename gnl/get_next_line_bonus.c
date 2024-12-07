/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldinc <aldinc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:09:25 by aldinc            #+#    #+#             */
/*   Updated: 2024/11/13 18:09:27 by aldinc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

char	*ft_get_line(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (ft_substr(str, 0, i));
}

char	*ft_append_to_left_one(int fd, char *buf)
{
	char	*temp;
	int		read_bytes;
	char	*new_buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(BUFFER_SIZE + 1);
	if (!buf)
		buf = ft_strdup("");
	if (!temp)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(buf, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, temp, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(buf), free(temp), NULL);
		temp[read_bytes] = '\0';
		new_buf = ft_strjoin(buf, temp);
		free(buf);
		buf = new_buf;
	}
	return (free(temp), buf);
}

char	*ft_after_newline(char *input_str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	if (!input_str)
		return (NULL);
	while (input_str[i] && input_str[i] != '\n')
		i++;
	if (!input_str[i] || !input_str[i + 1])
	{
		free(input_str);
		return (NULL);
	}
	result = (char *)malloc(sizeof(char) * (ft_strlen(input_str) - i));
	if (!result)
		return (NULL);
	i++;
	j = 0;
	while (input_str[i])
		result[j++] = input_str[i++];
	result[j] = '\0';
	free(input_str);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buf[4242];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 4242)
		return (NULL);
	buf[fd] = ft_append_to_left_one(fd, buf[fd]);
	if (!buf[fd] || !*buf[fd])
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(buf[fd]);
	buf[fd] = ft_after_newline(buf[fd]);
	return (line);
}
