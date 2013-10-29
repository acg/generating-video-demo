# Generating Video Programmatically - A Quick Demo #

So you want to make programmatically generated video content?

Codecs, encoding parameters, container formats...it all sounds pretty painful. But it's actually pretty easy. Just write a program that pipes raw rgb video frames into [ffmpeg](http://ffmpeg.org/), and let it do all the heavy lifting.

Herein lies a little demo of the technique. The generated video is of the [Mandelbrot set](http://en.wikipedia.org/wiki/Mandelbrot_set) coming into focus as the maximum escape iterations increases.

    make

    make mp4
    vlc mandelbrot.mp4

    make gif
    google-chrome mandelbrot.gif

