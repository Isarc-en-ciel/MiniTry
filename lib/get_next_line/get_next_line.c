/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:27:00 by csteylae          #+#    #+#             */
/*   Updated: 2024/07/08 13:38:35 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	init_values(char **str, char *tab)
{
	size_t	len;

	if (!tab)
		return ;
	len = ft_strlen_gnl(tab);
	*str = (char *)malloc(sizeof(char) * (len + 1));
	if (!*str)
		return ;
	ft_memcpy_gnl(*str, tab, len);
	*(*str + len) = '\0';
	len = 0;
	while (len != (BUFFER_SIZE + 1))
	{
		tab[len] = '\0';
		len++;
	}
}

char	*read_until_end_of_line_or_eof(int fd, char *line)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	bytes_read = 1;
	while (ft_strchr_gnl(line, '\n') == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_memfree(line));
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		line = ft_strjoin_gnl(line, buffer);
		if (!line)
			return (NULL);
	}
	if (ft_strlen_gnl(line) == 0)
		return (ft_memfree(line));
	return (line);
}

void	update_next_line_value(char *str, char *tab)
{
	size_t	i;

	i = 0;
	str = ft_strchr_gnl(str, '\n');
	if (!str)
		return ;
	str = str + 1;
	i = ft_strlen_gnl(str);
	ft_memcpy_gnl(tab, str, i);
}

char	*create_line(char *line)
{
	size_t	i;
	char	*new_line;

	i = 0;
	new_line = NULL;
	while (line[i] != '\n' && line[i])
		i++;
	i = i + 1;
	if (!ft_strchr_gnl(line, '\n'))
		i = i - 1;
	new_line = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (ft_memfree(line));
	ft_memcpy_gnl(new_line, line, i);
	ft_memfree(line);
	new_line[i] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	next_line[BUFFER_SIZE + 1] = "";
	char		*line;

	line = NULL;
	if (fd < 0)
		return (NULL);
	init_values(&line, next_line);
	if (!line)
		return (NULL);
	line = read_until_end_of_line_or_eof(fd, line);
	if (!line)
		return (ft_memfree(line));
	update_next_line_value(line, next_line);
	line = create_line(line);
	if (!line)
		return (ft_memfree(line));
	return (line);
}
//
//#include <fcntl.h>
//#include <stdio.h>
//int main(int argc, char **argv)
//{
////   int fd = open("one_line_no_nl.txt", O_RDONLY);
//    int fd = open("file3.txt", O_RDONLY);
//    (void)argc;
//    (void)argv;
//     char *str = NULL;
//   str = get_next_line(fd);
//   printf("%s", str);
//   free(str);
//   while(str)
//   {
//       str = get_next_line(fd);
//       printf("%s", str);
//       free(str);
//   }
//   return(0);
//}
//  
