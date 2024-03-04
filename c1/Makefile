CCFLAGS :=-std=c++2b -Wall -Wpedantic -Wextra -Wconversion
CC      :=clang++
OBJ     :=obj/main.o obj/aicomponent.o obj/rendercomponent.o obj/physicscomponent.o obj/inputcomponent.o obj/entitymanager.o obj/gamemanager.o obj/entity.o
INCLUDE :=-Isrc/
DEBUGFLAGS:=-g -fsanitize=address
LDFLAGS :=-lraylib

game: $(OBJ)
	$(CC) -o $@ $(DEBUGFLAGS) $(LDFLAGS) $^

obj/%.o: src/%.cpp | obj
	$(CC) $(DEBUGFLAGS) $(CCFLAGS) $(INCLUDE) -g -c -o $@ $^

obj:
	mkdir obj

.PHONY: clean
clean:
	rm -rf ./obj/