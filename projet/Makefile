.PHONY: all debug install clean

all: 
	(cd lib; make all)
	(cd app; make all)

debug:
	(cd lib; make all)
	(cd app; make debug)

install: all
	(cd app; make install)
	serieViaUSB -l

clean: 
	(cd lib; make clean)
	(cd app; make clean)