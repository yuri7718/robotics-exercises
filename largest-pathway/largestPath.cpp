#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct coord { int pos[2]; };

vector< vector<char> > matrix;  // stores the labyrinth schema from a txt file
vector< vector<int> > visited;  // stores the information about whether a cell is already visited
int n, m;   // n: number of rows, m: number of columns
vector<coord> p;    // vector that stores the current path
vector<coord> l;    // vector that stores the longest path

bool isValid(int i, int j)
{
    // visited[i][j] is 0 if the cell is not yet visited and 1 if the cell is already visited
    return i >= 0 && i < n && j >= 0 && j < m && matrix[i][j] == '.' && visited[i][j] == 0;
}

int dfs(int i, int j)
{
    coord position = {i,j};
    p.push_back(position);
    visited[i][j] = 1;  // mark the cell as visited

    if (isValid(i-1,j)) dfs(i-1,j);
    if (isValid(i,j+1)) dfs(i,j+1);
    if (isValid(i+1,j)) dfs(i+1,j);
    if (isValid(i,j-1)) dfs(i,j-1);

    visited[i][j] = 0;  // backtracking step

    if (p.size() > l.size()) l = p; // update the longest path

    p.pop_back();

    return 0;
}

int longestPath()
{
    visited.resize(n, vector<int>(m,0));

    for (int i=0; i<n; i++) {
        if (matrix[i][0] == '.')    dfs(i,0);
        if (matrix[i][m-1] == '.')  dfs(i,m-1);
    }
    for (int j=0; j<m; j++) {
        if (matrix[0][j] == '.')    dfs(0,j);
        if (matrix[n-1][j] == '.')  dfs(n-1,j);
    }
    
    // overwrite the holes with order
    for (int i=0; i<l.size(); i++) {
        coord tmp = l[i];
        matrix[tmp.pos[0]][tmp.pos[1]] = '0' + i;
    }
    return 0;
}


int main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Please pass command line arguments as follows: ./largestPath labyrinth.txt\n";
        exit(-1);
    }

    ifstream file(argv[1]);
    if (!file) {
        throw runtime_error("Error opening file");
    }

    int cols = -1;
    string content;

    while (file >> content) {
        vector<char> v(content.begin(), content.end());
        if (cols == -1) {
            cols = v.size();
        } else {
            if (cols != v.size()) {
                throw runtime_error("Columns do not have the same number of elements");
            }
        }
        matrix.push_back(v);
    }
    file.close();

    n = matrix.size();
    m = cols;

    longestPath();

    ofstream soln;
    string s(argv[1]);
    soln.open (s.substr(0,s.find("."))+"_soln.txt");

    soln << l.size() << "\n";
    for (int i=0; i<matrix.size(); i++) {
        for (int j=0; j<matrix[i].size(); j++) {
            soln << matrix[i][j];
        }
        soln << "\n";
    }
    soln.close();
    return 0;
}   