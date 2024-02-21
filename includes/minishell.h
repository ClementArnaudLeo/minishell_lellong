/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carnaud <carnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:12:51 by carnaud           #+#    #+#             */
/*   Updated: 2023/09/17 11:39:04 by carnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdbool.h>
#include "../libft/libft.h"
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

// STRUCTURES + (definition var globale t_minishell)
typedef struct s_sous_dico
{
	char *key;
	char *value;
	struct s_sous_dico *next;
} t_sous_dico;

typedef struct s_dico
{
	t_sous_dico **sous_dico;
	unsigned int count;
	unsigned int size;

} t_dico;

typedef struct s_minishell
{
	t_dico *env;
	t_dico *local_vars;
	int error_status;
} t_minishell;

extern t_minishell g_minishell;

typedef struct s_token
{
	int type;
	char *value;
	struct s_token *next;
	struct s_token *previous;
} t_token;

typedef struct s_var
{
	char *before;
	char *after;
	char *value;
	char *pointer;
} t_var;

void err_msg(char *input, char *err_msg, int status);
t_sous_dico *dico_create_pair(char *key, char *value);
t_dico *dico_create_table(unsigned int size);
void dico_free_pair(t_sous_dico *pair);
void dico_free_table(t_dico *table);
void dico_insert(char *key, char *value, t_dico *table);
char *dico_search(t_dico *table, char *key);
void dico_delete(t_dico *table, char *key);
char **dico_to_env(t_dico *table);
char **dico_to_env_with_quotes(t_dico *table);
t_dico *env_to_dico(char **env);

// SIGNATURES FONCTIONS
void print_environment(t_dico *env, int fd);
int export_(char **cmd);
void unset(char **cmd);
void pwd(void);
void cd(char *path);
void echo(char **cmd);
void exit_builtin(char **cmd);
void exit_minishell(void);
int set_local_var(char **cmd, int *i);

void tri_array(char **array, int left, int right);
int get_array_length(char **array);

unsigned long int hash(char *key, unsigned int size);
char *create_prompt(bool *booleen);
void define_signals(void);
void define_signals2(void);
void print_2d_array_fd(char **array, int fd);
void free_2d_array(char **ptr);
char *get_absolute_path(char *cmd, char *path_variable);
void execute(char **cmd);
void join_array(char *string_to_join, char **array);

void tokenizer(char **line, t_token **token_lst);
void add_token(char *line, int start, int end, t_token **token_lst);
int split_token(char *line, int *i, int *tkn_end, t_token **token_lst);

void cas_speciaux(char **value);
bool is_quote(char c);
bool is_between_quotes(char *line, int i, int *match_index, char c);
void remove_quotes(char **value, char quote);

bool is_builtin(char *value);
void expand_variables(char **value);
void free_var_struct(t_var *var);
void expand(char **variable);
void handle_var_squote(t_var *var, char **value, int i);
void check_and_insert_spaces(char **line);
char *insert_spaces(char **line, char *operator_pointer, char *line_init);
bool no_blanks_around_operator(char *line, char *line_init);
void handle_quotes(char **token_ptr, int i, int *end_quote);

void define_end_quote(char *token, bool has_variable,
					  char first_quote, int *end_quote);

bool if_is_special_case(char *value);

char *search_var(char *value, int *i);
int get_var_size(char *var, int *index);
void define_type(t_token *previous, char *value, int *type);
bool is_redirect(char *value);

void token_list_clear(t_token **lst);
t_token *token_new(char *value, int type);
void token_add_back(t_token **lst, t_token *new_token);
t_token *token_last(t_token *lst);
void parse_then_execute(t_token *token_lst);
void command_parser(t_token *token_lst, t_token *pipe, int *old_pipe_in);
void check_redirects(t_token *token_lst, t_token *pipe, int *save_fd);
void here_doc_input(char *eof, int *save_fd);
char **create_command_array(t_token *head, t_token *pipe);
void stop_here_doc(int signal);
void free_var_struct(t_var *var);
char **split_by_two(const char *string, char c);
char **split_by_two_ptr(const char *string, char *c_ptr);

// DEFINITIONS
#define KEY 0
#define VALUE 1
#define IN 0
#define OUT 1
#define NOT_FOUND "command not found."
#define TOO_MANY_ARGS "too many arguments."
#define NO_OLDPWD "OLDPWD environment variable has not been set."
#define NO_HOME "HOME environment variable has not been set."
#define NO_FILE "no such file or directory."
#define SYNTAX_ERROR "syntax error."
#define NEED_NUM_ARG "numeric argument required."
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BOLD_YELLOW "\033[1;33m"
#define CYAN "\033[0;36m"
#define RESET_COLOR "\033[0m"
#define BOLD_RED "\001\033[1;31m\002"
#define RESET_BOLD_RED "\001\033[0m\002"
#define T_BUILTIN 42
#define T_LITERAL 43
#define T_PIPE 44
#define T_REDIRECT 45
#define T_HERE_DOC 46
#define T_FILE 47

#endif
