/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldinc <aldinc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:09:50 by aldinc            #+#    #+#             */
/*   Updated: 2024/11/13 18:09:52 by aldinc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
	if (!temp)
		return (NULL);
	if (!buf)
		buf = ft_strdup("");
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
	static char	*buf = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_append_to_left_one(fd, buf);
	if (!buf || !*buf)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	line = ft_get_line(buf);
	buf = ft_after_newline(buf);
	return (line);
}
