/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:37:27 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:04:50 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_child(t_data *d, int fd[2], char *av)
{
	t_exe	exe;

	ft_close(d, fd[0]);
	if (d->i == d->ac - 1)
		ft_dup2(d, d->outfile, STDOUT_FILENO);
	else
		ft_dup2(d, fd[1], STDOUT_FILENO);
	ft_close(d, fd[1]);
	exe = ft_get_cmd(d, av);
	if (!exe.cmd || !exe.path)
		exit(EXIT_FAILURE);
	exe.ret = execve(exe.path, exe.cmd, d->env);
	free(exe.path);
	ft_mfree((void **)exe.cmd, ft_mstrlen(exe.cmd));
	if (exe.ret == -1)
		ft_error(d, strerror(errno), NULL);
}

static void	ft_parent(t_data *d, int fd[2])
{
	ft_close(d, fd[1]);
	ft_dup2(d, fd[0], STDIN_FILENO);
	ft_close(d, fd[0]);
}

static void	ft_pipe_cmd(t_data *d, char *av)
{
	int		fd[2];
	pid_t	pid;

	pid = ft_pipe_fork(d, fd);
	if (pid == 0)
		ft_child(d, fd, av);
	else
		ft_parent(d, fd);
}

void	ft_pipex(t_data *d)
{
	if (d->limiter)
		ft_here_doc(d);
	d->i = 0;
	while (d->i < d->ac)
	{
		ft_pipe_cmd(d, d->av[d->i]);
		d->i++;
	}
	d->i = 0;
	while (d->i < d->ac)
	{
		ft_waitpid(d, -1, &d->status, 0);
		d->i++;
	}
	if (WIFEXITED(d->status))
		d->status = WEXITSTATUS(d->status);
	else
		d->status = 0;
}
