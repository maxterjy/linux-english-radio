.PHONY: all audioplayer newspuller tinyxml2 app

all: app

app: audioplayer newspuller
	g++ app.cpp audioplayer.o newspuller.o -Ilib -o app -g -lpthread `pkg-config --cflags-only-I --libs gstreamer-1.0 gstreamer-audio-1.0` `curl-config --static-libs` lib/tinyxml2/libtinyxml2.a

audioplayer:
	g++ -c audioplayer.cpp -o audioplayer.o -g `pkg-config --cflags --libs gstreamer-1.0 gstreamer-audio-1.0` -Wno-format-overflow -Wno-literal-suffix -Wno-write-strings

newspuller: tinyxml2
	g++ -c newspuller.cpp lib/tinyxml2/libtinyxml2.a -o newspuller.o `curl-config --static-libs` -pthread -g -Wno-write-strings -Ilib

tinyxml2:
	make --directory lib/tinyxml2

clean:
	rm audioplayer.o newspuller.o .channel_html .channel_list
