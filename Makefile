CC=g++
EXT=cpp

EXEC=TP4

CFLAGS=-std=c++11 -O2
LDFLAGS=

OBJDIR = obj
SRC= $(wildcard *.$(EXT))
HEAD= $(SRC:.$(EXT)=.h)
OBJ= $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))


.PHONY: all clean clean-all depend

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.$(EXT)
	@mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(LDFLAGS) $(CFLAGS)

clean:
	@echo "Suppression des fichiers objet..."
	@rm -rf $(OBJDIR)
	@echo "Suppression de l'exécutable..."
	@rm -f $(EXEC) core$

depend:
	@makedepend $(SRC) -p$(OBJDIR)/
# DO NOT DELETE

obj/circle.o: circle.h shape.h object.h
obj/clearh.o: clearh.h history.h objectmanager.h shape.h object.h selection.h
obj/deleteh.o: deleteh.h history.h objectmanager.h shape.h object.h
obj/deleteh.o: selection.h
obj/history.o: history.h objectmanager.h shape.h object.h selection.h
obj/inserth.o: inserth.h history.h objectmanager.h shape.h object.h
obj/inserth.o: selection.h
obj/line.o: line.h polyline.h shape.h object.h
obj/loadh.o: loadh.h history.h objectmanager.h shape.h object.h selection.h
obj/main.o: circle.h shape.h object.h line.h polyline.h rectangle.h
obj/main.o: selection.h objectmanager.h
obj/moveh.o: moveh.h history.h objectmanager.h shape.h object.h selection.h
obj/object.o: object.h
obj/objectmanager.o: objectmanager.h shape.h object.h selection.h history.h
obj/objectmanager.o: inserth.h deleteh.h clearh.h loadh.h moveh.h circle.h
obj/polyline.o: polyline.h shape.h object.h
obj/rectangle.o: rectangle.h polyline.h shape.h object.h
obj/selection.o: selection.h shape.h object.h
obj/shape.o: shape.h object.h
