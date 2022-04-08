NAME		= aes

INCS		= aes.h \
			  constant.h

SRCS		= main.cpp \
			  aes_algorithm.cpp \
			  str_utils.cpp

OBJS		= $(SRCS:.cpp=.o)

CC			= g++
CFLAGS		= -std=c++17


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)


all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
