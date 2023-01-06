# Treasure-Maze

## Part 1: The Stack, Queue, and Deque Classes
### The Deque Class 
The underlying data structure will be a C++ standard vector. Following the convention of the queue where data is allowed to “float” in the vector. 
If, upon a removal, you discover that the contiguous block of data (whose size is, say, k) will “fit” in the first k empty positions of the vector,
then the Deque is resized down by making a new vector and copying the k pieces of data into that new vector. Additions to the structure can use the 
standard vector functions, and can only occur at the “right” side of the contiguous data (i.e. the position of largest index). 
(Note that in this implementation the structure is not “circular”– we do not wrap the data using the modulo of the array size.)


### The Stack Class
Basic Stack data structure with the addition of the peek() function. The push() and pop() functions are implemented in constant O(1) runtime 
The Stack is implemented with the Deque data structure previously mentioned. 


### The Queue Class
Basic Queue data structure with the addition of the peek() function. 
The enqueue() and dequeue() functions are implemented in constant O(1) runtime using the Deque data structure. 


## Part 2: Treasure Maze Maps
A few summers ago, a company called GoldHunt ran a treasure hunt adventure game, where for an entry fee of $75, Vancouverites could 
join in the hunt for a $100,000 treasure chest. Participants were given a map and collections of poetic clues that helped the hunters 
home in on the location of the treasure. It was a scavenger hunt, with a real prize! 
The GoldHunt idea was good, but low-tech, and it didn’t scale. This programming project develops an algorithmic tool for 
creating (and solving) treasure maps by hiding them within images.

### Part A -- Creating a Map
The image on the left is a base image onto which is encoded onto the maze on the right, resulting in an image which is essentially 
indistinguishable from the first. <br />
<img width="635" alt="Screen Shot 2023-01-05 at 9 10 22 PM" src="https://user-images.githubusercontent.com/119923836/210934437-d4270e51-6871-4de1-bd84-8f6d836c9797.png">

A treasure maze consists of a base image, a maze image, and a starting position. The treasure is found at the point (pixel location) 
whose shortest distance to the start in the maze is longest. A maze is simply an image containing a collection of points whose 
pixel colours are equivalent to the pixel colour of the start location, and reachable from the start location via a path of 
same-coloured pixels. To judge colour equivalence, the == operator within the RGBAPixel class.

The algorithm for embedding the maze into a treasure map is as follows:
<img width="602" alt="Screen Shot 2023-01-05 at 9 12 17 PM" src="https://user-images.githubusercontent.com/119923836/210934642-f7aeba51-99bc-4987-af87-f3563097262b.png">


The image below shows the maze and the start location superimposed on the base map. <br />
<img width="599" alt="Screen Shot 2023-01-05 at 9 13 40 PM" src="https://user-images.githubusercontent.com/119923836/210934801-b4f828ba-5953-41ed-8f7f-cb300174de14.png">

### Part B -- Finding the Treasure
The decoder for treasure maps created using the embedding algorithm from part A, and then solve the maze to find the treasure!
The algorithm for finding the maze embedded in the treasure map, given a starting point: <br />
<img width="610" alt="Screen Shot 2023-01-05 at 9 14 42 PM" src="https://user-images.githubusercontent.com/119923836/210934899-5127458d-6785-4134-a47d-5b96defb344a.png">


Once you have found the maze, you have to solve it to find the treasure! The treasure is located at the point on the map corresponding to 
the pixel whose shortest distance to the start, within the maze, is longest. In this context, distance is just the number of pixels on the 
path in the maze between any pair of pixels (inclusive). You will search the maze for the shortest distance from the start to each maze point, 
and then the solution will be the longest of those. The images below show the maze we discovered while decoding, and also the solution 
path to the treasure. <br />
<img width="606" alt="Screen Shot 2023-01-05 at 9 16 03 PM" src="https://user-images.githubusercontent.com/119923836/210935036-737b1666-a062-4935-847d-fce50304994f.png">


Finding and solving the maze will use an algorithm similar to the embedding algorithm  part A. 
