#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

int W, H, L, K;
//W - park width
//H - park height
//L - infection's level
//K - number of mans(boys)

int boysCounter;
struct Cell{
    int type;
    int counter;
};

Cell ** readData(Cell ** park, bool readWay){

    fstream file ("random30_2.in",std::ios::in);

    if (readWay == false){
        string data;
        getline(file, data);

        stringstream ss;
        ss << data;

        string temp;
        int found;
        int firstLine[4];
        int counter = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (stringstream(temp) >> found){
                firstLine[counter] = found; 
				cout << firstLine[counter] << " ";
            }
            temp = "";
            counter ++;
        }
        W = firstLine[0];
        H = firstLine[1];
        L = firstLine[2];
        K = firstLine[3];

        getline(file, data);
        cout << endl << "name is: " << data << endl;
    }
    else{
        cin >> W;
        cin >> H;
        cin >> L;
        cin >> K;
        string name;
        cin >> name;
    }



    park = new Cell*[W];
    for (int i = 0; i < W; i ++){
        park[i] = new Cell[H];
    }

    if (readWay == false){

        string data;
        for(int i = 0; i < H; i++){
            getline(file, data);
            cout << data << endl;

            for (int j = 0; j < W; j++){
                park[j][i].type = data[j];
            }
        }
    }

    else{
        for(int i = 0; i < H; i++){
            string data;
            cin >> data;
            for (int j = 0; j < W; j++){
                park[j][i].type = data[j];
            }
        }
    }

    return park;
}

void printPark(Cell ** park){
    for (int i = 0; i < H; i ++){
        for (int j = 0; j < W; j ++){
            cout << park[j][i].type << " ";
        }
        cout << endl;
    }
}

int countNodes(Cell ** park){
    int counter = 0;
    for (int i = 0; i < H; i ++){
        for (int j = 0; j < W; j ++){
            if ( park[j][i].type != "."[0] ) counter ++;
        }
    }
    return counter;
}

Cell ** fillPark(Cell ** park){
    int counter = 0;
    for (int i = 0; i < H; i ++){
        for (int j = 0; j < W; j ++){
            if (park[j][i].type != "."[0]){
                park[j][i].counter = counter;
                //cout << counter << " ";
                counter++;
            }
            else{
                park[j][i].counter = -1;
                //cout << ".";
            }
        }
        //cout << endl;
    }
    return park;
}

struct Node{
int x;
int y;
int nodes[4];
int ill;
int taken;
int boy;
};

struct Graph{
Node * node;
int result;
};

Node * fillNode(Node * node, int nodesNumber ){

    for (int i = 0; i < nodesNumber; i++){
        node[i].nodes[0] = -1;
        node[i].nodes[1] = -1;
        node[i].nodes[2] = -1;
        node[i].nodes[3] = -1;
        node[i].ill = -1;
        node[i].taken = -1;
        node[i].boy = 0;
    }
    return node;
}

Node * convertToGraph(Cell ** park){
    int nodesNumber = countNodes(park);
    Node * node = new Node[nodesNumber];
    node = fillNode(node, nodesNumber);

    park = fillPark(park);
    int counter = 0;
    for (int i = 0; i < H; i ++){
        for (int j = 0; j < W; j ++){
            switch(park[j][i].type){
                case "+"[0]:
                    //intersection
                    if (j > 0 && (park[j-1][i].type == "+"[0] || park[j-1][i].type == "-"[0] ))
                        node[counter].nodes[0] = park[j-1][i].counter;
                    if (j < W-1 && (park[j+1][i].type == "+"[0] || park[j+1][i].type == "-"[0] ))
                        node[counter].nodes[1] = park[j+1][i].counter;

                    if (i > 0 && (park[j][i-1].type == "+"[0] || park[j][i-1].type == "|"[0] ))
                        node[counter].nodes[2] = park[j][i-1].counter;
                    if (i < H-1 && (park[j][i+1].type == "+"[0] || park[j][i+1].type == "|"[0] ))
                        node[counter].nodes[3] = park[j][i+1].counter;
                    node[counter].x = j;
                    node[counter].y = i;
                    counter++;

                    break;
                case "-"[0]:
                    //horizontal road
                    if (j > 0 && (park[j-1][i].type == "+"[0] || park[j-1][i].type == "-"[0] ))
                        node[counter].nodes[0] = park[j-1][i].counter;
                    if (j < W-1 && (park[j+1][i].type == "+"[0] || park[j+1][i].type == "-"[0] ))
                        node[counter].nodes[1] = park[j+1][i].counter;
                    node[counter].x = j;
                    node[counter].y = i;
                    counter++;

                    break;
                case "|"[0]:
                    //vertical road
                    if (i > 0 && (park[j][i-1].type == "+"[0] || park[j][i-1].type == "|"[0] ))
                        node[counter].nodes[0] = park[j][i-1].counter;
                    if (i < H-1 && (park[j][i+1].type == "+"[0] || park[j][i+1].type == "|"[0] ))
                        node[counter].nodes[1] = park[j][i+1].counter;
                    node[counter].x = j;
                    node[counter].y = i;
                    counter++;
                    break;
            }

        }

    }

    return node;
}

