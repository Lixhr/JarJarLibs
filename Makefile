NAME = jjl
CC = c++

INCLUDES=./includes
ARES_INCLUDES=$(INCLUDES)/ares

CFLAGS = -Wall -Wextra -Werror -I./includes -I$(ARES_INCLUDES)

SRCS_LIST = main \
			init/get_args \
			JarJarLibs/JarJarLibs \
			JavaClass/JavaClass \
			utils/utils utils/GNL/GNL utils/GNL/get_next_line utils/GNL/get_next_line_utils

SRC_DIR = ./srcs
SRCS = $(addprefix $(SRC_DIR)/,  $(addsuffix .cpp, $(SRCS_LIST)))

OBJS_DIR = ./objs
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJS_DIR)/%.o)


all: $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)


clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re