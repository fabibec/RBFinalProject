#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/* Matrix conversion */
char mapStringMatrix[14][14];
uint8_t start;
char destinations[] = {'2', '3'};

void convertMapStringToMatrix(){
    const char* mapString = "###############     S      ###   #####   ##    11      ##            ##   ####   2 ##      #   2 ##      #     ##   ###########   #        ##   #   33   ##   #        ##            ###############";

    for (uint8_t i = 0; i < 196; i++) {
        mapStringMatrix[(i/14)][(i%14)] = mapString[i];
    }
}
/* Matrix conversion End*/

/* utils - use 1D as 2D and vise versa*/
uint8_t conv2Dto1D(uint8_t row, uint8_t col){
    return row * 14 + col;
}

void conv1Dto2D(uint8_t index, uint8_t* row, uint8_t* col){
    *row = index / 14;
    *col = index % 14;
}
/* utils - end */

/* Tracking start and possible end positions */
bool isTablePosition(char c){
    return (c == destinations[0] || c == destinations[1]);
}

void findStartPosition(){
    char currentChar;
    for (int8_t i = 1; i < 13; i++){
        for (int8_t j = 1; j < 13; j++) {
            currentChar = mapStringMatrix[i][j];
            if (currentChar == 'S') {
                start = conv2Dto1D(i,j);
                return;
            }
        }
    }
}
/* Tracking start and possible end positions - end */

/* Dijkstra Pathfinding */
typedef struct{
    bool visited;
    uint16_t distance; // distance to start
    uint8_t prev; //address of previous
} dj_info;
dj_info runtime_infos[196];

uint8_t minDistance(){
    uint16_t min = UINT16_MAX;
    uint8_t min_index;

    for (uint8_t v = 0; v < 196; v++)
        if (runtime_infos[v].visited == false && runtime_infos[v].distance <= min)
            min = runtime_infos[v].distance, min_index = v;

    return min_index;
}

void printSolution(){
    uint8_t x, y, x2, y2;
    uint16_t distance;
    conv1Dto2D(start, &x, &y);
    printf("Start: (%d,%d)\n", x, y);
    printf("Vertex\t\tDistance from Source\t\tFrom\n");
    for (int i = 0; i < 196; i++) {
        distance = runtime_infos[i].distance;
        if (distance < UINT16_MAX) {
            conv1Dto2D(runtime_infos[i].prev, &x, &y);
            conv1Dto2D(i, &x2, &y2);
            printf("(%d,%d)\t\t\t\t%d\t\t(%d,%d)\n", x2, y2, distance, x, y);
        }
    }
}

void dijkstra(){
    for(uint8_t i = 0; i < 196; ++i){
        runtime_infos[i].visited = false;
        runtime_infos[i].distance = UINT16_MAX;
        runtime_infos[i].prev = i;
    }
    runtime_infos[start].distance = 0;

    for (uint8_t count = 0; count < 196 - 1; count++) {
        uint8_t u = minDistance();

        runtime_infos[u].visited = true;

        int16_t adjacent[4] = {-1, -1, -1, -1};
        if(u >= 14){
            adjacent[0] = (int16_t) u - 14;
        }
        if(u <= 196 - 1 - 14){
            adjacent[1] = (int16_t) u + 14;
        }
        if(u != 0 || u % 14 != 0){
            adjacent[2] = (int16_t) u - 1;
        }
        if(u != 196 - 1 || u % 14 != 13){
            adjacent[3] = (int16_t) u + 1;
        }
        uint8_t x, y;
        for(uint8_t v = 0; v < 4; v++){
            if(adjacent[v] != -1){
                conv1Dto2D(adjacent[v], &x, &y);
            } else {
                break;
            }
            if (mapStringMatrix[x][y] == ' '
                && runtime_infos[u].distance != UINT16_MAX
                && !runtime_infos[v].visited
                && (runtime_infos[u].distance + 1) < runtime_infos[adjacent[v]].distance){
                runtime_infos[adjacent[v]].distance = runtime_infos[u].distance + 1;
                runtime_infos[adjacent[v]].prev = u;
            }
        }

    }
    // print the constructed distance array
    printSolution();
}
/* Dijkstra Pathfinding End */

int main() {
    convertMapStringToMatrix();
    findStartPosition();
    dijkstra();
}

