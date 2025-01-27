# project name
TARGET   = memalloc

# compiler and compiler flags
CC       = gcc
CFLAGS   = -std=c89 -Wall -Wextra -Werror -Wpedantic -Iinc -D_GLIBCXX_DEBUG -D_GNU_SOURCE -g
# -fsanitize=address -fsanitize=undefined

# linker and linker flags
LINKER   = gcc
LFLAGS   = -std=c89 -Wall -Wextra -Werror -Wpedantic -Iinc -D_GLIBCXX_DEBUG -D_GNU_SOURCE -g

SRCDIR   = src
INCDIR   = inc
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "*****LINKING COMPLETE*****"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "*****COMPILATION COMPLETE*****"

.PHONY: run
run:
	@./$(BINDIR)/$(TARGET)
	@echo "*****EXECUTION COMPLETE*****"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "*****CLEANUP COMPLETE*****"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "*****EXECTUABLE REMOVED*****"

.PHONY: all
all: $(BINDIR)/$(TARGET)
