SVR_BIN = ChatServer
CLI_BIN = ChatClient
INLCUDE_PATH=-I /usr/include/jsoncpp
INLCUDE_PATH1=-I /usr/include/

all: ChatServer ChatClient
$(SVR_BIN):ChatServer.cpp
	g++ $^ -o $@ -lpthread -std=c++11 -ljsoncpp $(INLCUDE_PATH)
$(CLI_BIN):ChatClient.cpp 
	g++ $^ -o $@ -lpthread -std=c++11 -ljsoncpp $(INLCUDE_PATH) -lncurses

.PHONY:clean
clean:
	rm $(SVR_BIN) $(CLI_BIN)
