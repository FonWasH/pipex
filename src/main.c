/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:48:28 by juperez           #+#    #+#             */
/*   Updated: 2025/05/07 04:05:20 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *env[])
{
	t_data	d;

	if (ac < 5 || (ac < 6 && !ft_strncmp(av[1], HERE_DOC, ft_strlen(av[1]))))
		ft_error(NULL, ERROR_ARG, NULL);
	ft_init_data(&d, ac, av, env);
	ft_pipex(&d);
	exit(d.status);
}
