
VERSION=0.9.0

FLAGS=-O2 `pkg-config --libs --cflags libgtop-2.0` -Wall -lpthread -DWHICH_XMESSAGE=\"`which xmessage`\"  -DVERSION=\"$(VERSION)\"

TAR=das_watchdog

DIST=$(TAR)-$(VERSION)


all:
	which xmessage
	gcc das_watchdog.c -o das_watchdog $(FLAGS)
	gcc test_rt.c -o test_rt

dist:
	make clean
	rm -fr $(DIST).tar.gz $(DIST)
	mkdir /tmp/$(DIST)
	cp -a * /tmp/$(DIST)
	mv /tmp/$(DIST) .
	tar cvf $(DIST).tar $(DIST)
	gzip $(DIST).tar
	marcel_upload $(DIST).tar.gz

clean:
	rm -f das_watchdog test_rt *~

