#-*-Makefile-*-

CC = cc
CFLAGS =  -g -Wall -Wextra -Werror -I./pars_ch -I./exec_w #-fsanitize=address
READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

SRCM = ./exec_w/bt_env.c ./exec_w/bt_export.c ./exec_w/bt_export2.c ./exec_w/bt_export3.c ./exec_w/bt_echo.c ./exec_w/bt_echo2.c \
		./exec_w/linked_list_mini.c ./exec_w/builtins.c ./exec_w/builtins2.c ./exec_w/cmds_exec_utils4.c \
		./exec_w/helper_funcs.c ./exec_w/helper_funcs2.c ./exec_w/cmds_exec.c ./exec_w/bt_pwd.c ./exec_w/bt_cd.c ./exec_w/bt_unset.c\
		./exec_w/bt_cd2.c ./exec_w/cmds_exec_utils.c ./exec_w/split_mini.c ./exec_w/cmds_exec2.c ./exec_w/cmds_exec3.c \
		./exec_w/cmds_exec_utils2.c ./exec_w/cmds_exec_utils3.c ./exec_w/bt_exit.c ./exec_w/bt_exit2.c \
		./pars_ch/split_double_char.c\
		./pars_ch/main.c ./pars_ch/syntax_error.c ./pars_ch/parssing1.c ./pars_ch/parssing2.c\
		./pars_ch/parssing3.c ./pars_ch/parssing5.c ./pars_ch/herdoc.c ./pars_ch/herdoc1.c ./pars_ch/herdoc2.c \
		./pars_ch/helper_fun.c ./pars_ch/helper_fun1.c ./pars_ch/main1.c ./pars_ch/main2.c\
		./pars_ch/expand.c ./pars_ch/expand1.c ./pars_ch/expand2.c ./pars_ch/quotes.c\
		./pars_ch/parssing.c ./pars_ch/parssing_helper1.c ./pars_ch/parssing_helper2.c ./pars_ch/mem_manager.c\
		./pars_ch/ft_itoa.c ./pars_ch/parssing_helper3.c ./pars_ch/expand3.c ./pars_ch/expand4.c ./pars_ch/expand5.c\

OBJM = $(SRCM:%.c=%.o)

SRCB = 

OBJB = $(SRCB:%.c=%.o)
#binaries :
NAME = minishell
BONUS = 
HEADER_MAN = ./pars_ch/minishell.h ./exec_w/execution.h 
HEADER_BON = 

all: $(NAME)



man: $(NAME)
bonus: $(BONUS)

#Build mandatory part :
$(NAME): $(OBJM)
	cc $(CFLAGS) $^ -o $@ -L $(READLINE_L) -lreadline 

# Compile object files for mandatory part :
$(OBJM):%.o:%.c $(HEADER_MAN)
	$(CC) $(CFLAGS) -I $(READLINE_I)  -c $< -o $@

#Build bonus part :
$(BONUS): $(OBJB)
	cc $(CFLAGS) $^ -o $@
# Compile object files for bonus part :
$(OBJB):%.o:%.c $(HEADER_BON)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJM) $(OBJB)
fclean: clean
	rm -f $(NAME) $(BONUS)
re: fclean all 
