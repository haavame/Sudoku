
IDIR = ../include
ODIR = build

.DEFAULT_GOAL := ../sudoku

CC=g++
CFLAGS=-I$(IDIR)

_DEPS = board.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o board.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS) | $(ODIR)
	$(CC) -c $< -o $@ $(CFLAGS)


../sudoku: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR):
	mkdir $(ODIR)


.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
