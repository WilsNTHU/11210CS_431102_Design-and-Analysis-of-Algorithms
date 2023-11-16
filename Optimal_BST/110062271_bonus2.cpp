#include <iostream>
#include <climits>
#include <vector>
#include <cstring>
#include <utility>
#include <string>

using namespace std;

class Node{
    public:
        Node(int k){
            char temp[20];
            int n = sprintf(temp, "k%d", k);
            this->id = string(temp);
            this->num = k;
            this->left = NULL;
            this->right = NULL;
        }
        Node *left;
        Node *right;
        string id;
        int num;
};

Node * construct_OBST(vector<vector<int>>& root, int i, int j){
    if(i > j) return NULL;
    else if(i == j){
        Node *node = new Node(i);
        return node;
    }
    else{
        Node *node = new Node(root[i][j]);
        node->left = construct_OBST(root, i, root[i][j] - 1);
        node->right = construct_OBST(root, root[i][j] + 1, j);
        return node;
    }
}

void traverse_OBST(Node *r, int depth){
    if(r && depth == 0){
        cout << r->id << " is the root" << endl;
    }
    if(r->left){
        cout << r->left->id << " is the left child of " << r->id << endl;
        traverse_OBST(r->left, depth + 1);
    }else{
        cout << "d" << r->num - 1 << " is the left child of " << r->id << endl;
    }
    if(r->right){
        cout << r->right->id << " is the rihgt child of " << r->id << endl;
        traverse_OBST(r->right, depth + 1);
    }
    else cout << "d" << r->num << " is the right child of " << r->id << endl;
    
    return;
}

pair<vector<vector<float>>, vector<vector<int>>> optimal_BST(vector<float>& p, vector<float>& q, int n){
    // auto e = new float[n+2][n+1];
    // auto w = new float[n+2][n+1];
    // auto root = new int[n+1][n+1];
    // my compiler doesn't allow me to declare an array with variable size.
   
    vector<vector<float>> e(n+2, vector<float>(n+1));
    vector<vector<float>> w(n+2, vector<float>(n+1));
    vector<vector<int>> root(n+1, vector<int>(n+1));

    for(int i=1; i<=n+1; i++){
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }

    for(int l=1; l<=n; l++){
        for(int i=1; i<=n-l+1; i++){
            int j = i+l-1;
            e[i][j] = (float)INT_MAX;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            for(int r=i; r<=j; r++){
                float t = e[i][r-1] + e[r+1][j] + w[i][j];
                if(t < e[i][j]){
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
    
    Node *r = construct_OBST(root, 1, n);
    traverse_OBST(r, 0);

    return make_pair(e, root);
}

int main(void){
    // this data is the one on the Introduction to Cormen 8e on Figure 14.9
    // vector<float> p = {0.00,0.15,0.10,0.05,0.10,0.20};
    // vector<float> q = {0.05,0.10,0.05,0.05,0.05,0.10};
    // pair<vector<vector<float>>, vector<vector<int>>> result = optimal_BST(p,q,5);
    // cout << "exepected search cost: " << result.first[1][5] << ", root: " << result.second[1][5] << endl;

    // this data is from the NTHU HW
    vector<float> p = {0.00,0.04,0.06,0.08,0.02,0.10,0.12,0.14};
    vector<float> q = {0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};
    pair<vector<vector<float>>, vector<vector<int>>> result = optimal_BST(p,q,7);
    cout << "exepected search cost: " << result.first[1][7] << ", root: " << result.second[1][7] << endl;


    // FOR TESTING PURPOSE
    // for(int i=1; i<=5; i++)
    //     for(int j=0; j<=5; j++){
    //         cout << "i = " << i << ", j = " << j << ", cost = " << result.first[i][j] << ", root = " << result.second[i][j] << endl;
    //     }


    return 0;
}