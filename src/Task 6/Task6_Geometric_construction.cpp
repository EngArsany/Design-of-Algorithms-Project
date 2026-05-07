#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    pair<int, int> current_point ;
    vector<pair<int, int>> points;
    cout << "Enter the value of the grid size: ";
    int n;
    cin >> n;
    int lines=2*n-6;
    cout<<lines<<endl;
    if(n==3)
    {
        current_point=make_pair(0, 0);
        points.push_back(current_point);
        cout<<"start at point: (0, 0)"<<endl;
        current_point.first=current_point.first+2;
        current_point.second=current_point.second+2;
        cout<<"Move 2 units diagonally down right"<<endl;
        points.push_back(current_point);
        current_point.first=current_point.first-3;
        current_point.second=current_point.second;
        cout<<"Move 3 units up (outside the box)"<<endl;
        points.push_back(current_point);
        current_point.first=current_point.first+3;
        current_point.second=current_point.second-3;
        cout<<"Move 3 units diagonally down left (outside the box)"<<endl;
        points.push_back(current_point);
        current_point.first=current_point.first;
        current_point.second=current_point.second+2;
        cout<<"Move 2 units to the right"<<endl;
        points.push_back(current_point);
    }
    else if(n%2)
    {
        current_point=make_pair(0, 0);
        points.push_back(current_point);
        cout<<"start at point: (0, 0)"<<endl;

        int conter=0;
        for(int i=0; i<lines-1; i++)
        {
            if(i%4==0)
            {
                current_point.first=current_point.first;
                current_point.second=current_point.second+n-1-conter;
                cout<<"Move "<<n-1-conter<<" units to the right"<<endl;
                points.push_back(current_point);
                if(conter>0)
                {
                    conter++;
                }
            }
            else if(i%4==1)
            {
                current_point.second=current_point.second;
                current_point.first=current_point.first+n-1-conter;
                cout<<"Move "<<n-1-conter<<" units down"<<endl;
                points.push_back(current_point);
            }
            else if(i%4==2)
            {
                current_point.first=current_point.first;
                current_point.second=current_point.second-n+1+conter;
                cout<<"Move "<<n-1-conter<<" units to the left"<<endl;
                points.push_back(current_point);
                conter++;
            }
            else
            {
                current_point.second=current_point.second;
                current_point.first=current_point.first-n+1+conter;
                cout<<"Move "<<n-1-conter<<" units up"<<endl;
                points.push_back(current_point);
            }
        }
        current_point.first=current_point.first-4;
        cout<<"Move 4 units up"<<endl;
        points.push_back(current_point);

        current_point.first=current_point.first+3;
        current_point.second=current_point.second+3;
        cout<<"Move 3 units diagonally down right"<<endl;
        points.push_back(current_point);
        current_point.first=current_point.first-3;
        current_point.second=current_point.second;
        cout<<"Move 3 units up"<<endl;
        points.push_back(current_point);
        current_point.first=current_point.first+3;
        current_point.second=current_point.second-3;
        cout<<"Move 3 units diagonally down left"<<endl;
        points.push_back(current_point);
        current_point.first=current_point.first;
        current_point.second=current_point.second+2;
        cout<<"Move 2 units to the right"<<endl;
        points.push_back(current_point);
    }

    else
    {
        current_point=make_pair(n-1, n-1);
        cout<<"start at point: ("<<n-1<<", "<<n-1<<")"<<endl;
        points.push_back(current_point);

        int conter=0;
        for(int i=0; i<lines-1; i++)
        {
            if(i%4==0)
            {
                current_point.first=current_point.first-n+1+conter;
                current_point.second=current_point.second;
                cout<<"Move "<<n-1-conter<<" units up"<<endl;
                points.push_back(current_point);
                if(conter>0)
                {
                    conter++;
                }
            }
            else if(i%4==1)
            {
                current_point.second=current_point.second-n+1+conter;
                current_point.first=current_point.first;
                cout<<"Move "<<n-1-conter<<" units to the left"<<endl;
                points.push_back(current_point);
            }
            else if(i%4==2)
            {
                current_point.first=current_point.first+n-1-conter;
                current_point.second=current_point.second;
                cout<<"Move "<<n-1-conter<<" units down"<<endl;
                points.push_back(current_point);
                conter++;
            }
            else
            {
                current_point.second=current_point.second+n-1-conter;
                current_point.first=current_point.first;
                cout<<"Move "<<n-1-conter<<" units to the right"<<endl;
                points.push_back(current_point);
            }
        }
        current_point.second=current_point.second-4;
        cout<<"Move 4 units to the left"<<endl;
        points.push_back(current_point);

        current_point.first=current_point.first+3;
        current_point.second=current_point.second+3;
        cout<<"Move 3 units diagonally down right"<<endl;
        points.push_back(current_point);
        current_point.first=current_point.first-3;
        current_point.second=current_point.second;
        cout<<"Move 3 units up"<<endl;
        points.push_back(current_point);
        current_point.first=current_point.first+3;
        current_point.second=current_point.second-3;
        cout<<"Move 3 units diagonally down left"<<endl;
        points.push_back(current_point);
        current_point.first=current_point.first;
        current_point.second=current_point.second+2;
        cout<<"Move 2 units to the right"<<endl;
        points.push_back(current_point);
    }

    cout << "Final order of points: ";
    for (const auto& point : points) {
        cout << "(" << point.first << ", " << point.second << ") ";
    }
    cout << endl;
    return 0;
}
