# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kjikuhar <kjikuhar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/30 14:37:47 by kjikuhar          #+#    #+#              #
#    Updated: 2025/07/28 18:39:49 by kjikuhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -----------------------------------------------------------------------------
# > options
# -----------------------------------------------------------------------------
BLACK	:=	\033[30m
RED		:=	\033[31m
GREEN	:=	\033[32m
YELLOW	:=	\033[33m
BLUE	:=	\033[96m
MAGENTA	:=	\033[38;5;206m
CYAN	:=	\033[36m
WHITE	:=	\033[37m
RESET	:=	\033[0m
BOLD	:=	\033[1m
DIM		:=	\033[2m
ITALIC	:=	\033[3m
UNDER	:=	\033[4m
BLINK	:=	\033[5m
REVERSE	:=	\033[7m
HIDDEN	:=	\033[8m
PINK	:=	\033[35m

# -----------------------------------------------------------------------------
# ▸ variables
# -----------------------------------------------------------------------------

NAME 			:=	minitalk
SERVER			:=	server
CLIENT			:=	client

# ─ compile config ────────────────────────────────────────────────────────────

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -Iincludes -Ilibft
T_CFLAGS	:=	-Iincludes -Ilibft

# ─ directory name ────────────────────────────────────────────────────────────

SRCDIR		:=	src
MAND 		:=	mandatory
OBJDIR		:=	obj
LIBFT_DIR	:=	libft
LIBFT_A		:=	$(LIBFT_DIR)/libft.a

# ─ sources & objects ─────────────────────────────────────────────────────────


# server-only sources
SRV_SRCS	:=	src/server.c
SRV_OBJS	:=	$(SRV_SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# client-only sources
CL_SRCS		:=	$(SRCDIR)/client_check_connection.c \
				$(SRCDIR)/client.c
CL_OBJS		:=	$(CL_SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES 	:=	includes/minitalk.h

# -----------------------------------------------------------------------------
# ▸ rules
# -----------------------------------------------------------------------------

all: server client
	@echo "Compiled with $(GREEN)$(BOLD)$(CFLAGS)$(RESET)"
	@echo "$(YELLOW)$(BOLD)========================================="
	@echo "    You can use My $(NAME)!!"
	@echo "=========================================$(RESET)"

server:	$(LIBFT_A) $(SRV_OBJS)
	@$(CC) $(SRV_OBJS) $(LIBFT_A) -o $@ $(CFLAGS)

client:	$(LIBFT_A) $(CL_OBJS)
	@$(CC) $(CL_OBJS) $(LIBFT_A) -o $@ $(CFLAGS)

# compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiled ✅ $(WHITE) $(BOLD) $^ $(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $^

# libft
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

# clean targets
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f client server

re: fclean all

# ノルムチェック
norm:
	@echo "$(CYAN)$(BOLD)========================================="
	@echo "    Checking 42 Norm..."
	@echo "=========================================$(RESET)"
	@norminette $(SRCS_MND) $(INCLUDES)
	@echo "$(GREEN)$(BOLD)Norm check completed!$(RESET)"

# リークチェック
leak: $(NAME)
	@echo "$(MAGENTA)$(BOLD)========================================="
	@echo "    Checking Memory Leaks..."
	@echo "=========================================$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME) test.fdf
	@echo "$(GREEN)$(BOLD)Leak check completed!$(RESET)"

# フルテスト（ノルム + リーク）
test: norm leak
	@echo "$(GREEN)$(BOLD)========================================="
	@echo "    All tests completed!"
	@echo "=========================================$(RESET)"

.PHONY: all clean fclean re norm leak test
