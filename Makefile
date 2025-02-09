CC = gcc
CFLAGS = -Iinclude
LFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lm -lpthread

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
OUT = $(BUILD_DIR)/main

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	del build /F /Q

run: $(OUT)
	$(OUT)