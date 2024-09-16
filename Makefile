# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytsyrend <ytsyrend@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 11:50:50 by ytsyrend          #+#    #+#              #
#    Updated: 2024/09/16 12:16:34 by ytsyrend         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	dda

# Compiler
C			=	gcc

# Compiler Flags
CFLAGS		=	-Wall -Werror -Wextra -I. -Iinclude
RM 			= 	rm -rf

# Directories
OBJS_DIR 	= 	objs
SRC_DIRS 	= 	srcs
TESTS_DIR	=	tests

# Source files for different tests
DDA 		= 	$(TESTS_DIR)/dda_tester.c
VERT 		= 	$(TESTS_DIR)/horizontal_tester.c
HOR 		= 	$(TESTS_DIR)/vertical_tester.c
COMMON_SRCS =	$(SRC_DIRS)/dda.c $(SRC_DIRS)/helper.c $(SRC_DIRS)/intersections.c $(SRC_DIRS)/zero_infinity.c

# Source and Object Files
DDA_SRCS 	= 	$(COMMON_SRCS) $(DDA)
VERT_SRCS 	= 	$(COMMON_SRCS) $(VERT)
HOR_SRCS 	= 	$(COMMON_SRCS) $(HOR)

DDA_OBJS 	= 	$(DDA_SRCS:%.c=$(OBJS_DIR)/%.o)
VERT_OBJS 	= 	$(VERT_SRCS:%.c=$(OBJS_DIR)/%.o)
HOR_OBJS 	= 	$(HOR_SRCS:%.c=$(OBJS_DIR)/%.o)

# Default rule
all: $(OBJS_DIR) $(NAME)

# Compile and Link the Project for main
$(NAME): $(DDA_OBJS)
	$(C) $(CFLAGS) $^ -o $@
	@echo "$(CYAN)dda: Compilation successful.$(RESET_COLOR)"

# Compile and Link the Project for vertical test
x: $(VERT_OBJS)
	$(C) $(CFLAGS) $^ -o $@
	@echo "$(CYAN)vertical_tester: Compilation successful.$(RESET_COLOR)"

# Compile and Link the Project for horizontal test
y: $(HOR_OBJS)
	$(C) $(CFLAGS) $^ -o $@
	@echo "$(CYAN)horizontal_tester: Compilation successful.$(RESET_COLOR)"

# Compile Source Files into Object Files
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	$(C) $(CFLAGS) -c $< -o $@

# Create the Object File Directory
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)/$(SRC_DIRS)

# Clean Objects and Executable
clean:
	$(RM) $(OBJS_DIR)
	@echo "$(GREEN)Object files and directory cleaned.$(RESET_COLOR)"

fclean: clean
	$(RM) $(NAME) 
	@echo "$(GREEN)Executable removed.$(RESET_COLOR)"

tclean: clean
	$(RM) test
	@echo "$(GREEN)Test executables removed.$(RESET_COLOR)"

# Memory Leak Checking
leaks: re
	@echo "\033[1;33m\nChecking for memory leaks...\033[0m"
	leaks --atExit -- ./$(NAME)

valgrind_leaks: re
	@echo "\033[1;33m\nChecking for memory leaks with valgrind...\033[0m"
	valgrind --leak-check=full ./$(NAME)

# Define symbolic constants for color codes
CYAN		=	\033[1;36m
GREEN		=	\033[1;32m
RESET_COLOR	=	\033[0m

# Phony targets
.PHONY: clean fclean re all leaks valgrind_leaks
