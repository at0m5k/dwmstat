PROG	  = dwmstat
CC	  = gcc
PREFIX	 ?= /usr/local
BINPREFIX = ${PREFIX}/bin

LIBS	 = -lX11 -liw -lasound
CFLAGS	 = -pedantic -Wall -Wextra -Wno-format-zero-length

${PROG}: ${PROG}.c ${PROG}.h
	@${CC} ${CFLAGS} ${LIBS} -o ${PROG} ${PROG}.c
	@strip ${PROG}

install:
	install -Dm755 ${PROG} ${DESTDIR}${BINPREFIX}/${PROG}
	install -Dm644 ${PROG}.service ${DESTDIR}/usr/lib/systemd/system/${PROG}.service

uninstall:
	rm -f ${BINPREFIX}/${PROG}
	rm -f /usr/lib/systemd/system/${PROG}.service

clean:
	rm -f ${PROG}
