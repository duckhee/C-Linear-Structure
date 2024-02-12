CC = gcc

SRCS = menu.c singleList.c main.c

C_EXTRA = menu.h singleList.h

BUILD_DIR = buildDir

TARGET = ex0503ADTFileIO

COBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

C_INC = $(patsubst %,-I%, $(C_EXTRA))

all: clean createdirs build

createdirs:
	$(shell mkdir ${BUILD_DIR})

build: $(COBJS)
	$(CC) $(C_INC) -o $(BUILD_DIR)/$(TARGET) $^

$(COBJS): $(BUILD_DIR)/%.o : %.c
	$(CC) $(C_INC) -o $@ -c $<

clean:
	rm -rf ${BUILD_DIR}


.SUFFIXES: .c .o
.PHONNY: clean createdirs build