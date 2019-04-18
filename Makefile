# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/26 17:04:04 by mjose             #+#    #+#              #
#    Updated: 2019/04/16 04:17:58 by bsiche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CLEAR_LINE	= \033[2K
BEGIN_LINE	= \033[A
COL_END		= \033[0m
COL_RED		= \033[1;31m
COL_GREEN	= \033[1;32m
COL_YELLOW	= \033[1;33m
COL_BLUE	= \033[1;34m
COL_VIOLET	= \033[1;35m
COL_CYAN	= \033[1;36m
COL_WHITE	= \033[1;37m

NAME :=	21sh

SRC = main.c \
	  test_option.c \
	  21sh/reddir_tools.c \
	  21sh/tools.c \
	  21sh/errors.c \
	  21sh/ft_parseur.c \
	  21sh/ft_lexeur.c \
	  21sh/ft_modif_list.c \
	  21sh/ft_ast.c \
	  21sh/its_token.c \
	  21sh/its_double_token.c \
	  21sh/execute_ast.c \
	  21sh/execute_pipe.c \
	  21sh/add_path_to_bin.c \
	  21sh/create_tab_to_exec.c \
	  21sh/convert_list.c \
	  21sh/create_fich.c \
	  21sh/hashtables.c \
	  21sh/search_arg.c \
	  21sh/completion.c \
	  21sh/check_quote.c \
	  21sh/out_redir.c \
	  21sh/parse.c \
	  21sh/execute_command.c \
	  21sh/exec_create_fich.c \
	  21sh/set_exec_pipe.c \
	  21sh/execute_pipe_two.c \
	  21sh/its_pipe.c \
	  21sh/ft_quotes.c \
	  21sh/alias_and_env_tools.c \
	  21sh/alias_and_env.c \
	  21sh/unexpected_token.c \
	  21sh/exec_sh.c \
	  21sh/exit_reddir.c \
	  builtins/env/env.c \
	  builtins/export/export.c \
	  builtins/export/export_error.c \
	  builtins/export/export_tools.c \
	  builtins/cd/ft_cd.c \
	  builtins/cd/sanitize_path.c \
	  builtins/cd/cd_path_var.c \
	  builtins/cd/chdir.c \
	  builtins/hash/hash_builtin.c \
	  builtins/hash/hash_args.c \
	  builtins/builtin_tools.c \
	  builtins/bg/bg.c \
	  builtins/fg/fg.c \
	  builtins/setenv/setenv.c \
	  builtins/unsetenv/unsetenv.c \
	  builtins/jobs/jobs_builtin.c \
	  builtins/jobs/jobs_tools.c \
	  builtins/unset/unset.c \
	  builtins/exit/exit.c \
	  builtins/exit/exit_helpers.c \
	  builtins/exit/exit_errors.c \
	  builtins/builtins.c \
	  builtins/set/set.c \
	  builtins/builtin_errors_cont.c \
	  builtins/echo/exec.c \
	  builtins/type/type_main.c \
	  builtins/type/is_cmd.c \
	  builtins/test/test_main.c \
	  builtins/test/test_tab.c \
	  builtins/test/test_two_arg.c \
	  builtins/test/test_three_arg.c \
	  builtins/builtin_errors.c \
	  jobs/signal_handlers.c \
	  jobs/job_utils.c \
	  jobs/job_functions.c \
	  jobs/ft_job_control.c \
	  jobs/job_tools.c \
	  jobs/job_helpers.c \
	  jobs/update_jobs.c \
	  jobs/jobs_output.c \
	  jobs/job_control_errors.c \
	  jobs/jobs_update_command.c \
	  jobs/job_checks.c \
	  gnl/coolprompt.c \
	  gnl/add_to_str.c \
	  gnl/rem_from_str.c \
	  gnl/term_setup.c \
	  gnl/init_term.c \
	  gnl/cursor_pos.c \
	  gnl/cursor_check.c \
	  gnl/cursor_arrows.c \
	  gnl/term_size.c \
	  gnl/lib_utf.c \
	  gnl/print_line.c \
	  gnl/next_word.c \
	  gnl/copy.c \
	  gnl/ctrl.c \
	  gnl/paste.c \
	  gnl/get_key.c \
	  gnl/get_cmd.c \
	  gnl/loop.c \
	  gnl/home_end.c \
	  gnl/basic_mode.c \
	  gnl/is_line_done.c \
	  auto_complete/auto_complete.c \
	  auto_complete/auto_complete_bin.c \
	  auto_complete/auto_complete_check.c \
	  auto_complete/auto_complete_cleanup.c \
	  auto_complete/auto_complete_cursor.c \
	  auto_complete/auto_complete_list.c \
	  auto_complete/auto_complete_page.c \
	  auto_complete/auto_complete_loop.c \
	  auto_complete/auto_complete_move.c \
	  auto_complete/auto_complete_parse.c \
	  auto_complete/auto_complete_padding.c \
	  auto_complete/auto_complete_type.c \
	  auto_complete/print_arg_list.c \
	  auto_complete/send_color.c \
	  auto_complete/var_list.c \
	  auto_complete/assign_word.c \
	  auto_complete/end_autocomplete.c \
	  free_func/free_hist.c \
	  free_func/free_mysh.c \
	  ft_ls/cmdparse.c \
	  ft_ls/cmdparse_misc.c \
	  ft_ls/color.c \
	  ft_ls/free_all.c \
	  ft_ls/print.c \
	  ft_ls/ft_clean.c \
	  ft_ls/ft_clean_bis.c \
	  ft_ls/ft_cleanusr.c \
	  ft_ls/ft_devid.c \
	  ft_ls/ft_ls.c \
	  ft_ls/getstat.c \
	  ft_ls/info_to_str.c \
	  ft_ls/main_ls.c \
	  ft_ls/makelist.c \
	  ft_ls/mode.c \
	  ft_ls/mergesort.c \
	  ft_ls/path.c \
	  ft_ls/recursive.c \
	  ft_ls/sortoption.c \
	  ft_ls/termsize.c \
	  ft_ls/timesort.c \
	  alias/alias_tools.c \
	  alias/alias_bin.c \
	  alias/alias_file.c \
	  alias/alias_struct.c \
	  alias/unalias.c \
	  alias/alias_helpers.c \
	  shell_core/copyenv.c \
	  shell_core/env_to_lst.c \
	  shell_core/init_shell.c \
	  shell_core/get_pwd.c \
	  shell_core/env_list_to_tab.c \
	  history/history_lst.c \
	  history/history_lst_options.c \
	  history/history_loop.c \
	  expansions/expand.c \
	  expansions/expand_tilde.c \
	  expansions/expand_keys.c \
	  expansions/expand_keys_dblpnt.c \
	  expansions/expand_keys_adv.c \
	  expansions/expand_error.c \
	  expansions/autocomplete/auto_com_expan.c \
	  expansions/command/cmd_expan_checker.c \
	  expansions/command/cmd_tools.c \
	  expansions/tools/parm.c \
	  expansions/tools/tools_altern.c \
	  expansions/tools/tools_quote.c \
	  expansions/tools/tools_double_percent.c \
	  expansions/tools/tools_double_hash.c \
	  expansions/tools/values_tools.c \
	  expansions/tools/percent_tools.c \
	  expansions/tools/hash_tools.c \
	  expansions/tools/check_sign_tools.c \
	  expansions/tools/tools_expand.c \
	  expansions/tools/user.c \
	  expansions/tools/home.c \
	  expansions/tools/analyzer.c \
	  expansions/tools/transform.c \
	  expansions/tools/values.c \
	  expansions/tools/scan.c \
	  expansions/tools/scan_tilde.c \
 	  expansions/tools/scarg.c \
	  expansions/command/cmd_helpers.c \
  	  expansions/tools/quote.c \
	  expansions/tools/varname.c \
	  expansions/tools/clean_unquoter.c \
	  temporal_env/temp_env.c \
	  temporal_env/restore_env.c \
	  temporal_env/tmp_env_helpers.c \
	  temporal_env/tmp_env_functions.c \
	  temporal_env/check_tmp_env.c \
	  temporal_env/check_env_i.c \
	  temporal_env/tmp_env_tools.c \
	  temporal_env/tmp_env_utils.c \
	  temporal_env/check_env_i_helpers.c \
	  environment/environ.c \
	  environment/set_environ.c \
	  environment/env_tools.c \

OBJ := $(SRC:.c=.o)

PWD := $(shell pwd)

SRCDIR := srcs
OBJDIR := obj

SRCP :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJP :=		$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
ONLYDIR :=	$(foreach dir, $(OBJP), $(shell dirname $(dir)))

LIB := -L srcs/libft/ -lft

INC := -I includes

FLAG := -Wall -Wextra -Werror

TOTAL_FILES := $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find $(PWD)/obj/ -type f 2> /dev/null | wc -l | sed -e 's/ //g')

all : libft_comp $(NAME)

$(NAME) : $(OBJP)
			@gcc $(FLAG) $(OBJP) -o $(NAME) -ltermcap $(INC) $(LIB)
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Finished compilation. Output file : $(COL_VIOLET)$(PWD)/$(NAME)$(COL_BLUE) ᕦ(ò_óˇ)ᕤ$(COL_END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p $(ONLYDIR)
			@gcc -c $(FLAG) $(INC) $< -o $@
			@echo "$(CLEAR_LINE)$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Compiling file [$(COL_VIOLET)$<$(COL_YELLOW)]. ($(CURRENT_FILES) / $(TOTAL_FILES))$(COL_END)$(BEGIN_LINE)"

libft_comp:
			@make -C srcs/libft

clean :
			@rm -rf $(OBJDIR)
			@make clean -C srcs/libft
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)compiled objects.$(COL_END)"

fclean :	clean
			@rm -rf $(NAME)
			@make fclean -C srcs/libft
			@echo "$(COL_BLUE)[$(NAME)] $(COL_YELLOW)Removed $(COL_VIOLET)$(NAME)$(COL_END)"

re :		fclean all

.PHONY: ft_printf clean fclean all re
