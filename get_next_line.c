/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:00:48 by lantonio          #+#    #+#             */
/*   Updated: 2024/05/23 07:55:51 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	remove_line(char **nxtline)
{
	char	*nl;
	char	*tmp;
	size_t	i;
	size_t	j;

	nl = ft_strchr(*nxtline, '\n');
	if (!nl)
	{
		free(*nxtline);
		*nxtline = NULL;
		return ;
	}
	tmp = malloc((ft_strlen(nl)) * sizeof(char));
	i = 0;
	j = ft_strlen(*nxtline) - ft_strlen(nl) + 1;
	while (j < ft_strlen(*nxtline))
		tmp[i++] = (*nxtline)[j++];
	tmp[i] = '\0';
	free(*nxtline);
	*nxtline = tmp;
	if (**nxtline == 0)
	{
		free(*nxtline);
		*nxtline = NULL;
	}
}

static void	get_line(char **nxtline, char **line)
{
	char	*nl;
	size_t	len;
	size_t	i;

	nl = ft_strchr(*nxtline, '\n');
	len = ft_strlen(*nxtline) - ft_strlen(nl) + 2;
	*line = (char *)malloc(len * sizeof(char));
	if (!line)
		return ;
	i = -1;
	while (++i < (len - 1))
		(*line)[i] = (*nxtline)[i];
	(*line)[i] = '\0';
}

static int	line_reader(int fd, char **nxtline, char *buffer)
{
	char	*tmp;
	int		bytes;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0 || buffer == NULL)
	{
		free (*nxtline);
		*nxtline = NULL;
		return (-1);
	}
	if (bytes == 0)
		return (bytes);
	tmp = ft_strjoin(*nxtline, buffer);
	free(*nxtline);
	*nxtline = tmp;
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*nxtline;
	char		*line;
	char		*buffer;
	int			bytes;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	bytes = 1;
	while (ft_strchr(nxtline, '\n') == NULL
		&& bytes > 0)
		bytes = line_reader(fd, &nxtline, buffer);
	free(buffer);
	if (bytes == -1 || ft_strlen(nxtline) == 0)
		return (NULL);
	get_line(&nxtline, &line);
	remove_line(&nxtline);
	return (line);
}

/*int	main(void)
{
	char	*linha;
	int		i;
	int		fd1;

	fd1 = open("../files/test.txt", O_RDONLY);
	i = 1;
	while (i < 12)
	{
		linha = get_next_line(fd1);
		printf("%s", linha);
		i++;
	}
	close(fd1);
	return (0);
}
*/