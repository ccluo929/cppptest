#pragma once
#include<string>
#include<iostream>
#include<vector>
#include "Session.h"
using namespace std;

class User
{
    private:
        string name;
        string password;
        vector<Session> history;
    public:
        User() = default;
        void signin();
        const string& getName() const;
        const string& getPassword() const;

        // 追加写 data/users.txt（账号|密码）
        void saveToFile();

        // 读本账号记录，按序号分组还原成 history
        void loadHistory();

        // 打印 history
        void showHistory() const;

        //void control();
        // 统计值都现算，不存字段
        int totalQuestions() const;     // 累计做题数
        double totalScore() const;      // 累计得分
        double accuracy() const;   // 正确率 0~1
};
