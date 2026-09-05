CC ?= clang
CFLAGS := -Wall -Wextra -Iinclude -MMD -MP
DEBUG ?= 0
OBJDIR := obj
LDFLAGS :=
LDLIBS = -lgit2

ifeq ($(DEBUG), 1)
    SANFLAGS := -fsanitize=address,undefined
    CFLAGS += -O0 $(SANFLAGS) -g
    LDFLAGS += $(SANFLAGS)
else
    CFLAGS += -O2
endif

ifeq ($(shell uname -s), Darwin)
	ARCH := $(shell uname -m)

	ifeq ($(ARCH), arm64)
		CFLAGS += -I/opt/homebrew/include
		LDFLAGS += -L/opt/homebrew/lib
	else ifeq ($(ARCH), x86_64)
		CFLAGS += -I/usr/local/include
		LDFLAGS += -L/usr/local/lib
	endif
endif

EXT:=.cgi
ifeq ($(OS),Windows_NT)
	EXT := .cgi.exe
endif

TARGET := gv$(EXT)

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR) $(TARGET)

-include $(DEPS)

.PHONY: all clean
