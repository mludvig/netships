#
# standard Makefile
#

TOPDIR  = ../

include $(TOPDIR)/Makefile.common

LIBOPT  = -L$(TOPDIR)/util -L$(TOPDIR)/comm -lmic -lncurses -lcomm
CFLAGS  = -I$(TOPDIR)/util -I$(TOPDIR)/comm -Wall -ggdb
ARCHDIR = $(TOPDIR)/arch

EXEC	= netships
OBJS	= sea.o main.o pool.o comm.o sea2.o poolk.o poolu.o info.o poolk-fill.o

ARCHDATE= $(TOPDIR)/b$(TOPDIR)/archdate

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LIBOPT)

# Some service targets:
clean: 
	rm -f *.o *~ core $(EXEC)

arch: 
	tar cvfz netship.`$(ARCHDATE)`.tgz *.cc *.h Makefile $(EXEC)
	mv netship.*.tgz $(ARCHDIR)

