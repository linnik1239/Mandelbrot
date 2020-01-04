Creating Mandelbrot set

Teodor Linnik 
-------------------------------
Brief explanation:
We created 2 shaders:
basicShader - for 2D texture support
basicShader2 - for 1D texture
they are basically the same, except the last lines where we decide which texture we use

Shader implementation:
We checked the coordinate and using it x and y values, we created c.
we sent c and p as parameters to mendelbrot function and received n as the number of iterations
after adjusting the color, we sampled the color from the texture that matched our color value.


* To support Zooming in and out, in scroll_callback at inputmanager.h 
  we changed the pixel width and updated the center of the scene accordingly
* To support 2D AddTexture, we changed the Texture function at texture.cpp 
  to support 2D in addition to 1D texture (depending on "for2D" parameter)
