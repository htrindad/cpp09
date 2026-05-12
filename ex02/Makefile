NAME = PmergeMe
SRC = PmergeMe.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
CPPFLAGS = -Wall -Werror -Wextra -O3 -std=c++98

%.o: %.cpp
	c++ $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	c++ $(CPPFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

test:
	valgrind ./PmergeMe 4 2 3 2 45 32
	@sleep 2
	valgrind ./PmergeMe $$(shuf -i 1-500 -n 200 | tr '\n' ' ')
	@sleep 2
	valgrind ./PmergeMe $$(shuf -i 1-10000 -n 3000 | tr '\n' ' ')
	@sleep 2
	valgrind ./PmergeMe $$(seq 1 500 | tr '\n' ' ')
	@sleep 2
	valgrind ./PmergeMe $$(seq 500 -1 1 | tr '\n' ' ')
	@sleep 2
	valgrind ./PmergeMe $$(seq 500 -250 250 | tr '\n' ' ')

re: fclean all
