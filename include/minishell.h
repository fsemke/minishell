/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsemke <fsemke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/10/27 10:34:13 by fsemke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/ioctl.h>

// echo -n hello < ifile > ofile
# define BUILTIN 4 // echo // == 1
# define EXEC 5 // 
# define FLAG 6 // -n
# define ARG 7 // hello
# define INPUT 8 // <
# define I_FILE 9  // ifile 
# define OUTPUT 10 // >
# define APPEND 11 // >>
# define HEREDOC 12 // <<
# define O_FILE 13 // ofile
# define PIPE 14

/* builtins */
# define PWD 15
# define CD 16
# define ECHO 17
# define EXP 18
# define UNSET 19
# define EXIT 20
# define ENV 21
# define HISTORY 22

# define EXIT_SHELL 42

extern int	g_exit_code;

/* 	token: cat | file | grep | a | ofile
	type: ENUM of tokens*/
typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	struct s_env	*next;
	char			*var;
}	t_env;

typedef struct s_history
{
	struct s_history	*next;
	int					index;
	char				*value;
}	t_history;

typedef struct s_exec
{
	pid_t			pid;
	t_token			*cmd;
	int				builtin;
	char			**options;
	char			*path;
	struct s_exec	*next;
	struct s_data	*data;
	int				heredoc_fdindex;
}	t_exec;

typedef struct s_redir
{
	int	filefd[2];
	int	saved_stdout;
	int	saved_stdin;
	int	flag[2];
}	t_redir;

typedef struct s_data
{
	t_env		*env;
	t_token		*tokens;
	t_exec		*cmd;
	t_token		*search_it;
	t_history	*history;
	char		**envp;
	char		*input;
	int			hist_count;
	int			num_cmds;
	int			cmd_found;
	int			next_is_file;
	t_redir		*redir;
	int			*here_fds;
}	t_data;

/* init */
void		init_shell_env(char **envp, t_data *data);
void		init_exec(t_data *data);
void		ini_data(t_data *data);
t_token		*ini_token(char *tmp, int type);
char		**alloc_options(t_token *head);

/* path */
char		*find_path(t_env *env);
char		*parse_path(t_env *env, char *cmd);
char		*ft_custom_strjoin(char const *s1, char const *s2, char const *s3);

/* parsing */
void		parsing_input(t_data *data);
int			after_processing(t_token *t);

/* parsing_errorcheck */
void		check_redir_char(t_token *token);
int			ft_error(char *s);
void		check_syntax_error(t_token *token);

/* parsing_identify */
char		*rem_all_quotes(char *old);
char		*identify_token(char *str, t_data *data, int *type);

/* parsing_utils */
char		*ft_get_next_word(const char *s);
int			check_quotes(const char *input, int i);
int			return_type_builtin(char *str);

/* heredoc */
void		run_heredoc(t_data *data);

/* piping */
void		ft_pipe(t_exec *cmd, int num_pipes, int *pipefd);

/* exec */
int			ft_exec(t_exec *cmd);

/* processes */
int			single_process(t_exec *cmd);
void		ft_new_process(t_exec *cmd);
void		child_process(t_exec *cmd, int *pipefd, int num_pipes);
void		parent_process(t_exec *head, int *pipefd, int num_pipes);

/* cmd */
int			cmd_link_nodes(t_exec **head, t_data *data);
int			num_args_until_pipe(t_token *head);

/* redirection */
void		ft_redir(t_exec *cmd, int *filefd);

/* signals */
void		handle_signal(int i);

/* utils */
void		remove_node(t_env **head, t_env *remove);
void		add_node(t_env **head, t_env *new);
t_env		*init_node(char *str);
int			linking_nodes(char *str, t_env **head);
void		clear_nodes(t_env **head);

/* utils_2 */
char		**split_var_val(char *str);
int			return_builtin(int type, t_exec *cmd);
char		*str_to_lower(char *str);
int			ft_emptyline(char *input);
int			count_type(t_token *token, int type);

/* builtins */
int			pwd(void);
void		env(t_env *head);
void		echo(t_exec *exec);
void		unset(t_env *ptr, t_exec *exec);

/* builtins2 */
void		cd(t_exec *exec);
int			strenv_cmp(const char *str1, const char *str2);
int			ft_exit(t_exec *exec);

/* builtins_export */
void		export(t_env *ptr, char *input);
void		export_recursive(t_env *ptr, t_token *token);

/* print_export */
void		print_export(t_env *env);

/* ext_env */
char		*ext_env_var(char *arg, t_data *data);

/* history */
void		add_hist_node(t_data *data);
void		print_hist_list(t_history *history);
void		ft_clear_history(t_history *history, t_data *data);

/* cleanup */
void		cleanup_tokens(t_data *data);
void		cleanup_exec(t_data *data);
void		free_double_p(char **local_paths);

/* error */
void		error_path(char *path, t_env *env);
void		fd_pid_error(int fd, pid_t pid);

#endif