Node * printGraph(Node * node, int nodesNumber){
	cout << endl;
    for (int i = 0; i < nodesNumber; i++){
        cout << "node " << i << ": ";
        for (int j = 0; j < 4; j++){
            if (node[i].nodes[j] >=0 ){
                cout << node[i].nodes[j] << " ";
            }
        }
        cout << endl;
    }
	cout << endl;
}

Node * printGraphWithBoys(Node * node, int nodesNumber){
    cout << endl;
    for (int i = 0; i < nodesNumber; i++)
        cout << "node " << i << ": " << node[i].boy << endl;
    cout << endl;
}

Node * printGraphAllData(Node * node, int nodesNumber){
    cout << endl;
    for (int i = 0; i < nodesNumber; i++)
        cout << "node " << i << ": " << "ill: " << node[i].ill << " taken: " << node[i].taken << " boy: " << node[i].boy << endl;
    cout << endl;

}

Node * printSolution(Node * node, int nodesNumber){


        int counter = 0;
        for(int i = 0; i < nodesNumber; i++){
            if (node[i].boy == 1){
                cout << node[i].x << " " << node[i].y << endl;
                counter ++;
            }
        }
        exit(0);
}
Node * markAsIll(Node * node, int currentPosition, int sourcePosition, int l){
    node[currentPosition].ill++;
    if(l <= 0) return node;

    for(int i = 0; i < 4; i++){
        if (node[currentPosition].nodes[i] != -1){
            int nextPosition = node[currentPosition].nodes[i];
            if(sourcePosition != nextPosition)
                node = markAsIll(node,nextPosition,currentPosition,l-1);
        }
    }
    return node;
}

Node * unmarkAsIll(Node * node, int currentPosition, int sourcePosition, int l){
    node[currentPosition].ill--;
    if(l <= 0) return node;

    for(int i = 0; i < 4; i++){
        if (node[currentPosition].nodes[i] != -1){
            int nextPosition = node[currentPosition].nodes[i];
            if(sourcePosition != nextPosition)
                node = unmarkAsIll(node,nextPosition,currentPosition,l-1);
        }
    }
    return node;
}

Node * markAsIllAndDelete(Node * node, int currentPosition, int sourcePosition, int l){
    node[currentPosition].ill++;
    if (node[currentPosition].boy == 1 && currentPosition != sourcePosition){
        node[currentPosition].boy = 0;
        node[currentPosition].taken = -1;
        node = unmarkAsIll(node, currentPosition, currentPosition, L);
    }
    if(l <= 0) return node;

    for(int i = 0; i < 4; i++){
        if (node[currentPosition].nodes[i] != -1){
            int nextPosition = node[currentPosition].nodes[i];
            if(sourcePosition != nextPosition)
                node = markAsIllAndDelete(node,nextPosition,currentPosition,l-1);
        }
    }
    return node;
}


Graph solveGraph(Graph graph,int nodesNumber, int boys){
    for (int i = 0; i < nodesNumber; i++){
        if (graph.node[i].ill == -1 && graph.node[i].taken == -1){

            graph.node[i].taken = 1;
            graph.node[i].boy = 1;

            graph.node = markAsIll(graph.node,i,i,L);

            return solveGraph(graph, nodesNumber, boys+1);

        }
    }
    graph.result = boys;
    return graph;
}

