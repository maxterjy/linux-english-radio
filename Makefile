.PHONY: all audioplayer newspuller

all: audioplayer newspuller

audioplayer:
	g++ audioplayer.cpp -o audioplayer -g `pkg-config --cflags --libs gstreamer-1.0 gstreamer-audio-1.0` -Wno-format-overflow -Wno-literal-suffix -Wno-write-strings

newspuller:
	g++ newspuller.cpp -o newspuller `curl-config --static-libs` -pthread -g


clean:
	rm audioplayer newspuller .channel_html .channel_list
