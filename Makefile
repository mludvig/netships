# Makefile for NetShips
# Michal Ludvig <michal@logix.cz>

include Makefile.common

EXEC = netships

SUBDIRS = util comm ncu # sub-packages to build/install

INSTDIR=/usr/local/bin

all:	$(EXEC)

clean:
	rm -f *~ *.o core $(EXEC)
	for i in $(SUBDIRS); do $(MAKE) -C $$i clean; done

arch:	$(SUBDIRS)
	for i in $(SUBDIRS); do $(MAKE) -C $$i arch; done

lines:
	(for i in $(SUBDIRS); do wc -l $$i/*.cc $$i/*.[ch] 2>/dev/null; done) | awk -f bin/lines.awk

# Don't edit anything below this line

$(EXEC): $(SUBDIRS)
	make -C util all
	make -C comm all
	make -C ncu all
	cp ncu/$(EXEC) .

util:
	$(MAKE) -C util all

comm:
	$(MAKE) -C util comm

ncu:
	$(MAKE) -C util ncu

install: $(EXEC)
	install -s $(EXEC) $(INSTDIR)
