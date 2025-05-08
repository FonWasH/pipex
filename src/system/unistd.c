/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unistd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:20:59 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:05:01 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open(t_data *d, char *path, t_openf flag)
{
	int	fd;

	fd = 0;
	if (flag == WR_APPEND)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (flag == WR_TRUNC)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == RD)
		fd = open(path, O_RDONLY, 0777);
	if (fd == -1)
		ft_error(d, strerror(errno), path);
	return (fd);
}

void	ft_close(t_data *d, int fd)
{
	if (fd == -1)
		return ;
	if (close(fd) == -1)
		ft_error(d, strerror(errno), NULL);
}

void	ft_write(t_data *d, int fd, char *str)
{
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		ft_close(d, fd);
		ft_error(d, strerror(errno), NULL);
	}
}

void	ft_dup2(t_data *d, int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		ft_close(d, oldfd);
		ft_close(d, newfd);
		ft_error(d, strerror(errno), NULL);
	}
}

pid_t	ft_pipe_fork(t_data *d, int fd[2])
{
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_error(d, strerror(errno), NULL);
	pid = fork();
	if (pid == -1)
	{
		ft_close(d, fd[0]);
		ft_close(d, fd[1]);
		ft_error(d, strerror(errno), NULL);
	}
	return (pid);
}
