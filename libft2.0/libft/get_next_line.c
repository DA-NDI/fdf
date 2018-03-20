/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:42:28 by avolgin           #+#    #+#             */
/*   Updated: 2018/01/20 20:41:26 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

static t_list	*ft_get_fd(t_list **buff, int fd)
{
	t_list		*temp;

	temp = *buff;
	while (temp)
	{
		if ((int)temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	if (!(temp = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	temp->content = ft_memalloc(1);
	ft_bzero(temp->content, 1);
	temp->content_size = fd;
	temp->next = NULL;
	ft_lstadd(buff, temp);
	temp = *buff;
	return (temp);
}

static int		read_fd(t_list **buff, int fd)
{
	char	*tmp;
	int		ret;
	char	*free_me;

	ret = 0;
	tmp = ft_memalloc(BUFF_SIZE + 1);
	while (!(ft_strchr((*buff)->content, '\n'))
		&& (ret = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		tmp[ret] = '\0';
		free_me = (*buff)->content;
		(*buff)->content = ft_strjoin((char*)(*buff)->content, tmp);
		ft_memdel((void**)&free_me);
	}
	ft_memdel((void**)&tmp);
	return (ret == -1) ? 0 : 1;
}

static int		write_slash_n_to_buff(t_list **buff)
{
	char	*ptr;

	ptr = ft_strchr((*buff)->content, '\n');
	if (ptr)
	{
		(*buff)->content = ptr + 1;
		(*buff)->content = ft_strdup((*buff)->content);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head = NULL;
	t_list			*buff;
	char			*tmp2;

	if (fd < 0 || fd > LIMIT_FD || line == NULL || BUFF_SIZE < 1)
		return (-1);
	buff = ft_get_fd(&head, fd);
	if (!(read_fd(&buff, fd)))
		return (-1);
	if (!((char*)buff->content)[0])
		return (0);
	if (!ft_strchr(buff->content, '\n') && buff->content)
	{
		*line = ft_strdup(buff->content);
		((char*)buff->content)[0] = '\0';
		return (1);
	}
	else
		*line = ft_strsub(buff->content, 0,
		ft_strchr(buff->content, '\n') - (char*)buff->content);
	tmp2 = buff->content;
	if (!write_slash_n_to_buff(&buff))
		return (0);
	ft_memdel((void**)&tmp2);
	return (1);
}
