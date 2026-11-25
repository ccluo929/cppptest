#include "TQB.h"
#include <sstream>
#include <cstdlib>


static string numText(double v)
{
    ostringstream oss;
    oss << setprecision(10) << v;
    return oss.str();
}

void TQB::start() {
    srand((unsigned int)time(nullptr));
    cout << "欢迎来到几何图形训练系统\n";

    int n = 0;
    while (true) {
        cout << "请输入你要训练多少道题（正整数）：";
        if (cin >> n && n > 0) break;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "输入无效，请重新输入。\n";
    }

    current = Session();
    current.qsnum = n;
    single_full = 100.0 / n;
    half_score = single_full / 2.0;
}

Shape* TQB::generate_question(string& typeName, string& info, double& rightPeri, double& rightArea)
{
    int type = rand() % 5;
    Shape* graph = nullptr;

    // 顺便把参数拼成字符串存进 info，回看时就知道题目长什么样
    if (type == 0)
    {
        circle* p = new circle();
        typeName = "圆";
        info = "半径=" + numText(p->getr());
        graph = p;
    }
    else if (type == 1)
    {
        four_square* p = new four_square();
        typeName = "正方形";
        info = "边长=" + numText(p->getside());
        graph = p;
    }
    else if (type == 2)
    {
        rectangle* p = new rectangle();
        typeName = "长方形";
        info = "长=" + numText(p->getlenth()) + ",宽=" + numText(p->getwidth());
        graph = p;
    }
    else if (type == 3)
    {
        trapezoid* p = new trapezoid();
        typeName = "梯形";
        info = "上底=" + numText(p->getupper_base())
             + ",下底=" + numText(p->getlower_base())
             + ",高=" + numText(p->getheight());
        graph = p;
    }
    else
    {
        Triangle* p = new Triangle();
        typeName = "三角形";
        info = "三边=" + numText(p->geta()) + "," + numText(p->getb()) + "," + numText(p->getc());
        graph = p;
    }

    graph->show();
    rightPeri = graph->perimeter();
    rightArea = graph->area();
    return graph;
}

//void TQB::control() {
//    cout << "开始练习->输入一";
//    cout << "退出练习并清空记录->输入二";
//    cout << "检查回看题目->输入三";
//}

void TQB::doing()
{
    for (int i = 0; i < current.qsnum; ++i)
    {
        cout << "\n---------- 第 " << i + 1 << " 题 ----------\n";
        string typeName;
        string info;
        double rightPeri, rightArea;
        Shape* graph = generate_question(typeName, info, rightPeri, rightArea);

        double userPeri, userArea;
        cout << "\n请输入周长：";
        cin >> userPeri;
        cout << "请输入面积：";
        cin >> userArea;

        double scoreThis = 0.0;
        bool peri_ok = fabs(userPeri - rightPeri) < eps;
        bool area_ok = fabs(userArea - rightArea) < eps;

        if (peri_ok)
        {
            scoreThis += half_score;
            cout << "周长正确，+" << fixed << setprecision(2) << half_score << "分\n";
        }
        else
        {
            cout << "周长错误，正确周长：" << fixed << setprecision(2) << rightPeri << endl;
        }
        if (area_ok)
        {
            scoreThis += half_score;
            cout << "面积正确，+" << fixed << setprecision(2) << half_score << "分\n";
        }
        else
        {
            cout << "面积错误，正确面积：" << fixed << setprecision(2) << rightArea << endl;
        }
        cout << "本题理论满分：" << fixed << setprecision(2) << single_full
            << "实际得分：" << fixed << setprecision(2) << scoreThis << endl;

        current.score += scoreThis;
        current.recordList.push_back({ typeName, info, rightPeri, rightArea, userPeri, userArea, scoreThis });
        delete graph;
        graph = nullptr;
    }
}

void TQB::end() {
    cout << "\n======== 刷题结束，成绩汇总 ========\n";
    cout << "你的总分（满分100）：" << fixed << setprecision(2) << current.score << endl;
}

// 追加写 data/questions.txt：一行一题，9 个字段用 | 分隔；同一次练习的“第几次”相同
void TQB::saveToFile(const string& userName)
{
    // 本次序号 = 该账号已有的最大序号 + 1
    int no = 1;
    {
        ifstream fin(dataPath("questions.txt"));
        string line;
        while (getline(fin, line))
        {
            size_t p1 = line.find('|');   // 账号之后
            if (p1 == string::npos) continue;
            size_t p2 = line.find('|', p1 + 1);   // 序号之后
            if (p2 == string::npos) continue;
            if (line.substr(0, p1) != userName) continue;   // 别人的记录跳过
            int v = atoi(line.substr(p1 + 1, p2 - p1 - 1).c_str());
            if (v >= no) no = v + 1;
        }
    }

    ofstream fout(dataPath("questions.txt"), ios::app);   // app：追加，不覆盖
    if (!fout)
    {
        cout << "题目记录保存失败（data 文件夹建不出来，或没有写入权限）\n";
        return;
    }

    fout << setprecision(10);   // 保留足够位数，读回来不失真

    for (int i = 0; i < (int)current.recordList.size(); ++i)
    {
        const QuestionRecord& r = current.recordList[i];
        fout << userName << '|' << no << '|' << r.typeName << '|' << r.info << '|'
             << r.rightPeri << '|' << r.rightArea << '|'
             << r.userPeri << '|' << r.userArea << '|'
             << r.scoreThis << '\n';
    }

    cout << "本次 " << current.recordList.size() << " 道题已写入 data\\questions.txt"
         << "（第 " << no << " 次）\n";
}

void TQB::revise() {
    cout << "\n是否查看答题记录？输入1查看，其他数字跳过：";
    int look;
    cin >> look;
    if (look == 1)
    {
        cout << "\n===== 答题记录回看 ====\n";
        double single = 100.0 / current.qsnum;

        for (int j = 0; j < current.recordList.size(); j++)
        {
            auto& r = current.recordList[j];
            cout << "第" << j + 1 << "题【" << r.typeName << "】\n";
            cout << "正确周长：" << r.rightPeri << "    你的答案：" << r.userPeri << "\n";
            cout << "正确面积：" << r.rightArea << "    你的答案：" << r.userArea << "\n";
            cout << "本题理论满分：" << fixed << setprecision(2) << single
                << "    本题实际得分：" << fixed << setprecision(2) << r.scoreThis << "\n\n";
        }
    }
}

const Session& TQB::getSession() const {
    return current;
}
