Creating Mandelbrot set

Teodor Linnik 
-------------------------------
Brief explanation:
I created 2 shaders:
basicShader - for 2D texture support
basicShader2 - for 1D texture
they are basically the same, except the last lines where I decide which texture I use

Shader implementation:
I checked the coordinate and using it x and y values, I created c.
I sent c and p as parameters to mendelbrot function and received n as the number of iterations
after adjusting the color, I sampled the color from the texture that matched our color value.


* To support Zooming in and out, in scroll_callback at inputmanager.h 
  I changed the pixel width and updated the center of the scene accordingly
* To support 2D AddTexture, I changed the Texture function at texture.cpp 
  to support 2D in addition to 1D texture (depending on "for2D" parameter)
