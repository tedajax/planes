TARGET		= planes
CC			= clang
CFLAGS		= -std=c99 -Wall -I. `pkg-config --cflags luajit` -g

LINKER		= clang -o
LFLAGS		= -Wall -I. -lm -lSDL2 -lSDL2_image `pkg-config --libs luajit` -rdynamic -pagezero_size 10000 -image_base 10000000

SRCDIR		= src
OBJDIR		= obj
BINDIR		= .

SOURCES		:= $(wildcard $(SRCDIR)/*.c)
INCLUDES	:= $(wildcard $(SRCDIR)/*.h)
OBJECTS		:= $(SOURCES:$(SRCDIR)%.c=$(OBJDIR)/%.o)
rm			= rm -f

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
