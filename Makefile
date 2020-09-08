NAME=gameoflife
SRCS=main.cpp\
	 grid.cpp
SRC=$(addprefix src/,$(SRCS))
INCLUDE=include

all:$(NAME)

$(NAME):
	g++ $(SRC) -lSDL2 -I $(INCLUDE) -o $(NAME)

clean:
	rm -f $(SRCS:.cpp=.o)
fclean:clean
	rm -f $(NAME)
re: fclean all
