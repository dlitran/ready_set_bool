NAME := readySetBool
SRC_DIR := src
SRC_NAME := main.cpp readySetBool.cpp tester.cpp\
			bitwiseArithmetic.cpp propositionalLogic.cpp\
			setAlgebra.cpp spaceFillingCurve.cpp\
			truthTable.cpp\
			

SRC := $(addprefix $(SRC_DIR)/,$(SRC_NAME))

OBJ_DIR := obj
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

CC := g++
CFLAGS := -Wall -Wextra -Werror

INCLUDE_DIR := inc
INC_NAME := main.hpp
INCLUDE := $(addprefix $(INCLUDE_DIR)/,$(INC_NAME))

RM := rm -f

DEPFLAGS := -MMD -MP
DEPS = $(OBJS:.o=.d)

all: $(NAME)
	@echo compiling $(SRC)

-include $(DEPS)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cpp Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS)
	@rmdir $(OBJ_DIR)


fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
