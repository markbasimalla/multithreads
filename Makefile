CC = gcc
CFLAGS = -Iinc
LDFLAGS = -lpthread 

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

EXEC = test
BUILDDIR = build

all: $(BUILDDIR)/$(EXEC)

$(BUILDDIR)/$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: src/%.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BUILDDIR)/$(EXEC)
