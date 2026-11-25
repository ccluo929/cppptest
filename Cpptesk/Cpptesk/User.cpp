#include "User.h"
#include "Session.h"   // dataPath()
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <map>

// 按分隔符切分一行文本
static vector<string> splitLine(const string& s, char sep)
{
    vector<string> out;
    string item;
    istringstream iss(s);
    while (getline(iss, item, sep))
        out.push_back(item);
    return out;
}

void User::signin() {
    cout << "请输入你的账号(未注册自动注册)";
    cin >> name;
    cout << "请输入你的密码";
    cin >> password;
}

const string& User::getName() const {
    return name;
}

const string& User::getPassword() const {
    return password;
}

// 追加写 data/users.txt：一行一个账号（账号|密码）
void User::saveToFile()
{
    ofstream fout(dataPath("users.txt"), ios::app);   // app：追加
    if (!fout)
    {
        cout << "用户信息保存失败（data 文件夹建不出来，或没有写入权限）\n";
        return;
    }
    fout << name << '|' << password << '\n';
    cout << "账号信息已写入 data\\users.txt\n";
}

//void User::control() {
//        cout << "开始练习->输入一";
//        cout << "检查回看题目->输入二";
//        cout << "退出练习->输入三";
//    }
// 读 data/questions.txt，把本账号的记录按“第几次”分组还原成 history：
// 同序号的多行属于同一次练习，map<int, Session> 会自动按序号排好。
void User::loadHistory()
{
    history.clear();   // 先清空，避免重复累加

    ifstream fin(dataPath("questions.txt"));
    if (!fin) return;   // 没有文件 = 还没做过题

    string line;
    map<int, Session> byNo;   // 序号 → 那一次练习

    while (getline(fin, line))
    {
        if (line.empty()) continue;

        vector<string> f = splitLine(line, '|');
        if (f.size() < 9) continue;   // 坏行跳过
        if (f[0] != name) continue;   // 别人的记录跳过

        int no = atoi(f[1].c_str());   // 第几次

        // 第一次遇到该序号时，map 自动建空 Session
        Session& s = byNo[no];
        s.no = no;

        QuestionRecord r;
        r.typeName = f[2];
        r.info = f[3];
        r.rightPeri = atof(f[4].c_str());
        r.rightArea = atof(f[5].c_str());
        r.userPeri = atof(f[6].c_str());
        r.userArea = atof(f[7].c_str());
        r.scoreThis = atof(f[8].c_str());

        s.recordList.push_back(r);
        s.qsnum = (int)s.recordList.size();   // 题数 = 组内行数
        s.score += r.scoreThis;   // 总分累加
    }

    // 已按序号排好，依次放进 history
    for (map<int, Session>::iterator it = byNo.begin(); it != byNo.end(); ++it)
        history.push_back(it->second);
}

// 先总览，再逐次逐题
void User::showHistory() const
{
    if (history.empty())
    {
        cout << "\n（还没有历史记录，做完一轮题目后就会有）\n";
        return;
    }

    cout << "\n========= 我的历史记录 =========\n";
    cout << "账号：" << name << "\n";
    cout << "共练习 " << history.size() << " 次，做题 " << totalQuestions() << " 道，"
         << "总得分 " << fixed << setprecision(2) << totalScore()
         << " / " << 100.0 * (double)history.size()
         << "，正确率 " << fixed << setprecision(2) << accuracy() * 100.0 << "%\n";

    for (int i = 0; i < (int)history.size(); ++i)
    {
        const Session& s = history[i];
        cout << "\n--- 第 " << s.no << " 次  "
             << s.qsnum << " 题  得分 "
             << fixed << setprecision(2) << s.score << " ---\n";

        for (int j = 0; j < (int)s.recordList.size(); ++j)
        {
            const QuestionRecord& r = s.recordList[j];

            // 容差与 TQB 的 eps 一致
            bool peri_ok = fabs(r.userPeri - r.rightPeri) < 0.01;
            bool area_ok = fabs(r.userArea - r.rightArea) < 0.01;

            cout << "  [" << j + 1 << "] " << r.typeName << "  " << r.info << "\n";
            cout << "      正确：周长 " << fixed << setprecision(2) << r.rightPeri
                 << "  面积 " << r.rightArea << "\n";
            cout << "      你的：周长 " << r.userPeri << (peri_ok ? " √" : " ×")
                 << "  面积 " << r.userArea << (area_ok ? " √" : " ×") << "\n";
        }
    }
}

// 累计做题数
int User::totalQuestions() const
{
    int n = 0;
    for (int i = 0; i < (int)history.size(); ++i)
        n += history[i].qsnum;
    return n;
}

// 累计得分
double User::totalScore() const
{
    double s = 0.0;
    for (int i = 0; i < (int)history.size(); ++i)
        s += history[i].score;
    return s;
}

// 正确率 0~1 = 总得分 / (100 × 练习次数)
double User::accuracy() const
{
    if (history.empty()) return 0.0;
    return totalScore() / (100.0 * (double)history.size());
}
