#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;

int W, H, L, K;
int boysCounter;
struct Doint{
    int type;
    int counter;
};

Doint ** readData(Doint ** park, bool readWay){

    fstream file ("in.txt",std::ios::in);

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
                firstLine[counter] = found; cout << firstLine[counter] << " ";
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



    park = new Doint*[W];
    for (int i = 0; i < W; i ++){
        park[i] = new Doint[H];
    }

    if (readWay == false){
        cout << endl;
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

void printPark(Doint ** park){
    for (int i = 0; i < H; i ++){
        for (int j = 0; j < W; j ++){
           // cout << park[j][i].type << " ";
        }
        cout << endl;
    }
}

int countNodes(Doint ** park){
    int counter = 0;
    for (int i = 0; i < H; i ++)
        for (int j = 0; j < W; j ++)
            if ( park[j][i].type != "."[0] ) counter ++;
    return counter;
}

Doint ** fillPark(Doint ** park){
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

Node * fillGraph(Doint ** park){
    int nodesNumber = countNodes(park);
    Node * node = new Node[nodesNumber];
    node = fillNode(node, nodesNumber);
    park = fillPark(park);
    int counter = 0;
    for (int i = 0; i < H; i ++){
        for (int j = 0; j < W; j ++){
            switch(park[j][i].type){
                case "+"[0]:
                    //cout << "plus" << endl;
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
                    //cout << "minus" << endl;
                    if (j > 0 && (park[j-1][i].type == "+"[0] || park[j-1][i].type == "-"[0] ))
                        node[counter].nodes[0] = park[j-1][i].counter;
                    if (j < W-1 && (park[j+1][i].type == "+"[0] || park[j+1][i].type == "-"[0] ))
                        node[counter].nodes[1] = park[j+1][i].counter;
                    node[counter].x = j;
                    node[counter].y = i;
                    counter++;

                    break;
                case "|"[0]:
                    //cout << "pipe" << endl;

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
    for (int i = 0; i < nodesNumber; i++){
        cout << "node " << i << ": ";
        for (int j = 0; j < 4; j++){
            if (node[i].nodes[j] >=0 ){
                cout << node[i].nodes[j] << " ";
            }
        }
        cout << endl;
    }
}

Node * printGraph2(Node * node, int nodesNumber){
    cout << endl;
    for (int i = 0; i < nodesNumber; i++)
        cout << "node " << i << ": " << node[i].boy << endl;
    cout << endl;

}

Node * printGraph3(Node * node, int nodesNumber){
    cout << endl;
    for (int i = 0; i < nodesNumber; i++)
        cout << "node " << i << ": " << "ill: " << node[i].ill << " taken: " << node[i].taken << " boy: " << node[i].boy << endl;
    cout << endl;

}


Node * markAsIll(Node * node, int positionHere, int positionFrom, int l){
    node[positionHere].ill++;
    if(l <= 0) return node;

    for(int i = 0; i < 4; i++){
        if (node[positionHere].nodes[i] != -1){
            int nextPosition = node[positionHere].nodes[i];
            if(positionFrom != nextPosition)
                node = markAsIll(node,nextPosition,positionHere,l-1);
        }
    }
    return node;
}

Node * unmarkAsIll(Node * node, int positionHere, int positionFrom, int l){
    node[positionHere].ill--;
    if(l <= 0) return node;

    for(int i = 0; i < 4; i++){
        if (node[positionHere].nodes[i] != -1){
            int nextPosition = node[positionHere].nodes[i];
            if(positionFrom != nextPosition)
                node = unmarkAsIll(node,nextPosition,positionHere,l-1);
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
    int randSize = 4;


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
           // printGraph3(graph.node, nodesNumber);
           // cout << randChoice << endl;
            counter ++;
        }
    }
    //printGraph3(graph.node, nodesNumber);
    Graph a = solveGraph(graph, nodesNumber, randSize);

    return a;

}

void solveGraph(Node * node,int nodesNumber){
    int size = 100;
    std::vector<Graph> array(size);
    for(int i=0; i<size; ++i){
        cout << "mapa: " << i << endl;
        array[i] = createNewMap(node, nodesNumber, i);
        printGraph3(array[i].node, nodesNumber);
        cout << "boys: " <<  array[i].result << endl;
    }

    while (true){
        for (int i = 0; i < nodesNumber; i++){
            for (int j = 0; j < nodesNumber; j++){
                //Graph child = combine(array[i], array[j]);
                //deleteTheWorst(array);
                //array.push_back(child);
            }
        }
    }


}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    boysCounter = 0;

    Doint ** park;
    park = readData(park, false);
    Node * node = fillGraph(park);
    int nodesNumber = countNodes(park);
    //cout << endl;
    //printGraph(node, nodesNumber);
    //solveGraph(node, nodesNumber, 0);
    solveGraph(node,nodesNumber);


}
