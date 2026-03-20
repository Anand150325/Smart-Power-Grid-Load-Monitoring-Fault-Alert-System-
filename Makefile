all:
	gcc main.c controller.c ipc.c log.c signal.c -o grid -lrt

run:
	./grid

clean:
	rm -f grid
