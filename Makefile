build:
	gcc ./src/*.c `sdl2-config --libs --cflags` -O3 -lm -o rasterizer

run:
	./rasterizer

perf: 
	perf stat -e cache-references,cache-misses ./rasterizer

clean:
	rm rasterizer
