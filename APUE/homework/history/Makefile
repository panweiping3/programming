main: main.c
	gcc -shared -o logger.so logger.c -ldl
	gcc -o main main.c

clean:
	rm main logger.so
