CC := clang
CFLAGS := -Wall -Wextra -Iinclude -MMD -MP
DEBUG ?= 0
OBJDIR := obj

ifeq ($(DEBUG), 1)
    CFLAGS += -O0 -fsanitize=address,undefined -g
else
    CFLAGS += -O2
endif

TARGET := main.out

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
