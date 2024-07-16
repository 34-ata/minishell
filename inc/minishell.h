/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:52 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/15 12:25:23 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../lib/libft/libft.h"

# define ERR_NOT_FOUND 127
# define ERR_PERMISSION 1271
# define ERR_SYNTAX 258
# define ERR_NOT_VALID 1
# define PROMT "/User "
# define BUILTIN 9
# define BUILTIN2 10
# define NONE 0
# define PIPE 1
# define HEREDOC 2
# define APPEND 3
# define HEREDOCAPPEND 4
# define PIPEHEREDOC 5
# define PIPEAPPEND 6
# define PIPEHEREDOCAPPEND 7

# define CHILD_P 1
# define MAIN_P 2
# define HEREDOC_P 3

typedef struct s_utils
{
	int	single_quote;
	int	dble_quote;
	int	i;
	int	j;
	int	k;
	int	c;
}	t_utils;

typedef struct s_main_env
{
	char	**envr;
	char	*minipwd;
}	t_main_env;

typedef struct s_cmds
{
	char				*cmd;
	char				**flags;
	char				**input;
	char				**heredoc;
	char				**output;
	char				**append;
	char				**args;
	int					status;
	pid_t				pid;
	char				**envr;
	int					execr;
	struct s_main_env	*env;
	struct s_cmds		*next;
	struct s_utils		utils;
}	t_cmds;

extern int	g_globals_exit;

void		envcpy(char **new_envr, char **s, t_cmds *cmds, int size);
void		start_parsing(char	**envp, char *temp, char *temp_args, char **av);
void		errorm(char *str);
void		exit_error_2(t_cmds *cmd);
int			status_control(int old, int n);
int			status_control(int old, int n);
int			check_cmmn(char *input, char *lll);
void		take_env(t_cmds *cmds, t_main_env *env, int status, char **environ);
int			take_env_size(char **env);
void		check_built(t_cmds *cmds);
void		ft_msg(char *str, int type);
void		del_ind(char **s);
void		del_ind_adv(char **s, int *rm1, int *rm2, int *i);
void		del_ind_int(int *rm1, int *rm2, int *i, int *quote);
void		ft_remove_char_by_index(char **str, int index);
int			is_valid(char *arg, int control);
int			search_eq(char *str);
void		check_dollar(t_cmds *cmds, char **str,
				int single_quote, int dble_quote);
void		check_built_f(t_cmds *cmds);
int			count_valid_pipe(char *str, int single_quote,
				int dble_quote, int count);
char		**quot_split(char *str, int single_quote,
				int dble_quote, int start);
void		parse_args(char **args, t_cmds *cmds, t_main_env *env);
void		take_input_first(char *str, t_cmds *cmds);
int			skip_input_output(char *str, int single_quote,
				int dble_quote, int i);
void		take_cmd(char *str, t_cmds *cmds, int single_quote, int dble_quote);
int			take_flags(char *str, t_cmds *cmds,
				int single_quote, int dble_quote);
int			skip_cmd(char *str, int i, int single_quote, int dble_quote);
void		quote_check(char c, int *single_quote, int *dble_quote);
void		take_args_and_flags(t_cmds *cmds, char *str,
				int single_quote, int dble_quote);
void		init_env(t_main_env *env, t_cmds *cmds);
void		handler_sigint(int sig);
void		handler(int sig);
int			ft_strncmp2(char *dest, char *src);
int			arg_control(char *str);
int			take_input2(char *str, int i);
void		freecpointer(char **s);
void		set_signal(int c);
void		cleanlist(t_cmds	*cmd);
int			output_count(char *str, int single_quote, int dble_quote, int type);
int			input_count(char *str, int single_quote, int dble_quote, int type);
int			flags_count(char *str, int i, int single_quote, int dble_quote);
int			args_count(char *str, int single_quote, int dble_quote, int i);
int			find_valid_space(char *str, int i,
				int single_quote, int dble_quote);
