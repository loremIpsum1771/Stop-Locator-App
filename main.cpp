#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <fstream>
#include <list>
#include <queue>
#include <algorithm>
#include<sstream>
#include <cstring>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ctime"
#include <iomanip>
#include <functional>
using namespace std;

//Extra Credit #5
class trainStopData{
public:
	trainStopData(const string& stopid, const string& stopname, double stoplat, double stoplong) :
    stop_id(stopid), stop_name(stopname), stop_lat(stoplat), stop_long(stoplong){}
	trainStopData() : stop_lat(0), stop_long(0){}
	void setStopId(string& idToAdd){
		stop_id = idToAdd;
	}
	void setStopName(string& nameToAdd){
		stop_name = nameToAdd;
	}
	void setStopLat(double latToAdd){
		stop_lat = latToAdd;
	}
	void setStopLon(double lonToAdd){
		stop_long = lonToAdd;
	}
	const string getStopId(){
		return stop_id;
	}
	const string  get_stop_name(){
		return stop_name;
	}
	double getStopLat(){
		return stop_lat;
	}
	double getStopLong(){
		return stop_long;
	}


class pred{
	bool predicate;
public:
	pred(bool aPred) :predicate(aPred){}
	operator bool() const{ return predicate; }
};
class isStopOnRoute{
	char route;
public:
	isStopOnRoute(char aRoute) :route(aRoute){}
	char operator() (trainStopData aStop) const{ return(aStop.getStopId()[0] == route); }
};
class isSubwayStop{
	string stopId;
public:
	isSubwayStop(string anId) :stopId(anId){}
	bool operator()(trainStopData aStop) const{ return(stopId == aStop.getStopId()); }
};
class isSubwayStopNearX{
	double longitude, lattitude, d;
public:
    double degrad(double d) {
        return d * M_PI / 180;
    }
    double haverdist(double lat1, double longit1, double lat2, double longit2)
    {
        double r = 6371;
        double dlat = degrad(lat2 - lat1);
        double dlongit = degrad(longit2 - longit1);
        double a = sin(dlat / 2)*sin(dlat / 2) +
        cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit / 2)*sin(dlongit / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        return r*c;
    }
	isSubwayStopNearX(double aLong, double aLat, double aD) : longitude(aLong), lattitude(aLat), d(aD){}
	bool operator()(trainStopData aStop) { return (haverdist(lattitude, longitude, aStop.getStopLat(), aStop.getStopLong()) <= d); }
};


class printTrainStopInfo{
public:
	void operator()(trainStopData aStop) const{
		cout << aStop.get_stop_name() << aStop.getStopId() << aStop.getStopLat(), aStop.getStopLong();
	}
};

template<class operation, class predicate, class iteration>
int perform_if(iteration itrStart, iteration itrEnd, predicate pred, operation op){
    
	int how_many = 0;
    
	while (itrStart != itrEnd){
		if (pred(*itrStart))
		{
			op(*itrStart);
			how_many++;
		}
        
		itrStart++;
	}
	if (how_many == 0){
		cout << "No elements satisfy Pred " << endl;
	}
	return how_many;
}
template <class ForwardItr, class Functor>
ForwardItr select_item(ForwardItr start, ForwardItr end, Functor pred){
	ForwardItr tmp_itr = end;
	while (start != end){
		if (pred(*start))
			tmp_itr = start;
		++start;
	}
	return tmp_itr;
}

class closest_stop {
public:
	closest_stop(double longitude, double latitude) :
		longitude(longitude), latitude(latitude), shortest_dist(numeric_limits<double>::max()){}
	double degrad(double d) {
		return d * M_PI / 180;
	}
	double haverdist(double lat1, double longit1, double lat2, double longit2)
	{
		double r = 6371;
		double dlat = degrad(lat2 - lat1);
		double dlongit = degrad(longit2 - longit1);
		double a = sin(dlat / 2)*sin(dlat / 2) +
			cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit / 2)*sin(dlongit / 2);
		double c = 2 * atan2(sqrt(a), sqrt(1 - a));
		return r*c;
	}
	bool operator()(trainStopData stop){
		double newDist = haverdist(latitude, longitude, stop.getStopLat(), stop.getStopLong());
		if (newDist<shortest_dist){
			shortest_dist = newDist;
			return true;
		}
		return false;
	}

private:
	double longitude;
	double latitude;
	double shortest_dist;
};
void tokenizer(char str[], vector<string>& tokens, const char delim[]) {
	tokens.clear();
	char* tok = strtok(str, delim);
	while (tok != NULL) {
		tokens.push_back(tok);
		tok = strtok(NULL, delim);
	}
}
//Code from Prof Lisa Hellerstein (very slightly modified)
// CS2134
//
// This is a bare-bones implementation of the single-source unweighted
// shortest paths algorithm
// It does not have nice classes.

