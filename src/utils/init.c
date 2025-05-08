/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:01:04 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:05:09 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_get_env_path(t_data *d, char **env)
{
	size_t	i;

	i = 0;
	while (!ft_strnstr(env[i], PATH, PATH_LEN))
		i++;
	if (!env[i])
		ft_error(d, ERROR_ENV, PATH);
	return (ft_strchr(env[i], '=') + 1);
}

void	ft_init_data(t_data *d, int ac, char *av[], char *env[])
{
	d->ac = ac - 3;
	d->av = av + 2;
	d->env_path = ft_get_env_path(d, env);
	d->env = env;
	d->limiter = NULL;
	d->infile = -1;
	d->outfile = -1;
	if (!ft_strncmp(av[1], HERE_DOC, ft_strlen(av[1])))
	{	
		d->limiter = av[2];
		d->ac -= 1;
		d->av += 1;
		d->outfile = ft_open(d, av[ac - 1], WR_APPEND);
	}
	else
	{
		d->infile = ft_open(d, av[1], RD);
		ft_dup2(d, d->infile, STDIN_FILENO);
		d->outfile = ft_open(d, av[ac - 1], WR_TRUNC);
	}
}
