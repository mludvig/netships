#
# standard Makefile
#

TOPDIR  = ../

include $(TOPDIR)/Makefile.common

EXEC	= libcomm.a
OBJS	= fmesg.o rw.o commsupp.o

ARCHDATE= $(TOPDIR)/bin/archdate

# Place your targets here:
#example: ex1.o ex2.o
#	$(CC) $(CFLAGS) -o example $^ $(LIBOPT)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(AR) rcv $(EXEC) $(OBJS)

# Some service targets:
clean: 
	rm -f *.o *~ core $(EXEC)

arch: 
	tar cvfz comm.`$(ARCHDATE)`.tgz *.c *.h Makefile $(EXEC)
	mv comm.*.tgz $(ARCHDIR)
