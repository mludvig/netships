#
# standard Makefile
#

TOPDIR  = ../

include $(TOPDIR)/Makefile.common

LIBOPT  += -lncurses
CFLAGS  += -I$(TOPDIR)/util -I$(TOPDIR)/comm
ARCHDIR = $(TOPDIR)/arch

DIRUTIL = ../util
DIRCOMM	= ../comm

LIBUTIL	= $(DIRUTIL)/libutil.a
LIBCOMM = $(DIRCOMM)/libcomm.a

EXEC	= netships
OBJS	= sea.o main.o pool.o comm.o sea2.o poolk.o poolu.o info.o poolk-fill.o

all: depend $(EXEC)

$(EXEC): $(OBJS) $(LIBUTIL) $(LIBCOMM)
	$(CXX) -o $(EXEC) $(OBJS) $(LIBOPT) $(LIBUTIL) $(LIBCOMM)

$(LIBUTIL):
	$(MAKE) -C $(DIRUTIL) all

$(LIBCOMM):
	$(MAKE) -C $(DIRCOMM) all

# Some service targets:
clean: 
	rm -f *.o *~ core $(EXEC) depend

depend: 
	-gcc -MM $(CFLAGS) *.cc > depend

-include depend
