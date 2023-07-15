# Bottom-Up

A practice problem that makes a bitmap image from bottom-up to top-down orientation.

## Learning Goals

- Practice working with images
- Learn about metadata
- Learn more about how structs can be useful

## Background

Imagine an image you need to present to your boss for a major presentation somehow got corrupted! Upon investigating, you find that the image is mostly intact. Except, when you view the image, it now appears to be upside down!

Recall that a digital image file is just a sequence of bits, arranged in some fashion. A 24-bit BMP file, then, is essentially just a sequence of bits, (almost) every 24 of which happen to represent some pixel’s color. But a BMP file also contains some “metadata,” information like an image’s height and width. That metadata is stored at the beginning of the file in the form of two data structures generally referred to as “headers,” not to be confused with C’s header files. The first of these headers, called BITMAPFILEHEADER, is 14 bytes long. (Recall that 1 byte equals 8 bits.) The second of these headers, called BITMAPINFOHEADER, is 40 bytes long. Immediately following these headers is the actual bitmap: an array of bytes, triples of which represent a pixel’s color.

Your job is to edit the metadata programmatically so that the bitmap’s top row is first and bottom row last. Best to avoid editing the pixels directly, lest you further corrupt the file!

## Implementation

BITMAPFILEHEADER and BITMAPINFOHEADER are included, along with their documentations from Microsoft, per the comments in bmp.h. This information is used to write a bit of code in bottomup.c to change the image from bottom-up to top-down.

## Usage

```lang-bash
$ ./bottomup <input_file.bmp> <output_file.bmp>
```

## Question

Why do image files need metadata?

- Organizing and managing images: Metadata can help you sort and organize your image collection based on different criteria, such as location, date, and subject.
- Copyright and ownership: Metadata can include information about the photographer or copyright owner of the image, which can be important for protecting the image from unauthorized use or infringement.
- Search and discovery: Metadata can make it easier to search for and discover images based on specific criteria or keywords, such as the name of a location or event.
- Editing and processing: Metadata can be used by image editing software to make adjustments to the image, such as correcting the exposure or color balance.

Overall, metadata provides additional context and information about an image that can be useful for various purposes, from managing and organizing image collections to protecting intellectual property and improving image processing.
