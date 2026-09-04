CC := clang
CFLAGS := -Wall -Wextra -Iinclude -MMD -MP
DEBUG ?= 0
OBJDIR := obj
UNAME := $(shell uname -s)
LDFLAGS :=
LDLIBS = -lgit2

ifeq ($(DEBUG), 1)
    SANFLAGS := -fsanitize=address,undefined
    CFLAGS += -O0 $(SANFLAGS) -g
    LDFLAGS += $(SANFLAGS)
else
    CFLAGS += -O2
endif

ifeq ($(UNAME), Darwin)
	CFLAGS += -I/opt/homebrew/include
	LDFLAGS += -L/opt/homebrew/lib
endif

TARGET := main.out

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
