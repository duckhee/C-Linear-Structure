CC = gcc

SRCS = dataStructure.c

BUILD_DIR = buildDir

TARGET = ex01ArrayBaseLinearStructure

COBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

all: clean createdirs build

createdirs:
	$(shell mkdir ${BUILD_DIR})

build: $(COBJS)
	$(CC) -o $(BUILD_DIR)/$(TARGET) $^

$(COBJS): $(BUILD_DIR)/%.o : %.c
	$(CC) -o $@ -c $<

clean:
	rm -rf ${BUILD_DIR}

.SUFFIXES: .c .o
.PHONNY: clean createdirs build