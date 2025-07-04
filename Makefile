NAME = jjl
CC = c++

INCLUDES=./includes
ARES_INCLUDES=$(INCLUDES)/ares

CFLAGS = -Wall -Wextra -Werror -I./includes --std=c++17 -I$(ARES_INCLUDES) -g
LDFLAGS = -lzip
 
SRCS_LIST = main \
			init/get_args init/ArgsParser\
			JarJarLibs/JarJarLibs JarJarLibs/ByteCode JarJarLibs/ProcessedMethod \
			GraphViz/GraphViz


SRCS_LIST +=ares/attribute_info\
			ares/class_file\
			ares/class_reader\
			ares/class_writer\
			ares/constant_info\
			ares/method_info\
			ares/field_info\
			ares/utils\
			ares/vm_check

SRC_DIR = ./srcs
SRCS = $(addprefix $(SRC_DIR)/,  $(addsuffix .cpp, $(SRCS_LIST)))

OBJS_DIR = ./objs
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJS_DIR)/%.o)


all: $(NAME)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS)  -c $< -o $@


$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) $(LDFLAGS)


clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re