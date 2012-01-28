CFLAGS += -O3
CFLAGS += -std=c99
CFLAGS += -Wall

# video input options
FFMPEG_OPTS += -f rawvideo
FFMPEG_OPTS += -pix_fmt rgb24
FFMPEG_OPTS += -s 640x480
FFMPEG_OPTS += -i /dev/stdin

# video output options
FFMPEG_OPTS += -y
FFMPEG_OPTS += -vcodec mpeg4
FFMPEG_OPTS += -sameq -r 30000/1001 -b 200k -bt 240k
#FFMPEG_OPTS += -vcodec libx264
#FFMPEG_OPTS += -vpre hq -vpre ipod640


mandelbrot.mp4 : mandelbrot
	./mandelbrot | ffmpeg $(FFMPEG_OPTS) $@

mandelbrot : mandelbrot.c

clean :
	rm -f mandelbrot.mp4 mandelbrot *.o

