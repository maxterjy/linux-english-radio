.PHONY: all audioplayer newspuller tinyxml2

all: audioplayer newspuller

audioplayer:
	g++ audioplayer.cpp -o audioplayer -g `pkg-config --cflags --libs gstreamer-1.0 gstreamer-audio-1.0` -Wno-format-overflow -Wno-literal-suffix -Wno-write-strings

newspuller: tinyxml2
	g++ newspuller.cpp lib/tinyxml2/libtinyxml2.a -o newspuller `curl-config --static-libs` -pthread -g -Wno-write-strings -Ilib

tinyxml2:
	make --directory lib/tinyxml2

clean:
	rm audioplayer newspuller .channel_html .channel_list
