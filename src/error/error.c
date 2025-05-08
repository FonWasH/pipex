/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:52:58 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:07:14 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_putstrlower(char *str, int fd)
{
	char	c;

	while (*str)
	{
		c = ft_tolower(*str);
		if (write(fd, &c, 1) == -1)
			break ;
		str++;
	}
}

void	ft_puterror(char *error, char *extra)
{
	ft_putstr(NAME, 2);
	ft_putstrlower(error, 2);
	if (extra)
	{
		ft_putstr(": ", 2);
		ft_putstr(extra, 2);
	}
	ft_putstr("\n", 2);
	if (!ft_strncmp(error, ERROR_ARG, ft_strlen(ERROR_ARG)))
		ft_printf("%s%s\n", USAGE1, USAGE2);
}

void	ft_error(t_data *d, char *error, char *extra)
{
	if (error)
		ft_puterror(error, extra);
	if (d && d->infile != -1)
		ft_close(d, d->infile);
	if (d && d->outfile != 1)
		ft_close(d, d->outfile);
	exit(errno);
}
