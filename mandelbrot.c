#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int mandelbrot_escapes(double cx, double cy, int n);

int main(int argc, char **argv)
{
  int cx = 128;
  int cy = 128;
  int max_iterations = 100;

  if (argc > 4) {
    fprintf(stderr, "usage: %s [width] [height] [max-iterations]\n", argv[0]);
    return 1;
  }

  argc--; argv++;

  if (argc) cx = atoi((argc--, *argv++));
  if (argc) cy = atoi((argc--, *argv++));
  if (argc) max_iterations = atoi((argc--, *argv++));

  char *bitmap;
  unsigned int bitmap_size = cx*cy*3;

  if (!(bitmap = malloc(bitmap_size))) {
    perror("malloc failed");
    return 111;
  }

  double rx = 2.0;
  double ry = rx * cy / cx;
  double ox = 0.0, oy = 0.0;
  double ax = ox-rx, ay = oy-ry;
  double bx = ox+rx, by = oy+ry;
  double dx = (bx-ax)/cx, dy = (by-ay)/cy;

  int nx, ny;
  double x, y;

  for (int iterations=1; iterations<max_iterations; iterations++) {
    for (y=ay, ny=0; ny<cy; y+=dy, ny++) {
      for (x=ax, nx=0; nx<cx; x+=dx, nx++) {
        int q = mandelbrot_escapes(x,y,iterations);
        for (int nrgb=0; nrgb<3; nrgb++)
          bitmap[ny*cx*3 + nx*3 + nrgb] = (char)(q * 0xff / iterations);
      }
    }
    if (write(1, bitmap, bitmap_size) < 0) {
      perror("write error on stdout");
      return 111;
    }
  }

  free(bitmap);

  return 0;
}

int mandelbrot_escapes(double cx, double cy, int n)
{
  double zx = 0, zy = 0;
  double i = 0;

  while (n > 0) {
    if (zx * zx + zy * zy > 2.0) return i;
    double newzx = zx * zx - zy * zy + cx;
    double newzy = 2 * zx * zy + cy;
    zx = newzx;
    zy = newzy;
    n--; i++;
  }

  return i;
}
