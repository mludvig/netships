# Makefile for NetShips
# Michal Ludvig <michal@logix.cz>

include Makefile.common

EXEC=netships
VER=`awk 'NR==1{print $1}' version`
SUBDIRS=util comm ncu # sub-packages to build/install
INSTDIR=/usr/local/bin

all:	$(EXEC)

clean:
	rm -f *~ *.o core $(EXEC) version.h
	for i in $(SUBDIRS); do $(MAKE) -C $$i clean; done

arch:	$(SUBDIRS)
	for i in $(SUBDIRS); do $(MAKE) -C $$i arch; done

dist: clean
	bin/dist.sh $(EXEC) $(VER)

lines:
	(for i in $(SUBDIRS); do wc -l $$i/*.cc $$i/*.[ch] 2>/dev/null; done) | awk -f bin/lines.awk

# Don't edit anything below this line

$(EXEC): version.h $(SUBDIRS)
	cp ncu/$(EXEC) .

non-existing-file:

util: non-existing-file
	$(MAKE) -C util all

comm: non-existing-file
	$(MAKE) -C comm all

ncu: non-existing-file
	$(MAKE) -C ncu all

version.h: version
	echo "#define VERSION \"$(VER)\"" > version.h

install: $(EXEC)
	install -s $(EXEC) $(INSTDIR)
