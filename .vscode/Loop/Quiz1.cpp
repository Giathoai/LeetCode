#include <iostream>
#include<string.h>


using namespace std;
// Hàm tính tổng các phần tử trong mảng bằng đệ quy
int recursiveSum(int arr[], int size) {
    // Trường hợp cơ sở: Nếu mảng không còn phần tử nào hoặc chỉ có một phần tử
    if (size == 0) {
        return 0;
    } else if (size == 1) {
        return arr[0];
    } else {
        cout << arr[0] << endl;
        // Gọi đệ quy: Tổng của phần tử đầu tiên cộng với tổng của các phần tử còn lại
        return arr[0] + recursiveSum(arr + 1, size - 1);
    }
}

void BF(int graph[20][20], int num_vertices, char start_vertex, int BFValue[], int BFPrev[])
{

    int copyArr[20];
    const int INF = 1000000;

    for (int i = 0; i < num_vertices; i++)
    {
        if (BFValue[i] == -1)
        {
            BFValue[i] = INF;
        }
    }
    BFValue[start_vertex - 'A'] = 0;

    for (int i = 0; i < num_vertices; i++)
    {
        copyArr[i] = BFValue[i];
    }

    int min = INF;

        for (int v = 0; v < num_vertices; v++)
        {
            for (int u = 0; u < num_vertices; u++)
            {
                if (copyArr[u] + graph[u][v] < BFValue[v])
                {
                    min = copyArr[u] + graph[u][v];
                    BFPrev[v] = u;
                }
            }
            if (min == INF)
                continue;
            else
            {
                BFValue[v] = min;
            }

            min = INF;
        }
    
}
    //Copy một mảng khác của value_array: chẳng hạn Copy_Array[20];
    //Sao chép giá trị từ Value Array qua Copy_Array
    //Duyệt theo đỉnh đến
    /*
        int Min = 100000000; biến này để lưu và so sánh min trong khi duyệt thôi
        for (int v = 0; v<n;v++) v là đỉnh đến
        {
            for (int u = 0; u <n;u++) u là đỉnh xuất phát
            {
                if (Copy_Array[u] + graph[u][v] < value_array[v] )
                {
                    min = Copy_Array[u] + graph[u][v];
                    prev_array[v] = u;
                }
            }
            Duyệt xong cho đỉnh v rồi đi kiểm tra 
            if (min == 100000000) continue;
            else 
            {
                value_array[v] = min;
            }
            set lại min cho hàm
            min = 100000000;
        }
    
    */

void process(const char *name, char *outstr) {

    int n=strlen(name);
    int i = 0;
    int j = 0;
        while(name[j] != '\0'){
        if(name[j]>='a' && name[j]<='z' || name[j]>='A' && name[j]<='Z' || name[j] == ' '){
         outstr[i] =  name[j];
         i++;
        }
         j++;
         
    }
    if(outstr[i-1] == ' ' && outstr[i] != 'a' && outstr[i] != 'z')
         outstr[i-1] = '\0';
    if (n> 0 && outstr[n-1] == ' ') {
        outstr[n-1] = '\0';
    }
    
    if(outstr[0]>='a' && outstr[0]<='z')
        outstr[0]-=32;    
    i = 1;
    while(outstr[i]!='\0'){
        if(outstr[i-1] == ' ' && outstr[i]>='a' && outstr[i]<='z')
        outstr[i]-=32;
        if(outstr[i-1] != ' ' && outstr[i]>='A' && outstr[i]<='Z')
        outstr[i]+=32;
        i++;
    }


}

int main() {
const int MAX_SIZE = 100;
char str[] = "doAn VAN *(()hau @!#$" ;
char outstr[MAX_SIZE];
process(str, outstr);
cout << outstr;
    return 0;
}