#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG & tm, pair<int,int> s)
   :start(s),mapImg(tm) {

/* YOUR CODE HERE */
mazePts.push_back(start);

int garb_val =  mapImg.width()*mapImg.height();
std::vector<std::vector<bool>> visit_data (mapImg.width(), std::vector<bool>(mapImg.height(), false));
std::vector<std::vector<int>> dist_data (mapImg.width(), std::vector<int>(mapImg.height(), garb_val));
std::vector<std::vector<pair<int,int>>> path_data (mapImg.width(), std::vector<pair<int,int>>(mapImg.height(), make_pair(garb_val, garb_val)));
// vector for saving location of discovery 

Queue<pair<int,int>> visit_queue;
visit_data[start.first][start.second] = true;
dist_data[start.first][start.second] = 0;
visit_queue.enqueue(start);

pair<int, int> curr;
while (!visit_queue.isEmpty()) {
    curr = visit_queue.dequeue();

    vector<pair<int,int>> curr_neighbors = neighbors(curr);
    for (int i = 0; i < 4; i++) {
        pair<int,int> p = curr_neighbors[i];

        if(good(visit_data, dist_data, curr, p)) { 
            
            int dist = dist_data[curr.first][curr.second] + 1;
            
            visit_data[p.first][p.second] = true;
            dist_data[p.first][p.second] = dist;

            mazePts.push_back(p);

            // save discovery loc
            path_data[p.first][p.second] = curr;

            visit_queue.enqueue(p);
        }
    }
}

// after breadth-first search curr == treasure spot 
// create a stack starting at treasure until start 

Stack<pair<int,int>> path_stack;
path_stack.push(curr);
while(curr != start) {
    curr = path_data[curr.first][curr.second]; // location curr was discovered 
    path_stack.push(curr);
}

// pop stack untill empty -- add to a vector for path points to be in order 
pair<int,int> next;
while(!path_stack.isEmpty()) {
    next = path_stack.pop();
    pathPts.push_back(next);
}

}

PNG decoder::renderSolution(){

/*!!!*/
pair<int,int> curr;
PNG copy_map(mapImg);
for (int i = 0; i < pathPts.size(); i++) {
   curr = pathPts[i];
   setRed(copy_map, curr);
}
return copy_map;
}

PNG decoder::renderMaze(){

/*!!!*/
pair<int,int> curr;
PNG copy_map(mapImg);
for (int i = 0; i < mazePts.size();i++) {
   curr = mazePts[i];
   setGrey(copy_map, curr);
}

// make red 7px by 7px bow where the starting position is at the center 
Queue<pair<int,int>> squareQueue = startSquare(start);
while(!squareQueue.isEmpty()) {
    curr = squareQueue.dequeue();
    if (curr.first < mapImg.width() && curr.second < mapImg.height() && curr.first >= 0 && curr.second >= 0) {
        setRed(copy_map, curr);
    }
}
return copy_map;
}

// creates vector with all the px locations for a 7px by 7px square around given curr 
Queue<pair<int, int>> decoder::startSquare(pair<int,int> curr) {
    // !!!
    Queue<pair<int,int>> square; 
    for (int col = curr.first - 3; col <= curr.first + 3; col++) {
        for (int row = curr.second - 3; row <= curr.second + 3; row++) {
            square.enqueue(make_pair(col, row));
        }
    }
    return square;
}


void decoder::setRed(PNG & im, pair<int,int> loc) {
   RGBAPixel* px = im.getPixel(loc.first, loc.second);
    px->r = 255;
    px->g = 0;
    px->b = 0;
}

void decoder::setGrey(PNG & im, pair<int,int> loc){

/* !!! */
RGBAPixel* px = im.getPixel(loc.first, loc.second);
px->r = 2*(px->r / 4);
px->g = 2*(px->g / 4);
px->b = 2*(px->b / 4);

}

pair<int,int> decoder::findSpot(){

/* YOUR CODE HERE */
return pathPts.back(); 

}

int decoder::pathLength(){

/* YOUR CODE HERE */
return pathPts.size();

}

bool decoder::good(vector<vector<bool>> & v, vector<vector<int>> & d, pair<int,int> curr, pair<int,int> next){

/* YOUR CODE HERE */
if (next.first < mapImg.width() && next.second < mapImg.height() && next.first >= 0 && next.second >= 0) { // test that next is within image
   
   if (!v[next.first][next.second]) { // test if next is unvisited 

      RGBAPixel* p = mapImg.getPixel(next.first, next.second);
      return compare(*p, d[curr.first][curr.second]); // tests if next is encoded with correct color 
   }

}
return false;

}

vector<pair<int,int>> decoder::neighbors(pair<int,int> curr) {

/* !!! */
vector<pair<int, int>> neighbor_loc;
neighbor_loc.push_back(make_pair(curr.first - 1, curr.second));     // left 
neighbor_loc.push_back(make_pair(curr.first,     curr.second + 1)); // below 
neighbor_loc.push_back(make_pair(curr.first + 1, curr.second));     // right 
neighbor_loc.push_back(make_pair(curr.first,     curr.second - 1)); // above

return neighbor_loc;

}


bool decoder::compare(RGBAPixel p, int d){

/*!!!*/
int p_num = (p.r % 4)*16 + (p.g % 4)*4 + (p.b % 4);
return p_num == ((d+1) % 64);

}
