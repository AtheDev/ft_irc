NAME_SERVER = server
NAME_CLIENT = client

SRCS_SERVER = main.cpp server.cpp client.cpp message.cpp
SRCS_CLIENT = client_test.cpp

OBJS_SERVER = $(SRCS_SERVER:.cpp=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.cpp=.o)

CXX = clang++

CXXFLAGS = -Wall -Wextra 

RM = rm -rf

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_SERVER): $(OBJS_SERVER)
				$(CXX) $(CXXFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
				$(CXX) $(CXXFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

$(OBJS_SERVER): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJS_CLIENT): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re