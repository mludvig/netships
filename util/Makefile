#
# standard Makefile
#

TOPDIR = ../

include $(TOPDIR)/Makefile.common

EXEC = libutil.a
OBJS = failprog.o

all:	$(EXEC)

$(EXEC): $(OBJS)
	$(AR) rcv $(EXEC) $(OBJS)

# Some service targets:
clean: 
	rm -f *.o *~ $(EXEC) core

arch: 
	tar cvfz lib.`$(ARCHDATE)`.tgz *.c *.h Makefile $(EXEC)
	mv lib.*.tgz $(ARCHDIR)

