VERSION=0.0.1

CFLAGS += -std=gnu11 -Wall

OBJECTS = simple_otp.c
SOURCES = $(patsubst %.o,%.c,$(OBJECTS))

all: simple_otp

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -O3 -o $@ $<

simple_otp: simple_otp.o
	$(CC) $(CPPFLAGS) $(CFLAGS) simple_otp.o $(LDFLAGS) -o simple_otp

install: all install-bin

install-bin:
	install -d -m 0755 $(DESTDIR)/usr/bin
	install -m 0755 simple_otp $(DESTDIR)/usr/bin

clean:
	rm -f *.o *~
	rm -f simple_otp

tag:
	@git tag -a -m "Tag as $(VERSION)" -f $(VERSION)
	@echo "Tagged as $(VERSION)"

archive:
	@git archive --format=tar --prefix=simple_otp-$(VERSION)/ HEAD |bzip2 > simple_otp-$(VERSION).tar.bz2
	@echo "The final archive is in simple_otp-$(VERSION).tar.bz2"
