# stereo-block-matching
Constructing disparity image from a stereo pair using stereo block matching. The code uses the sum of square differences (SSD) as a metric to compare windows.

# dependencies
The program was compiled with OpenCV-2.4.13 and g++-5

# usage
The repository contains a directory of stereo images to get started. These are a subset from the Middlebury dataset.
To run the program first compile the file:

```g++ one.cpp -o one `pkg-config --cflags --libs opencv```

To run the file:

```./sbm <index_of_folder_to_use>```

{"img/Art", "img/Books", "img/Dolls", "img/Laundry", "img/Moebius", "img/Reindeer"}

Depending on the window size and the permissible range to search from the center pixel, the execution time may vary. The parameters can be tuned by the following:

```
\\ default values
int disparity_min = -50, disparity_max = 50; \\ search 50 pixels on either side of the current pixel
int disparity_range = disparity_max - disparity_min;
int half_block_size = 8
```
