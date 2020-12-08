DESTDIR="/usr/bin"

dcal:dcal.c
	cc dcal.c -o dcal

install:
	cc dcal.c -o dcal
	mv ./dcal $(DESTDIR)

clean:
	rm dcal
