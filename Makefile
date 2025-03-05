# Colors
RESET			= "\033[0m"
BLACK    		= "\033[30m"    # Black
RED      		= "\033[31m"    # Red
GREEN    		= "\033[32m"    # Green
YELLOW   		= "\033[33m"    # Yellow
BLUE     		= "\033[34m"    # Blue
MAGENTA  		= "\033[35m"    # Magenta
CYAN     		= "\033[36m"    # Cyan
WHITE    		= "\033[37m"    # White

# Emojis
SUCCESS		= "✅"
BUILD		= "🔨"
CLEAN		= "🧹"

# Compiler
NAME			= fractol
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -O3 -Ofast -flto -g
OS				= $(shell uname)
MAKE			= make -sC
MKDIR			= mkdir -p
RM				= rm -rf

# Libs
LIBFT_DIR		= Libft
LIBFT			= $(LIBFT_DIR)/libft.a
LINKER  	    = -lft -L $(LIBFT_DIR)

# Includes
INCLUDES_DIR 	= includes
INCLUDES_FLAG 	= -I$(INCLUDES_DIR) \
				  -I$(LIBFT_DIR) \

INCLUDES		= $(INCLUDES_DIR)/fractol.h $(LIBFT_DIR)/libft.h

# Sources
SRCS_DIR		= srcs/
SRC_FILES		= main.c fractal_compute.c fractal_init.c render.c utils.c event_handler.c

SRCS			= $(SRCS_DIR)main.c $(SRCS_DIR)fractal_compute.c $(SRCS_DIR)fractal_init.c $(SRCS_DIR)render.c $(SRCS_DIR)utils.c $(SRCS_DIR)event_handler.c

# Objects
OBJS_DIR		= objs/
OBJ_FILES		= main.o fractal_compute.o fractal_init.o render.o utils.o event_handler.o
OBJS			= $(OBJS_DIR)main.o $(OBJS_DIR)fractal_compute.o $(OBJS_DIR)fractal_init.o $(OBJS_DIR)render.o $(OBJS_DIR)utils.o $(OBJS_DIR)event_handler.o

# Platform-dependent compilation
ifeq ($(OS), Linux)
	MLX_DIR			= mlx_linux
	MLX				= $(MLX_DIR)/libmlx.a
	LINKER			+= -lmlx -lm -lz -lXext -lX11 -L $(MLX_DIR)
	INCLUDES_FLAG	+= -I$(MLX_DIR)
else
	MLX_DIR			= mlx_macos
	MLX				= $(MLX_DIR)/libmlx.a
	LINKER			+= -lmlx -lm -framework OpenGl -framework Appkit -L $(MLX_DIR)
	INCLUDES_FLAG	+= -I$(MLX_DIR)
endif

all : $(LIBFT) $(MLX) $(OBJS_DIR) $(NAME)

$(LIBFT) :
	@echo $(BUILD) $(CYAN) "Making libft..." $(RESET)
	@$(MAKE) $(LIBFT_DIR)
	@echo $(SUCCESS) $(YELLOW) "Made libft!" $(RESET)

$(MLX) :
	@echo $(BUILD) $(CYAN) "Making mlx..." $(RESET)
	@$(MAKE) $(MLX_DIR)
	@echo $(SUCCESS) $(YELLOW) "Made mlx!" $(RESET)

$(OBJS_DIR) :
	@$(MKDIR) $(OBJS_DIR)

$(NAME) : $(OBJS) Makefile
	@echo $(BUILD) $(GREEN) "Compiling $(NAME)..." $(RESET)
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) -o $(NAME)
	@echo $(SUCCESS) $(YELLOW) "Compiling $(NAME) FINISHED" $(RESET)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCLUDES)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAG) -c $< -o $@

clean :
	@$(RM) $(OBJS_DIR)
	@echo $(CLEAN) $(RED) "Cleaned!" $(RESET)

fclean : clean
	@$(RM) $(NAME)
	@$(MAKE) $(MLX_DIR) clean
	@$(MAKE) $(LIBFT_DIR) fclean
	@echo $(CLEAN) $(RED) "Full Cleaned!" $(RESET)

re: fclean all

.PHONY: all clean fclean re
