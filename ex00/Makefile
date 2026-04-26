NAME = btc
SRC = BitcoinExchange.cpp main.cpp
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

re: fclean all
