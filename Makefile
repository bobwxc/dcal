dcal:dcal.c
	cc dcal.c -o dcal

install:
	cc dcal.c -o dcal
	mv ./dcal /usr/bin/

clean:
	rm dcal
