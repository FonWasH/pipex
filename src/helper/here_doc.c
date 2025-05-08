/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 02:41:15 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:04:44 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_child(t_data *d, int fd[2])
{
	char	*line;

	ft_close(d, fd[0]);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, d->limiter, ft_strlen(d->limiter)))
			exit(EXIT_SUCCESS);
		ft_write(d, fd[1], line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

static void	ft_parent(t_data *d, int fd[2])
{
	ft_close(d, fd[1]);
	ft_dup2(d, fd[0], STDIN_FILENO);
	ft_close(d, fd[0]);
	ft_wait(d, NULL);
}

void	ft_here_doc(t_data *d)
{
	int		fd[2];
	pid_t	pid;

	pid = ft_pipe_fork(d, fd);
	if (pid == 0)
		ft_child(d, fd);
	else
		ft_parent(d, fd);
}
