# Smiley



## Learning Goals

- Learn how to work with images
- Practice manipulating pixels

## Background

You’ve seen in lecture a bit about how images are stored on a computer. In this lab, you’ll practice working with a BMP file, actually the smiley face pictured here, and change all the black pixels to a color of your choosing.

However, the smiley face you’ll be working with is not just made of of 0’s and 1’s, or black and white pixels, but consists of 24 bits per pixel. It uses eight bits to represent red values, eight bits for green and eight bits for blue. Since each color uses eight bits or one byte, we can use a number in the range of 0 to 255 to represent its color value. In hexadecimal, this is represented by 0x00 to 0xff. By mixing together these red, green and blue values, we can create millions of possible colors.

If you look at bmp.h, one of the the helper files in the distribution code, you’ll see how each RGB triple is represented by a struct like:

```lang-C
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
}
RGBTRIPLE;
```

where BYTE is defined as an 8-bit integer.

You’ll notice several files provided in the distribution code to handle the reading and writing of an image file, as well as handling the image’s metadata or “headers”. You’ll be completing the function colorize in helpers.c, which already has as input parameters, the image’s height, width, and a two-dimensional array of RGBTRIPLE’s which create the image itself.

## Implementation

The image’s height, width and a two-dimensional array of pixels is set up as the input parameters for the function colorize. This function changes all the black pixels in the image to a color of your choosing.


## Usage

```lang-bash
$ ./colorize smiley.bmp outfile.bmp
```

outfile.bmp is the name of the new bmp you are creating.

## Question 1

How do you think you represent a black pixel when using a 24-bit color BMP file?

A black pixel is represented by the RGB color value (0,0,0), where each component (red, green, blue) is represented by an 8-bit unsigned integer. This means that the red, green, and blue components are all set to their minimum value of 0, resulting in the absence of color and the appearance of black. The right combination of bits will mix the right combination of Red, Green and Blue in order to for our eyes to perceive it as a specific color.

## Question 2

Is this the same or different when mixing paints to repesent various colors?

the process of representing colors is different from the digital representation in a BMP file. In paint mixing, colors are typically represented using subtractive color mixing, where pigments or dyes are mixed together to absorb specific wavelengths of light and reflect others.
in additive color mixing, such as with digital displays, colors are created by adding together different colors of light (typically red, green, and blue) to produce a range of colors. The absence of any light produces black, while the presence of all colors of light produces white. This could be considered the same as with pixels.
