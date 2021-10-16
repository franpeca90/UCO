How to compile
==============
    - mkdir build
    - cd build
    - cmake ..
    - make


How to run the program
======================
    - ./assignment7 [image path]


How to use
==========
The program must be executed as follows:
 
    ./assignment7 in_image out_image -thres <val> -op <(erode|dilate|open|close)> 

    -thres <val> : threhold value. The image will be thresholded using this value. pixels BELOW this value will be set to 255, the others to 0.

    -op <string>:  the morphological operation to be applied.

The out_image will be storage in "build" directory by default, and must end with ".jpg". This is important.

This is an example:

    ./assignment7 ../img.jpg result.jpg --thres 150 --op close