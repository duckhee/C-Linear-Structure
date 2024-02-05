CC = gcc

AR = ar

AR_FLAGS = rcus

SRCS =

SRCS += $(C_SOURCES)

# sub folder setting
SUB_DIRS :=

SUB_DIRS += Src

# SUB_DIR addprefix Setting
SUB_DIRS := $(addprefix ./,$(SUB_DIRS))

# Source File add compling
vpath %.c $(SUB_DIRS)


sinclude $(addsuffix /Makefile, $(SUB_DIRS))

BUILD_DIR = buildDir

TARGET = libdataList.a

#DYNAMIC_TARGET = libdataList.so
DYNAMIC_TARGET = libdataList.dylib

C_EXTRA += $(EXTRAINCDIRS)

C_INC = $(patsubst %,-I%, $(C_EXTRA))

COBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

CFLAGS = -fPIC


all: clean createdirs build dynamicLib

createdirs:
	$(shell mkdir ${BUILD_DIR})


build: $(COBJS)
	$(AR) $(AR_FLAGS) $(BUILD_DIR)/$(TARGET) $^

dynamicLib: $(COBJS)
	$(CC) -shared -o $(BUILD_DIR)/$(DYNAMIC_TARGET) $^

$(COBJS): $(BUILD_DIR)/%.o : %.c
	$(CC) $(C_INC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf ${BUILD_DIR}

.SUFFIXES: .c. o
.PHONNY: clean createdirs build dynamicLib