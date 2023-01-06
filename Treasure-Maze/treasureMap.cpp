#include "treasureMap.h"
#include "queue.h"

using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{
/* !!! */
start = s;
base = baseim;
maze = mazeim;
}

void treasureMap::setGrey(PNG& im, pair<int,int> loc){

/*!!!*/
RGBAPixel* px = im.getPixel(loc.first, loc.second);
px->r = 2*(px->r / 4);
px->g = 2*(px->g / 4);
px->b = 2*(px->b / 4);

}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){

/* !!! */
// unsigned int d_bits = d%64;
RGBAPixel* px = im.getPixel(loc.first, loc.second);

px->r = ((px->r / 4) * 4) + (d/16)%4;
px->g = ((px->g / 4) * 4) + (d/4)%4;
px->b = ((px->b / 4) * 4) + d%4;
}

PNG treasureMap::renderMap(){
/* !!! */
// 0) make a copy of the base image 

PNG copy_base(base);

// 1a) 2d vector same dimensions as the image - hold boolean
// 1b) 2d vector, same dimensions as base -- hold int value 

std::vector<std::vector<bool>> visit_data (base.width(), std::vector<bool>(base.height(), false));
std::vector<std::vector<int>> dist_data (base.width(), std::vector<int>(base.height(), base.width()*base.height()));

// 2) initialize a queue whose purpose is to orchestrate the traversal - keep point to visit
Queue<pair<int,int>> visit_queue;

// 3) mark start location as visited, dist 0, encode distance in lower bits of map, enqueue pos
visit_data[start.first][start.second] = true;
dist_data[start.first][start.second] = 0;

setLOB(copy_base, start, 0);

visit_queue.enqueue(start);

/* 4) while the queue is not empty 
      a. cur = value at front of queue (and dequeue)
      b. for each compas neighbor, p, (left, below, right, above)
            i. if p is "good"
                1) mark p visited
                2) set p's distance to curr's distance + 1
                3) encode the distance in the lower order bits of the treasure map
                4) enqueue p
*/
 
pair<int, int> curr;
while (!visit_queue.isEmpty()) {
    curr = visit_queue.dequeue();

    vector<pair<int,int>> curr_neighbors = neighbors(curr);
    for (int i = 0; i < 4; i++) {
        pair<int,int> p = curr_neighbors[i];

        if(good(visit_data, curr, p)) { 
            
            int dist = dist_data[curr.first][curr.second] + 1;
            
            visit_data[p.first][p.second] = true;
            dist_data[p.first][p.second] = dist;

            setLOB(copy_base, p, dist);

            visit_queue.enqueue(p);
        }
    }
}

// 5) return image
return copy_base;

}


PNG treasureMap::renderMaze(){

/* !!! */
PNG copy_base(base);

std::vector<std::vector<bool>> visit_data (base.width(), std::vector<bool>(base.height(), false));

Queue<pair<int, int>> visit_queue;

visit_data[start.first][start.second] = true;

setGrey(copy_base, start); // a bit unnecessary? Since will change to red later???

visit_queue.enqueue(start);

pair<int, int> curr;
while (!visit_queue.isEmpty()) {
    curr = visit_queue.dequeue();

    vector<pair<int,int>> curr_neighbors = neighbors(curr);
    for (int i = 0; i < 4; i++) {
        pair<int,int> p = curr_neighbors[i];

        if(good(visit_data, curr, p)) {
            visit_data[p.first][p.second] = true;
            setGrey(copy_base, p);
            visit_queue.enqueue(p);
        }
    }
}

// make red 7px by 7px bow where the starting position is at the center 
Queue<pair<int,int>> squareQueue = startSquare(start);
while(!squareQueue.isEmpty()) {
    curr = squareQueue.dequeue();
    if (curr.first < base.width() && curr.second < base.height() && curr.first >= 0 && curr.second >= 0) {
        setRed(copy_base, curr);
    }
}

return copy_base;

}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

/* !!! */
if (next.first < base.width() && next.second < base.height() && next.first >= 0 && next.second >= 0) { // (1) checks if next is within image 
   
    if (!v[next.first][next.second]) { // (2) checks that next is unvisited (false)
        
        RGBAPixel* px_curr = maze.getPixel(curr.first, curr.second);
        RGBAPixel* px_next = maze.getPixel(next.first, next.second);
        if (px_curr->r == px_next->r && px_curr->g == px_next->g && px_curr->b == px_next->b) { // (3) checks that next is the same colour as curr in maze image
            return true;
        }
    }
}
return false;

}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {

/* !!! */
vector<pair<int, int>> neighbor_loc;
neighbor_loc.push_back(make_pair(curr.first - 1, curr.second));     // left 
neighbor_loc.push_back(make_pair(curr.first,     curr.second + 1)); // below 
neighbor_loc.push_back(make_pair(curr.first + 1, curr.second));     // right 
neighbor_loc.push_back(make_pair(curr.first,     curr.second - 1)); // above

return neighbor_loc;

}

void treasureMap::setRed(PNG& im, pair<int,int> loc) {
    // !!!
    RGBAPixel* px = im.getPixel(loc.first, loc.second);
    px->r = 255;
    px->g = 0;
    px->b = 0;
}

Queue<pair<int, int>> treasureMap::startSquare(pair<int,int> curr) {
    // !!!
    Queue<pair<int,int>> square; 
    for (int col = curr.first - 3; col <= curr.first + 3; col++) {
        for (int row = curr.second - 3; row <= curr.second + 3; row++) {
            square.enqueue(make_pair(col, row));
        }
    }
    return square;
}


