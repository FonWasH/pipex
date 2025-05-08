/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperez <juperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:46:13 by juperez           #+#    #+#             */
/*   Updated: 2024/07/11 10:22:00 by juperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

/* LIBFT */
# include "../lib/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

/* ERROR */
# define NAME "pipex: "
# define ERROR_ARG "bad arguments"
# define ERROR_ENV "environment variable not found"
# define ERROR_CMD "command not found"

/* USAGE */
# define USAGE1 "Usage:\t./pipex [FILE] [COMMAND]... [FILE]\n"
# define USAGE2 "\t./pipex here_doc [LIMITER] [COMMAND]... [FILE]"

/* STRING */
# define HERE_DOC "here_doc"
# define PATH "PATH"
# define PATH_LEN 4

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

/*ENUM OPEN MODE */
typedef enum e_openf
{
	WR_APPEND,
	WR_TRUNC,
	RD
}	t_openf;

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

typedef struct s_exe
{
	char	**cmd;
	char	*path;
	int		ret;
}			t_exe;

typedef struct s_data
{
	int		i;
	int		ac;
	char	**av;
	char	**env;
	char	*env_path;
	char	*limiter;
	int		infile;
	int		outfile;
	int		status;
}			t_data;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

/* ERRORS */
void	ft_error(t_data *d, char *error, char *extra);
void	ft_puterror(char *error, char *extra);

/* INIT */
void	ft_init_data(t_data *d, int ac, char *av[], char *env[]);

/* SYSTEM */
void	ft_wait(t_data *d, int *wstatus);
void	ft_waitpid(t_data *d, pid_t pid, int *wstatus, int options);

/* UNISTD */
int		ft_open(t_data *d, char *path, t_openf flag);
void	ft_close(t_data *d, int fd);
void	ft_write(t_data *d, int fd, char *str);
void	ft_dup2(t_data *d, int oldfd, int newfd);
pid_t	ft_pipe_fork(t_data *d, int fd[2]);

/* UTILS */
t_exe	ft_get_cmd(t_data *d, char *av);

/* PIPEX */
void	ft_pipex(t_data *d);
void	ft_here_doc(t_data *d);

#endif
