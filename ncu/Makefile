#
# standard Makefile
#

TOPDIR  = ../

include $(TOPDIR)/Makefile.common

LIBOPT  += -L$(TOPDIR)/util -L$(TOPDIR)/comm -lncurses -lutil -lcomm
CFLAGS  += -I$(TOPDIR)/util -I$(TOPDIR)/comm
ARCHDIR = $(TOPDIR)/arch

EXEC	= netships
OBJS	= sea.o main.o pool.o comm.o sea2.o poolk.o poolu.o info.o poolk-fill.o

ARCHDATE= $(TOPDIR)/b$(TOPDIR)/archdate

all: depend $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LIBOPT)

# Some service targets:
clean: 
	rm -f *.o *~ core $(EXEC) depend

arch: 
	tar cvfz netship.`$(ARCHDATE)`.tgz *.cc *.h Makefile $(EXEC)
	mv netship.*.tgz $(ARCHDIR)

depend: 
	-gcc -MM $(CFLAGS) *.cc > depend

-include depend