// Assumption: The vertices of the graph are labeled from 0 to n - 1,
// where n is the number of vertices.

const int DEFAULT_VAL = -1;      // must be less than 0
typedef vector<list<int> > Graph;        // The graph is given in an adjacency list.
// Vertices are indexed from 0 to V-1
// The indices of the vertices adjacent to vertex i
// are in the list Graph[i].
// Graph can be directed or undirected.

struct vertexInf                    // Stores information for a vertex
{
	int dist;  // distance to vertex from the source
	int prev;  // previous node in BFS tree
};

void printpath(int j, vector<vertexInf> & vinfo,vector<string> intToStopVect)
{
	stack<int> t;
    
	int current = j;
	while (current != DEFAULT_VAL)
	{
		t.push(current);
		current = vinfo[current].prev;
	}
	while (!t.empty())
	{
		cout << intToStopVect[t.top()] << " ";
		t.pop();
	}
}
void printSpecificpath(int j, vector<vertexInf> & vinfo,vector<string> intToStopVect, string endPoint)
{
	stack<int> t;
    
	int current = j;
	while (current != DEFAULT_VAL)
	{
		t.push(current);
		current = vinfo[current].prev;
	}
	while (!t.empty())
	{
		cout << intToStopVect[t.top()] << " ";
		t.pop();
	}
}

// Breadth First Search
// The unweighted shortest path algorithm on the graph g, with vertex i as the source
// Prints the length (number of edges) of the shortest path from the source to every vertex
// in the graph

