/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 02:28:34 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:04:56 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_wait(t_data *d, int *wstatus)
{
	if (wait(wstatus) == -1)
		ft_error(d, strerror(errno), NULL);
}

void	ft_waitpid(t_data *d, pid_t pid, int *wstatus, int options)
{
	if (waitpid(pid, wstatus, options) == -1)
		ft_error(d, strerror(errno), NULL);
}
