#DESTDIR="/usr/bin/"

dcal:dcal.c
	cc dcal.c -o dcal

#install:
#	mv ./dcal $(DESTDIR)

clean:
	rm dcal
