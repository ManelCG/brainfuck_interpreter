BDIR = build
SDIR = src

IDIR = include
CC = gcc
CFLAGS = -I$(IDIR)

ODIR=obj
LDIR=lib

LIBS = -lm

_DEPS = bf.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o bf.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

.PHONY: all
all: main clean
