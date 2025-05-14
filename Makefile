# ----------------------------------------Name
NAME = libgl-utils.a

# ----------------------------------------Files
FILES_SRCS =	glad.cpp \
				Window.cpp \
				Key.cpp \
				Shader.cpp \
				ComputeShader.cpp \
				VAO.cpp \
				VBO.cpp \
				EBO.cpp \
				SSBO.cpp \
				bmp.cpp \
				textures.cpp \
				FrameBuffer.cpp \
				RenderBuffer.cpp \
				read_file.cpp \

FILES_OBJS = $(FILES_SRCS:.cpp=.o)

# ----------------------------------------Directories
DIR_SRCS = ./src/
DIR_OBJS = ./obj/
DIR_LIB = ./lib/
DIR_EMLM = $(DIR_LIB)emlm/
DIR_EMLM_OBJS = ./obj_emlm/

vpath %.cpp \
	$(DIR_SRCS) \
	$(DIR_LIB) \
	$(DIR_LIB)bmp \

# ----------------------------------------Sources
SRCS = $(FILES_SRCS:%=$(DIR_SRCS)%)

# ----------------------------------------Objects
OBJS = $(FILES_OBJS:%=$(DIR_OBJS)%)
EMLM_OBJS = $(DIR_EMLM_OBJS)*.o

# ----------------------------------------Libs
EMLM = $(DIR_EMLM)libmlm.a
EMLM_SM = $(DIR_EMLM).git

# ----------------------------------------Flags
CC = c++
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -O3
# CFLAGS += -fsanitize=address -g

INC = \
	-Iinc \
	-Iinc/utils \
	-I$(DIR_LIB) \
	-I$(DIR_EMLM) \

all:
	@$(MAKE) $(NAME) -j4
.PHONY: all

$(NAME): $(DIR_OBJS) $(OBJS) $(EMLM_OBJS)
	ar -crs $(NAME) $(OBJS) $(EMLM_OBJS)

$(DIR_OBJS)%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(DIR_OBJS):
	mkdir -p $@

$(EMLM_OBJS): $(EMLM) $(DIR_EMLM_OBJS)
	ar x --output $(DIR_EMLM_OBJS) $(EMLM)

$(DIR_EMLM_OBJS):
	mkdir -p $@

$(EMLM): $(EMLM_SM)
	$(MAKE) -C $(DIR_EMLM)

$(EMLM_SM):
	@$(MAKE) submodule

submodule:
	@echo "fetching submodules..."
	git submodule init
	git submodule update

# ----------------------------------------Cleaning
clean:
	rm -f $(OBJS)
	rm -f $(EMLM_OBJS)
	$(MAKE) clean -C $(DIR_EMLM)
.PHONY: clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(DIR_EMLM)
.PHONY: fclean

re: fclean all
.PHONY: re
