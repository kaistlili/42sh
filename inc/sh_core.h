/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_core.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 23:39:07 by ktlili            #+#    #+#             */
/*   Updated: 2019/02/18 19:15:36 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_CORE_H
# define SH_CORE_H

# include "libft.h"
# include "generic_typedef.h"
# include "ft_lexer_typedef.h"
# include "ft_lexer.h"
# include "ft_parser_typedef.h"
# include "ft_parser.h"
# include "ft_wordexp.h"
# include "ft_eval.h"
# include "ft_light_parser_typedef.h"
# include "ft_light_parser.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

# define MEMERR 2 
# define SYNERR 3
# define ENVERR 4
# define ACCERR 5

typedef struct 		s_sh_state
{
	int	interactive;
	char **internal;
	char **export_var;
	/* stuff needed by job control will eventually live in this struct 
	 */
}					t_sh_state;

/*
	minishell cmd to remove
*/
typedef	struct			s_command
{
	char				**args;
	char				**process_env;
	struct s_command	*next;
	struct s_command	*previous;
}						t_command;
/*
*/

typedef struct s_cmd_tab t_cmd_tab;

typedef	int				(*t_builtin)(t_cmd_tab*);

/* to delete*/
/**/
extern	t_sh_state		g_sh;

char					**ms_shlvl(char **env);
char*					ms_varchr(char **env, char *toto);
char**					ms_envaddint(char **caca, char *toto, int fifi);
char*					ms_envchrr(char **env, char *var);
t_ast_node				*get_tree(t_ast_node *tree);
int						change_dir(t_cmd_tab *cmd);
int						ft_exit(t_cmd_tab *cmd);
int						ft_env(t_cmd_tab *cmd);
int						ft_unsetenv(t_cmd_tab *cmd);
int						setenv_wrapper(t_cmd_tab *cmd);
int						ft_echo(t_cmd_tab *cmd);
int						ft_set(t_cmd_tab *cmd);
int						ft_unset(t_cmd_tab *cmd);
void					print_env_tab(char **machintruc);
void					print_cmd(t_command command);
void					print_cmd_lst(t_command *command);
int						ft_cmptab(char **machintruc, char *str);
void					free_tab(char **machintruc);
void					free_tab_bytes(char **machintruc);
char					**dup_tab(char **machintruc);
t_command				*new_cmd_node(char **space_split);
void					add_cmdlst(t_command **head, t_command *to_add);
void					free_cmdlst(t_command *command_lst);
void					putstr_stderr(char *str);
int						write_dbuff(t_list *buffer, char c, int *index);
int						putstr_dbuff(t_list *buffer, char *str, int *index);
int						path_access(char *path);
int						ft_ispath(char *str);
char					*handle_pwd_l(void);
void					init_iterator(int *read, int *write);
char					*get_env_value(char *name);
int						set_shell_env(char *name, char *value, int to_export);
int						valid_env_name(char *str);
int						valid_env_char(char c);
char					*tab_get_value(char *name, char **env);
char					*get_value(char *env_var);
int						parser(char *line, t_command **cmd_lst);
int						expand_tokens(char **arg);
char					*expand_dollar(char *line);
void					dispatch_parse_err(int error);
char					*searchbin(char *binname, char *path);
int						bin_perm(char *path);
void					exec_error(int errnum, char *str);
int						dir_access(char *cd_path, char **curpath);
void					cleanpath(char *str);
int						add_slash(char **path);
void					cleandotdot(char *path);
int						valid_env_var(char *str);
int						append_tab(char **new_env, char **to_add, int count);
int						cd_l(char *curpath, char *arg);
int						cd_p(char *curpath, char *arg);
int						cd_dispatch_err(char *arg, char *curpath);
void					update_env_pwd(char *pwd, char *curpath);
int						cd_error(int errnum, char *str);
char					*getoldpwd(void);
char					**ms_csetenv(char **env, char *var);
char					**ms_envdel(char **env, char *var);
char					**ms_envaddstr(char **env, char *var, char *value);

#endif
