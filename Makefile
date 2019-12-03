.PHONY: all audioplayer

all: audioplayer

audioplayer:
	g++ audioplayer.cpp -o audioplayer -g `pkg-config --cflags --libs gstreamer-1.0 gstreamer-audio-1.0`


clean:
	rm audioplayer