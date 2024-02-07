CC = gcc

SRCS = main.c

TARGET = ex0401NodeSort

BUILD_DIR = buildDir

COBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

C_EXTRA :=
C_EXTRA += ./lib/Data_Lib/inc
C_EXTRA += ./lib/UI_Lib/inc

C_MODULE :=


LIBS :=
# 라이브러리 파일의 시작은 lib으로 시작해야한다.
LIBS += -ldataList -L ./lib/Data_Lib/buildDir
LIBS += -luiLib -L ./lib/UI_Lib/buildDir


C_INC = $(patsubst %,-I%, $(C_EXTRA)) $(C_MODULE) $(LIBS)

C_FLAGS :=

all: clean createdirs build

createdirs:
	$(shell mkdir ${BUILD_DIR})

build: $(COBJS)
	$(CC) $(C_INC) $(C_FLAGS) -o $(BUILD_DIR)/$(TARGET) $^

$(COBJS): $(BUILD_DIR)/%.o : %.c
	$(CC) $(C_INC) $(C_FLAGS) -o $@ -c $<

clean:
	rm -rf ${BUILD_DIR}

.SUFFIXES: .c .o
.PHONNY: clean createdirs build