void shortestpaths(vector<list<int>> adjacent, int s, vector<string> intToStopVect)
{
	queue<int> q;             // q is the queue of vertex numbers
    
	if (s < 0 || s > adjacent.size() - 1)
	{
		cout << "Bad index" << endl;
		return;
	}
	vector<vertexInf> vertices(adjacent.size());               // stores BFS info for the vertices
	// info for vertex j is in position j
    
	for (int j = 0; j < vertices.size(); ++j)                 // Initialize distances and prev values
	{
		vertices[j].dist = DEFAULT_VAL; vertices[j].prev = DEFAULT_VAL;
	}
	vertices[s].dist = 0;
    
	q.push(s);
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (list<int>::const_iterator w = adjacent[v].begin(); w != adjacent[v].end(); w++)
		{
			if (vertices[*w].dist == DEFAULT_VAL)          // distance of *w from source not determined yet
			{
				vertices[*w].dist = vertices[v].dist + 1;
				vertices[*w].prev = v;
				q.push(*w);
			}
		}
	}
	for (int j = 0; j < vertices.size(); j++)        // print distances from source and paths
	{
		cout << "vertex " << intToStopVect[j] << endl;
		cout << "distance: " << vertices[j].dist << endl;
		cout << "shortest path: ";
		printpath(j, vertices,intToStopVect);
		cout << endl;
	}
}
void specificPath(vector<list<int>> adjacent, string startPoint, vector<string> intToStopVect, string endPoint)
{
	queue<int> q;             // q is the queue of vertex numbers
    
    int s =0;
    for(int i= 0; i < intToStopVect.size();i++){
        if(intToStopVect[i]==startPoint){
            s=i;
        }
    }
	if (s < 0 || s > adjacent.size() - 1)
	{
		cout << "Bad index" << endl;
		return;
	}
	vector<vertexInf> vertices(adjacent.size());               // stores BFS info for the vertices
	// info for vertex j is in position j
    
	for (int j = 0; j < vertices.size(); ++j)                 // Initialize distances and prev values
	{
		vertices[j].dist = DEFAULT_VAL; vertices[j].prev = DEFAULT_VAL;
	}
	vertices[s].dist = 0;
    
	q.push(s);
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (list<int>::const_iterator w = adjacent[v].begin(); w != adjacent[v].end(); w++)
		{
			if (vertices[*w].dist == DEFAULT_VAL)          // distance of *w from source not determined yet
			{
				vertices[*w].dist = vertices[v].dist + 1;
				vertices[*w].prev = v;
				q.push(*w);
			}
		}
	}
	for (int j = 0; j < vertices.size(); j++)        // print distances from source and paths
	{
        if(intToStopVect[j] == endPoint){
            cout << "Destination " << intToStopVect[j] << endl;
            cout << "distance: " << vertices[j].dist << endl;
            cout << "shortest path: ";
            printSpecificpath(j, vertices,intToStopVect,endPoint);
        }
    }
    cout << endl;
}
void menu(){
	vector<trainStopData> tVect;
	ifstream txtFile("MTA_train_stop_data.txt");
	if (!txtFile) { cerr << "File not found"; return; }
	string stopLine;
	getline(txtFile, stopLine);
	vector<string> intToStop;
	map<string, int> stopToInt;
	int i = 0;
	while (getline(txtFile, stopLine)) {
		// All just data processing here
		vector<string> stopData;
		char* charStopLine = new char[stopLine.size() + 1];
		strcpy(charStopLine, stopLine.c_str());
		char delim[] = ",";
		//Separate data by commas
		tokenizer(charStopLine, stopData, delim);
		//Convert the long/latitude to doubles
		double lat = atof(stopData[2].c_str());
		double lon = atof(stopData[3].c_str());
		//Add new stop to trainStops vector;
		tVect.push_back(trainStopData(stopData[0], stopData[1], lat, lon));
		intToStop.push_back(stopData[0]);
		stopToInt[stopData[0]] = i;
		i++;
		delete[] charStopLine;
	}

	vector<trainStopData>::iterator itrBegin = tVect.begin();
	vector<trainStopData>::iterator itrEnd = tVect.end();
	string userChoice;


	// Get transfer information
	// Note: If you only used the transfers.txt file, you may
	// have less stops than if you used both files
	txtFile.close();
	txtFile.open("transfers.txt");
	if (!txtFile) { cerr << "File not found"; return; }
	vector<list<int>> adjacent(i);
	getline(txtFile, stopLine);
	while (getline(txtFile, stopLine)) {
		// All just data processing here
		vector<string> stopData;
		char* charStopLine = new char[stopLine.size() + 1];
		strcpy(charStopLine, stopLine.c_str());
		char delim[] = ", ";
		// Separate data by commas
		tokenizer(charStopLine, stopData, delim);
		// Add transfer data to vectors
		// Also check for self-transfer case
		if (stopData[0] != stopData[1]) {
			adjacent[stopToInt[stopData[0]]].push_back(stopToInt[stopData[1]]);
		}
		delete[] charStopLine;
	}

	// Fill transfers based on adjacencies
	// Note: The method used here assumes that adjacent stops are listed together
	// in the adjacency vector... By reading from the MTA_train_stop_data file,
	// this is a safe assumption.
	for (size_t j = 0; j < adjacent.size(); j++) {
		// check if previous stop in vector is on the same train line
		// takes a look at character 0 of the stop, aka the train line
		if (j > 0 && intToStop[j][0] == intToStop[j - 1][0]) {
			adjacent[j].push_back(j - 1);
		}
		// check if following stop in vector is on the same train line
		if (j < adjacent.size() - 1 && intToStop[j][0] == intToStop[j + 1][0]) {
			adjacent[j].push_back(j + 1);
		}
	}
	while (userChoice != "quit"){
		cout << "a) Print out the information about all the train stops on a specific route?\nb)Print out the information about a specific train stop\nc)Print out all the train stops within a certain distance\nquit\nd)Print out the available transfers at a specific train stop\ne)Print transfers available at all stops\nf) Print outthe shortest path length from the current stop to every other stop\ng) Print out the shortest path between two stops\nh) Find the closest stop to current location and then print the shortest path between that stop and the next closest stop ";
		cin >> userChoice;
		cout << endl;

		if (userChoice == "a"){
			char aRoute;
			cout << "Enter a route" << endl;
			cin >> aRoute;
			isStopOnRoute istop(aRoute);
			printTrainStopInfo outputStop;
			perform_if(itrBegin, itrEnd, istop, outputStop);
			cout << endl;
		}
		else if (userChoice == "b"){
			string aStop;
			cout << "Enter a stop id" << endl;
			cin >> aStop;
			isSubwayStop istop(aStop);
			printTrainStopInfo outputStop;
			perform_if(itrBegin, itrEnd, istop, outputStop);
			cout << endl;
		}
		else if (userChoice == "c"){
			double lat, lon, dist;
			cout << "Enter a lattitude, a longitude, then a distance" << endl;
			cin >> lat >> lon >> dist;
			isSubwayStopNearX istop(lon, lat, dist);
			printTrainStopInfo outputStop;
			perform_if(itrBegin, itrEnd, istop, outputStop);
			cout << endl;
		}
		else if (userChoice == "d"){
			string stopID;
			int stopIdx = 0;
			cout << "Enter a stopID" << endl;
			cin >> stopID;
			for (int i = 0; i < intToStop.size(); i++){
				if (stopID == intToStop[i]){
					stopIdx = i;
				}
			}
			cout << " at stop: " << intToStop[stopIdx] << " transfer available to ";
			list<int>::iterator itr = adjacent[stopIdx].begin();
			while (itr != adjacent[stopIdx].end()) {
				cout << intToStop[*itr] << " , ";
				itr++;
			}
			cout << endl;
		}
		else if (userChoice == "e"){
			for (size_t j = 0; j < adjacent.size(); j++) {
				cout << " at stop: " << intToStop[j] << " transfer available to ";
				list<int>::iterator itr = adjacent[j].begin();
				while (itr != adjacent[j].end()) {
					cout << intToStop[*itr] << " , ";
					itr++;
				}
				cout << endl;
			}
		}
		else if (userChoice == "f"){
			string stopid;
			int stopIdx = 0;
			cout << "Enter a Stop Id" << endl;
			cin >> stopid;
			for (int i = 0; i < intToStop.size(); i++){
				if (stopid == intToStop[i]){
					stopIdx = i;
				}
			}
			shortestpaths(adjacent, stopIdx, intToStop);
		}
		else if (userChoice == "g"){
			string endPoint;
			string startPoint;
			cout << "enter an startpoint" << endl;
			cin >> startPoint;
			cout << "enter an endpoint" << endl;
			cin >> endPoint;
			specificPath(adjacent, startPoint, intToStop, endPoint);
		}
		else if (userChoice == "h"){
			double lat, lon, dist;
			cout << "Enter a lattitude, and a longitude" << endl;
			cin >> lat >> lon ;
			closest_stop cstop1(lon, lat);
			vector<trainStopData>::iterator closestStop1 = select_item(itrBegin, itrEnd, cstop1);
			closest_stop cstop2(closestStop1->getStopLong()	, closestStop1->getStopLat());
			vector<trainStopData>::iterator closestStop2 = select_item(itrBegin, itrEnd, cstop2);
			specificPath(adjacent, closestStop1->getStopId(), intToStop, closestStop2->getStopId());
			cout << endl;
		
	}

			
            
        }
        
    }
private:
	string stop_id;
	string stop_name;
	double stop_lat;
	double stop_long;
};

int main(){
    trainStopData aStop;
    aStop.menu();
	
	return 0;
    
}
