/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamashis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 08:07:59 by kamashis          #+#    #+#             */
/*   Updated: 2018/01/29 11:25:28 by kamashis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		reading_content(const int fd, char **line)
{
	int		content_read;
	char	*buffer;
	char	*temp;

	if (!(buffer = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	content_read = read(fd, buffer, BUFF_SIZE);
	if (content_read > 0)
	{
		buffer[content_read] = '\0';
		temp = ft_strjoin(*line, buffer);
		free(*line);
		*line = temp;
	}
	free(buffer);
	return (content_read);
}

static void		string_join(char **holder, char *s1, char *s2)
{
	char	*temp;

	temp = *holder;
	*holder = ft_strjoin(s1, s2);
	free(temp);
}

static void		string_dup(char **holder, char *s1)
{
	char	*temp;

	temp = *holder;
	*holder = ft_strdup(s1);
	free(temp);
}

int				get_next_line(const int fd, char **line)
{
	static char		*stock = NULL;
	char			*eol_buffer;
	int				characters_read;

	if ((!stock && (stock = (char *)malloc(sizeof(*stock))) == NULL) ||
			!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	eol_buffer = ft_strchr(stock, '\n');
	while (eol_buffer == NULL)
	{
		characters_read = reading_content(fd, &stock);
		if (characters_read == 0)
		{
			if (ft_strlen(stock) == 0)
				return (0);
			string_join(&stock, stock, "\n");
		}
		if (characters_read < 0)
			return (-1);
		else
			eol_buffer = ft_strchr(stock, '\n');
	}
	*line = ft_strsub(stock, 0, ft_strlen(stock) - ft_strlen(eol_buffer));
	string_dup(&stock, &(eol_buffer[1]));
	return (1);
}
