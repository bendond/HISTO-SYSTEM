# Histogram System

The histo system is comprised of 2 data producers and 1 data consumer. Uses forks, semaphores, and shared memory to manage the system. Both data producers share a "write head" within the shared memory block and use semaphores to write an arbitrary character to the shared memory. 
The Data consumer attaches to the shared memory block and uses a "read head" to read the values within the shared memory block to then display to the screen as a histogram

## Installation

Run the make file in the main directory. If that fails there are individual make files in each of the DC, DP1, and DP2 directories.

```bash
    make -f makefile
```

## Usage

Run the DP1 application created and placed at ./DP1/bin/ , it will fork the other applications needed to run. Do not move DP1/DP2/DC applications from their bin folders as it will cause forks to fail.

## Screenshots
* = 100, + = 10, - = 1
![App Screenshot](https://github.com/bendond/HISTO-SYSTEM/blob/main/images/HistogramImage.png?raw=true)

## License

[MIT](https://choosealicense.com/licenses/mit/)
