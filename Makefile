NAME = jjl
CC = c++

INCLUDES=./includes
ARES_INCLUDES=$(INCLUDES)/ares

CFLAGS = -Wall -Wextra -Werror -I./includes -I$(ARES_INCLUDES)

SRCS_LIST = main \
			init/get_args \
			JarFile/JarFile JarFile/unJar \
			utils/signature utils/bitwise utils/utils \
			JarJarLibs/JarJarLibs JarJarLibs/JniOwner

SRCS_LIST+= ares_byte_code/attribute_info \
			ares_byte_code/class_file \
			ares_byte_code/class_reader \
			ares_byte_code/class_writer \
			ares_byte_code/constant_info \
			ares_byte_code/field_info \
			ares_byte_code/method_info \
			ares_byte_code/vm_check

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