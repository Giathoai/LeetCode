#include<iostream>

using namespace std;


bool palindromeRecursion(const string &str, int left, int right) {
    if (left >= right) {
        return true;
    }
    if (str[left] != str[right]) {
        return false;
    }
    return palindromeRecursion(str, left + 1, right - 1);
}


bool palindromeRecursion(string s)
{
    // BEGIN YOUR IMPLEMENTATION [1]
    return palindromeRecursion(s, 0, s.length() - 1);
    // END YOUR IMPLEMENTATION [1]
}

int main()
{
    //hiddenCheck();
    // BEGIN YOUR IMPLEMENTATION [2]
    string input;
    while(true){
        getline(cin, input);
        if (input[0] == '*') {
            break;
        }
        if(palindrome(input)) cout << "true" << " ";
        else cout << "false" << " ";
        if(palindromeRecursion(input)) cout << "true" << endl;
        else cout << "false" << endl;

    }
    // END YOUR IMPLEMENTATION [2]
    return 0;
}