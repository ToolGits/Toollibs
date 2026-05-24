/*
    Toollibs - Input Simulation Module

    This file was adapted and improved from:
    VideoGame.cpp
    from: https://github.com/akshitagit/CPP

    Original project licensed under the MIT License.

    Modifications:
    - Refactored code structure
    - Improved variable naming
    - Removed goto usage
    - Cleaned control flow
 */

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    long long n, h;
    int position = 0;
    int holding = 0;

    int a[100000];
    string commands;

    cin >> n >> h;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cin.ignore();
    getline(cin, commands);

    int size = commands.length();

    for (int i = 0; i < size; i++) {

        switch (commands[i]) {

        case '1':
            position = max(position - 1, 0);
            break;

        case '2':
            position = min(position + 1, (int)n - 1);
            break;

        case '3':
            if (holding == 0 && a[position] > 0) {
                a[position]--;
                holding = 1;
            }
            break;

        case '4':
            if (holding == 1 && a[position] < h) {
                a[position]++;
                holding = 0;
            }
            break;

        case '0':
            i = size;
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    return 0;
}