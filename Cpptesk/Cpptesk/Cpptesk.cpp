#include <iostream>
#include "circle.h"
#include "Squares.h"
#include "Triangle.h"
#include"TQB.h"
#include"User.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include<iomanip>
#include <string>
using namespace std;

int main() {
       
        User user;
        user.signin();
        user.saveToFile();
        cout << "\n1. 开始做题\n2. 查看历史记录和正确率\n3. 退出\n请输入你的选择：";
        int a;
        cin >> a;
        switch (a)
        {
        case 1:
        {
            TQB t;
            t.start();
            t.doing();
            t.end();
            t.saveToFile(user.getName());
            t.revise();
            break;
        }
        case 2:
            user.loadHistory();
            user.showHistory();
            break;
        case 3:
            return 0;
        default:
            cout << "没有这个选项。\n";
            break;
        }
        return 0;
}