Graph createNewMap(Node * dontTouch,int nodesNumber, int x){

    Graph graph;
    graph.node = new Node[nodesNumber];
    for (int i = 0; i < nodesNumber; i++){
        graph.node[i] = dontTouch[i];
    }
    int randSize = W/2;


    for (int i = 0; i < randSize; i++){
        int counter = 0;
        while (true){
            int randChoice = (x*x*i+i+counter)%nodesNumber;
            if (graph.node[randChoice].ill == -1 && graph.node[randChoice].taken == -1){
                graph.node[randChoice].taken = 1;
                graph.node[randChoice].boy = 1;
                graph.node = markAsIll(graph.node,randChoice,randChoice,L);

                break;
            }

            counter ++;
        }
    }


    Graph a = solveGraph(graph, nodesNumber, randSize);

    return a;

}

Graph inheritGens(Graph child, Graph graph2, int nodesNumber, int indexToInherit, int sourcePosition, int lengthToInherit){
    if (child.node[indexToInherit].boy == graph2.node[indexToInherit].boy && lengthToInherit <= 0) return child;

    if (child.node[indexToInherit].boy == 1 && graph2.node[indexToInherit].boy == 0){
            child.node[indexToInherit].taken = -1;
            child.node[indexToInherit].boy = 0;
            child.node = unmarkAsIll(child.node, indexToInherit, indexToInherit, L);
        }
    if (child.node[indexToInherit].boy == 0 && graph2.node[indexToInherit].boy == 1){

            child.node[indexToInherit].taken = 1;
            child.node[indexToInherit].boy = 1;
            child.node = markAsIllAndDelete(child.node, indexToInherit, indexToInherit, L);
        }


    if(lengthToInherit <= 0){
            return child;
    }

    for(int i = 0; i < 4; i++){

        if (child.node[indexToInherit].nodes[i] != -1){
            int nextPosition = child.node[indexToInherit].nodes[i];

            if(sourcePosition != nextPosition){

                child = inheritGens(child, graph2, nodesNumber,nextPosition, indexToInherit, lengthToInherit - 1);

            }
        }
    }

    return child;
}

Graph geneticCrossbreeding (Graph graph1, Graph graph2, int nodesNumber, int indexToInherit){


    int lengthToInherit = pow(W*H,0.5)/3;
    Graph child;
    child.node = new Node[nodesNumber];
    for (int i = 0; i < nodesNumber; i++){
        child.node[i] = graph1.node[i];
    }


    child = inheritGens(child, graph2, nodesNumber, indexToInherit,indexToInherit , lengthToInherit);

    int result = 0;
    for (int i = 0; i < nodesNumber; i++){

        if (child.node[i].ill == -1 && child.node[i].taken == -1){
            child.node[i].taken = 1;
            child.node[i].boy = 1;
            child.node = markAsIll(child.node,i,i,L);
        }

        if (child.node[i].boy == 1) result++;
    }

    child.result = result;

    return child;
}
void solveGraph(Node * node,int nodesNumber){
    int size = 10000;

    std::vector<Graph> array(size);

    for(int i=0; i<size; ++i){
        array[i] = createNewMap(node, nodesNumber, i);
        if (array[i].result >= K) printSolution(array[i].node, nodesNumber);
    }


    int counter = 0;
    while (true){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){


                int pseudoRand = ((i*j+counter)^j) % nodesNumber;

                Graph child = geneticCrossbreeding(array[i], array[j], nodesNumber, pseudoRand);

                if (child.result >= K) printSolution(child.node, nodesNumber);

                int theWorst = 0;
                for (int k = 0; k < size; k++){
                    if (array[k].result < array[theWorst].result)
                        theWorst = k;
                }

                int theBest = 0;
                for (int k = 0; k < size; k++){
                    if (array[k].result > array[theBest].result)
                        theBest = k;

                }


                if (counter % 10000 == 0)
                cout << counter/1000 << " tys best: " << theBest << " result: " << array[theBest].result << " the worst: " << array[theWorst].result << endl;


                if (array[theWorst].result <= child.result){
                    delete [] array[theWorst].node;
                    array[theWorst] = child;

                }
				else{
                    delete [] child.node;
                }

                counter ++;

            }
        }
    }
}


int main()
{
	//Speed up cout and cin
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
	
    boysCounter = 0;
    Cell ** park;
    park = readData(park, false);
    Node * node = convertToGraph(park);
    int nodesNumber = countNodes(park);

    solveGraph(node,nodesNumber);


}
