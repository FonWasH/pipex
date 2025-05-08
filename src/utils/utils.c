/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:42 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:05:14 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_init_exec_cmd(t_exe *exe)
{
	exe->cmd = NULL;
	exe->path = NULL;
}

static void	ft_free_exec_cmd(t_exe *exe)
{
	ft_mfree((void **)exe->cmd, ft_mstrlen(exe->cmd));
	exe->cmd = NULL;
}

static char	*ft_get_cmd_path(t_data *d, char *cmd)
{
	char	**paths;
	char	*cmd_path;
	size_t	i;

	paths = ft_split(d->env_path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
			return (ft_mfree((void **)paths, ft_mstrlen(paths)),
				free(cmd), NULL);
		if (!access(cmd_path, F_OK))
			return (ft_mfree((void **)paths, ft_mstrlen(paths)),
				free(cmd), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_puterror(ERROR_CMD, cmd + 1),
		ft_mfree((void **)paths, ft_mstrlen(paths)), free(cmd), NULL);
}

t_exe	ft_get_cmd(t_data *d, char *av)
{
	t_exe	exe;
	char	*cmd;

	ft_init_exec_cmd(&exe);
	if (!*av)
		return (ft_puterror(ERROR_CMD, NULL), exe);
	exe.cmd = ft_split(av, ' ');
	if (!exe.cmd)
		return (exe);
	if (!access(exe.cmd[0], F_OK))
	{
		exe.path = ft_strdup(exe.cmd[0]);
		if (!exe.path)
			return (ft_free_exec_cmd(&exe), exe);
		return (exe);
	}
	cmd = ft_strjoin("/", exe.cmd[0]);
	if (!cmd)
		return (ft_free_exec_cmd(&exe), exe);
	exe.path = ft_get_cmd_path(d, cmd);
	if (!exe.path)
		ft_free_exec_cmd(&exe);
	return (exe);
}
