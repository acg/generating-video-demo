#include <unistd.h>
#include <stdio.h>

int mandelbrot_escapes(double cx, double cy, int n);

int main()
{
  int cx = 640;
  int cy = 480;
  char bitmap[cy][cx][3];

  double rx = 2.0;
  double ry = rx * cy / cx;
  double ox = 0.0, oy = 0.0;
  double ax = ox-rx, ay = oy-ry;
  double bx = ox+rx, by = oy+ry;
  double dx = (bx-ax)/cx, dy = (by-ay)/cy;

  int nx, ny;
  double x, y;

  for (int iterations=1; iterations<100; iterations++) {
    for (y=ay, ny=0; ny<cy; y+=dy, ny++) {
      for (x=ax, nx=0; nx<cx; x+=dx, nx++) {
        int q = mandelbrot_escapes(x,y,iterations);
        for (int nrgb=0; nrgb<3; nrgb++)
          bitmap[ny][nx][nrgb] = (char)(q * 0xff / iterations);
      }
    }
    if (write(1, bitmap, sizeof bitmap) < 0) {
      perror("write error on stdout");
      return 111;
    }
  }

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
