

// thuật toán tsm
// tạo 1 biến curent cost
// tạo 1 mảng xem đã đi qua chưa, tạo 1 mảng cập nhật liên tục cấu hình, tạo 1 mảng lưu ans 
// tsm:
// duyệt các đỉnh
// nếu đỉnh đó chưa đi thì cập nhật đỉnh đó vào phần tử cấu hình X[i] = j;
// current cost = current cost + c[i - 1][j]; nghĩ là đường đi từ đỉnh trước đó tới đỉnh hiện tại
// đánh giá cận current cost > best cost thì bỏ

void tsm(int i, int n, int G[][20], bool* visited, int* X, int current_cost, int& bestcost, int* best_path, int cmin, int start){
    for(int j = 0; j < n; j++){
        if(!visited[j] && G[X[i - 1]][j] > 0){
            X[i] = j;
            visited[j] = true;
            current_cost += G[X[i - 1]][j];
            if(i == n - 1){
                if(current_cost + G[X[n - 1]][start] < bestcost && G[X[n - 1]][start] > 0){
                    bestcost = current_cost + G[X[n - 1]][start];
                    for(int k = 0; k < n; k++){
                        best_path[k] = X[k];
                    }
                }
            }else {
                tsm(i + 1, n, G, visited, X, current_cost, bestcost, best_path, cmin, start);
            }
            visited[j] = false;
            current_cost -= G[X[i - 1]][j];
        }    
    }
}

string Traveling(int G[][20],int n,char start){
    bool visited[20];
    //memset(visited,false,sizeof(visited));
    for(int i = 0; i < n; i++){
        visited[i] = false;
    }
    int X[20];
    int starting = start - 'A';
    int current_cost = 0;
    int best_path[20];
    int bestcost = 2147483647;
    int cmin = 2147483647;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(G[i][j] < cmin){
                cmin = G[i][j];
            }
        }
    }
    visited[starting] = true;
    X[0] = starting;

    tsm(1, n, G, visited, X, current_cost, bestcost, best_path, cmin,starting);
    string ans = "";
    for(int i = 0; i < n; i++){
        ans += (char)(best_path[i] + 'A');
        ans += " ";
    }
    ans += start;
return ans;
}
