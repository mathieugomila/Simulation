CFLAGS = -W -Wall -pedantic

INCLUDE_DIR = source/header
SOURCE_DIR = source
OBJ_DIR = object

SRC= $(wildcard $(SOURCE_DIR)/*.c) 

OBJ_tempo= $(notdir $(SRC:%.c=%.o))
OBJ = $(OBJ_tempo:%.o=$(OBJ_DIR)/%.o)

DEP = -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -lm -I/usr/local/include -L/usr/local/lib  

EXEC = debug

all: clean init $(EXEC)

init:
	@mkdir -p $(OBJ_DIR)

debug: $(OBJ)			
	@gcc -o $@ $^ $(DEP)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c $(INCLUDE_DIR)/Game.h
	@gcc -o $@ -c $< $(CFLAGS) $(DEP)


clean:
	@rm -rf $(OBJ_DIR)/*.o

total_clean: clean
	@rm -rf $(EXEC)
