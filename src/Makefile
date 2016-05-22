#**********************************************************************
#
#  twm Makefile
#
#**********************************************************************

.SUFFIXES: .y .o

.y.o:
	yacc -d $*.y
	mv y.tab.c $*.c
	mv y.tab.h $*.h
	$(CC) -c $(CFLAGS) $*.c

#
#  If you are running X11R1, then you must use the resource manager
#  library in addition to libX11.a
#
#LIBS= -lX11 -lXrm
LIBS= -lX11

#
# -DNOFOCUS  causes the focus button in the title bar to be compiled out 
#

# Use this definition of CFLAGS for HP machines running HP-UX
#
# CFLAGS= -O +Nd5000 +Ns5000
#
CFLAGS= -O
LDFLAGS=

O_FILES=\
        gram.o\
        lex.o\
        add_window.o\
        gc.o\
        list.o\
        twm.o\
        parse.o\
        menus.o\
        events.o\
        resize.o\
        util.o\
        version.o


all:	twm

twm:	$(O_FILES)
	cc $(LDFLAGS) -o twm $(O_FILES) $(LIBS)

#
#  Dependencies
#
gram.o: \
	twm.h \
	menus.h \
	list.h \
	util.h
lex.o: \
	gram.h
util.o: \
	twm.h \
	util.h \
	gram.h
menus.o: \
	twm.h \
	gc.h \
	menus.h \
	events.h \
	util.h \
	gram.h \
	pull.bm
resize.o: \
	twm.h \
	util.h \
	resize.h \
	add_window.h \
	resize.bm \
	focus.bm
list.o: \
	twm.h \
	gram.h
events.o: \
	twm.h \
	add_window.h \
	menus.h \
	events.h \
	resize.h \
	gram.h \
	twm.bm
parse.o: \
	twm.h \
	menus.h \
	util.h
twm.o: \
	twm.h \
	add_window.h \
	gc.h \
	parse.h \
	version.h \
	menus.h \
	events.h \
	util.h \
	gram.h \
	twm.bm \
	gray.bm
gc.o: \
	twm.h
add_window.o: \
	twm.h \
	add_window.h \
	util.h \
	resize.h \
	gram.h \
	list.h \
	events.h \
	menus.h \
	iconify.bm \
	resize.bm \
	focus.bm \
	hilite.bm
