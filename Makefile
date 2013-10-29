# compiler flags
CFLAGS += -O3
CFLAGS += -std=c99
CFLAGS += -Wall

# size of picture, before matting
PICTURE_WIDTH = 512
PICTURE_HEIGHT = 512

# matted video
MATTE_WIDTH = $(PICTURE_WIDTH)
MATTE_HEIGHT = $(PICTURE_HEIGHT)
MATTE_COLOR = violet

# video input options
FFMPEG_IN_OPTS += -f rawvideo
FFMPEG_IN_OPTS += -pix_fmt rgb24
FFMPEG_IN_OPTS += -s $(PICTURE_WIDTH)x$(PICTURE_HEIGHT)
FFMPEG_IN_OPTS += -i /dev/stdin

# common video output options
FFMPEG_OUT_OPTS += -vf pad="$(MATTE_WIDTH):$(MATTE_HEIGHT):(ow-iw)/2:(oh-ih)/2:$(MATTE_COLOR)"

# video output options - H.264
FFMPEG_H264_OPTS += -y
FFMPEG_H264_OPTS += -vcodec mpeg4
FFMPEG_H264_OPTS += -sameq -r 30000/1001 -b 200k -bt 240k
FFMPEG_H264_OPTS += $(FFMPEG_OUT_OPTS)

# video output options - GIF
FFMPEG_GIF_OPTS += -y
FFMPEG_GIF_OPTS += $(FFMPEG_OUT_OPTS)


all : mandelbrot

mp4 : mandelbrot.mp4

gif : mandelbrot.gif

mandelbrot.mp4 : mandelbrot
	./mandelbrot $(PICTURE_WIDTH) $(PICTURE_HEIGHT) | ffmpeg $(FFMPEG_IN_OPTS) $(FFMPEG_H264_OPTS) $@

mandelbrot.gif : mandelbrot
	./mandelbrot $(PICTURE_WIDTH) $(PICTURE_HEIGHT) | ffmpeg $(FFMPEG_IN_OPTS) $(FFMPEG_GIF_OPTS) $@

mandelbrot : mandelbrot.c

clean :
	rm -f mandelbrot.mp4 mandelbrot.gif mandelbrot *.o


### Delete $@ if a rule fails. GNU make-specific.
### You'd think this would be the default behavior.

.DELETE_ON_ERROR :

