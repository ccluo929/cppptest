#pragma once
#include <string>
#include <vector>
#include <direct.h>
using namespace std;

inline string dataPath(const string& fileName)
{
    _mkdir("data");
    return "data/" + fileName;
}

// ---------- 练习题数据 ----------

// 一道题的作答记录
struct QuestionRecord
{
    string typeName;
    string info;
    double rightPeri = 0;
    double rightArea = 0;
    double userPeri = 0;
    double userArea = 0;
    double scoreThis = 0;
};

struct Session
{
    int no = 0;
    int qsnum = 0;
    double score = 0;
    vector<QuestionRecord> recordList;
};