int			skip_arg(char *str, int *single_quote, int *dble_quote, int i);
void		take_all(char *str, t_cmds *cmds);
void		take_output_first(char *str, t_cmds *cmds);
void		init_take_output(t_cmds	*cmds, char *str);
void		assign_var(t_cmds *cmds, char *temp, int j, int type);
int			check_input(t_cmds	*cmds, char *str);
int			go_take_output(t_cmds *cmds, char *str);
int			take_append(t_cmds *cmds, char *str);
int			take_output(char *str, t_cmds *cmds, int j, int type);
int			take_output2(int i, int fd, t_cmds *cmds);
int			take_output3(int i, int fd, t_cmds *cmds);
t_main_env	*set_env_main(char **av);
int			empty_input_output(char *str, int single_quote, int dble_quote);

void		pwd(t_cmds *cmd);
void		exitmini(t_cmds *cmd);
void		unset_env(t_cmds *cmds);
void		cd(t_cmds *cmd, char *newdirect);
void		ft_echo(t_cmds *cmds);
void		print_env(t_cmds *cmds, int status);
void		new_envr(t_cmds *cmds, int i, int j, int size);
void		nocmd_heredoc(t_cmds *temp, int i, int c, char *lll);

char		*get_clear_cwd(char *cwd, int c);
char		*get_clear_pwd(char *cwd, int c);
char		*edit_pwd(char *av);
char		*set_dollar_zero(char **av, int a);
int			check_behind(char *av);
int			check_flags_2(int i, t_cmds *cmds);
char		*replace_check_dol(char *val);
char		*replace_check_dol_adv(t_utils t, char **temp, char *val);
int			temp_char_size(char **temp);
void		set_int(t_utils *t);
int			temp_size(char **temp);
int			check_value(char *val);
int			chdir_func(char *newpwd, char *newdirect, char *oldpwd);
void		set_newdirect(char *oldpwd, char **tmppwd, char **newpwd, char *nd);
int			cd_if(char **newpwd, t_cmds *cmd, char **newdirect, char *oldpwd);
int			cd_if2(char **newpwd, t_cmds *cmd, char **newdirect, char *oldpwd);
char		*getoldpwd(t_cmds *cmd);
int			exit_ut(int i, int n, t_cmds *cmd);
char		*gethome(t_cmds *cmd);
void		exit_error(t_cmds *cmd);
int			exitflag(t_cmds *cmd);
int			exitarg(t_cmds *cmd);
int			ft_isnumeric(char*str);
void		setoldpwd2(char *newpwd, char **newpwd2);
void		set_oldpwd(char *oldpwd, t_cmds *cmd, int i);
void		set_newpwd(char *newpwd, char *newpwd2, t_cmds *cmd, int i);
void		pipe_heredoc(t_cmds *temp, char **run, int fd[2]);
void		cmd_start(t_cmds *cmds);
void		read_and_exec(t_cmds *cmds, int i);
void		childproces(char **run, t_cmds *temp, int i);
void		builtornot(t_cmds *temp, char **run);

void		backup_default_fd(int fd[2]);
void		get_exit_status(t_cmds *cmds, int i);
int			is_file(const char *path);
void		patherror1(char *command);
int			is_directory(const char *path);
void		closedup(int fd[2]);
int			runcommand(char **command, t_cmds *cmd);
int			set_fork_and_output(t_cmds *temp, int i);
int			set_input(t_cmds *temp, int c);
int			set_output(t_cmds *temp, int p[2], int i);
void		fderror(char *output);
void		fderror2(char *output);
void		pipecheck(int fd[2]);
char		*findpath(char **command, char **env);
int			open_output_append(t_cmds *temp, int c);
int			open_output(t_cmds *temp, int c);
int			set_fork_and_output_2(t_cmds *temp, int i);
int			commandcounter(t_cmds *temp);
int			commanlistcount(t_cmds *cmd);
int			status_check(t_cmds *temp);
char		*ft_substr_trim(char *str, int start, int end, char *spt);
char		*find_path_while(char **path, char *command);
void		error_write(char *command);
void		unset_error(t_cmds	*cmds);
void		token_error(char	*str);
void		for_zero(int *i, int *single_quote, int *dble_quote);
int			else_control(char	**str, int i, int single_quote);
void		ft_ctrl_d(void);

#endif