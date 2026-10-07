#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// ============================================================
// 三角形题目类 TriangleQuestion
// ============================================================
class TriangleQuestion {
private:
    int    id;             // 题目编号
    double a, b, c;        // 三条边长
    string correctAnswer;  // 正确答案
    string userAnswer;     // 用户答案
    bool   answered;       // 是否已作答
    bool   correct;        // 是否答对

public:
    // ---------- 构造 / 初始化 ----------
    TriangleQuestion() : id(0), a(0), b(0), c(0), answered(false), correct(false) {}

    TriangleQuestion(int id, double a, double b, double c)
        : id(id), a(a), b(b), c(c), answered(false), correct(false) {
        correctAnswer = computeCorrectAnswer();
    }

    void init(int id, double a, double b, double c) {
        this->id = id;
        this->a = a;
        this->b = b;
        this->c = c;
        this->answered = false;
        this->correct = false;
        this->userAnswer.clear();
        this->correctAnswer = computeCorrectAnswer();
    }

    // ---------- 修改数据成员 ----------
    void setSides(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->answered = false;
        this->correct = false;
        this->userAnswer.clear();
        this->correctAnswer = computeCorrectAnswer();
    }

    // ---------- 获取数据成员 ----------
    int    getId()            const { return id; }
    double getA()             const { return a; }
    double getB()             const { return b; }
    double getC()             const { return c; }
    string getCorrectAnswer() const { return correctAnswer; }
    string getUserAnswer()    const { return userAnswer; }
    bool   isAnswered()       const { return answered; }
    bool   isCorrect()        const { return correct; }

    // ---------- 判断是否为有效三角形 ----------
    bool isValidTriangle() const {
        return a > 0 && b > 0 && c > 0 &&
               a + b > c && a + c > b && b + c > a;
    }

    // ---------- 求周长 ----------
    double perimeter() const {
        return a + b + c;
    }

    // ---------- 求面积（海伦公式） ----------
    double area() const {
        if (!isValidTriangle()) return 0.0;
        double p = perimeter() / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    // ---------- 判断三角形类型 ----------
    string triangleType() const {
        if (!isValidTriangle()) return "不是三角形";

        const double eps = 1e-9;
        double x = a, y = b, z = c;
        // 排序，让 z 最大
        if (x > z) swap(x, z);
        if (y > z) swap(y, z);
        if (x > y) swap(x, y);

        bool right       = fabs(x * x + y * y - z * z) < eps;
        bool equilateral = fabs(a - b) < eps && fabs(b - c) < eps;
        bool isosceles   = fabs(a - b) < eps || fabs(b - c) < eps || fabs(a - c) < eps;

        if (equilateral)            return "等边三角形";
        if (right && isosceles)     return "等腰直角三角形";
        if (right)                  return "直角三角形";
        if (isosceles)              return "等腰三角形";
        return "普通三角形";
    }

    // ---------- 计算正确答案 ----------
    string computeCorrectAnswer() const {
        if (!isValidTriangle()) return "不是三角形";
        return triangleType();
    }

    // ---------- 设置用户答案并判断对错 ----------
    void setUserAnswer(const string& ans) {
        userAnswer = ans;
        answered   = true;
        correct    = (userAnswer == correctAnswer);
    }

    // ---------- 输出题目 ----------
    void displayQuestion() const {
        cout << "----------------------------------------" << endl;
        cout << "题目编号：" << id << endl;
        cout << "三条边长：" << a << ", " << b << ", " << c << endl;
        cout << "请输入该三角形的类型" << endl;
        cout << "（等边三角形 / 等腰三角形 / 直角三角形 / 等腰直角三角形 / 普通三角形 / 不是三角形）：";
    }

    // ---------- 输出完整信息 ----------
    void displayInfo() const {
        cout << "题目编号：" << id
             << " | 边长：" << a << ", " << b << ", " << c
             << " | 周长：" << perimeter()
             << " | 面积：" << fixed << setprecision(2) << area()
             << " | 类型：" << triangleType()
             << " | 正确答案：" << correctAnswer;
        if (answered) {
            cout << " | 你的答案：" << userAnswer
                 << " | 结果：" << (correct ? "正确" : "错误");
        } else {
            cout << " | 未作答";
        }
        cout << endl;
    }
};

// ============================================================
// 题库类 QuestionBank
// ============================================================
class QuestionBank {
private:
    string name;                         // 题库名称
    int    questionCount;                // 题目数量
    vector<TriangleQuestion> questions;  // 所有题目
    vector<bool>  scores;                // 每道题成绩（是否答对）
    int    answeredCount;                // 已作答题数
    int    correctCount;                 // 答对题数

public:
    // ---------- 构造 / 初始化 ----------
    QuestionBank(const string& name = "默认题库")
        : name(name), questionCount(0), answeredCount(0), correctCount(0) {}

    void init(const string& name) {
        this->name = name;
        questions.clear();
        scores.clear();
        questionCount = 0;
        answeredCount = 0;
        correctCount  = 0;
    }

    // ---------- 获取数据成员 ----------
    string getName()            const { return name; }
    int    getQuestionCount()   const { return questionCount; }
    int    getAnsweredCount()   const { return answeredCount; }
    int    getCorrectCount()    const { return correctCount; }

    // ---------- 计算平均分 ----------
    double getAverageScore() const {
        if (answeredCount == 0) return 0.0;
        return (double)correctCount / answeredCount * 100.0;
    }

    // ---------- 增加题目（手动输入） ----------
    bool addQuestion() {
        double a, b, c;
        cout << "请输入三角形的三条边长（用空格分隔）：";
        while (!(cin >> a >> b >> c)) {
            cout << "输入格式错误，请重新输入三条边长：";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        TriangleQuestion q;
        q.init(questionCount + 1, a, b, c);

        if (!q.isValidTriangle()) {
            cout << "× 这不是一个有效三角形，无法加入题库！" << endl;
            return false;
        }

        questions.push_back(q);
        scores.push_back(false);
        questionCount++;
        cout << "√ 题目添加成功！当前题库共有 " << questionCount << " 道题。" << endl;
        return true;
    }

    // ---------- 删除题目 ----------
    bool deleteQuestion(int id) {
        for (int i = 0; i < (int)questions.size(); i++) {
            if (questions[i].getId() == id) {
                // 如果该题已作答，需要同步更新统计
                if (questions[i].isAnswered()) {
                    answeredCount--;
                    if (questions[i].isCorrect()) correctCount--;
                }
                questions.erase(questions.begin() + i);
                scores.erase(scores.begin() + i);
                questionCount--;

                // 重新编号
                for (int j = 0; j < (int)questions.size(); j++) {
                    questions[j].init(j + 1,
                                      questions[j].getA(),
                                      questions[j].getB(),
                                      questions[j].getC());
                }
                cout << "√ 题目 " << id << " 已删除。" << endl;
                return true;
            }
        }
        cout << "× 未找到编号为 " << id << " 的题目。" << endl;
        return false;
    }

    // ---------- 查询所有题目 ----------
    void listQuestions() const {
        if (questionCount == 0) {
            cout << "题库为空。" << endl;
            return;
        }
        cout << "\n========== 题库：" << name << " ==========" << endl;
        for (const auto& q : questions) {
            q.displayInfo();
        }
        cout << "共 " << questionCount << " 道题。" << endl;
    }

    // ---------- 按编号答题 ----------
    void answerQuestion(int id) {
        if (questionCount == 0) {
            cout << "题库为空，无法答题。" << endl;
            return;
        }

        TriangleQuestion* target = nullptr;
        int index = -1;
        for (int i = 0; i < (int)questions.size(); i++) {
            if (questions[i].getId() == id) {
                target = &questions[i];
                index  = i;
                break;
            }
        }

        if (target == nullptr) {
            cout << "× 未找到编号为 " << id << " 的题目。" << endl;
            return;
        }

        if (target->isAnswered()) {
            cout << "该题已经作答过了。" << endl;
            target->displayInfo();
            return;
        }

        target->displayQuestion();
        string ans;
        cin >> ans;

        target->setUserAnswer(ans);
        answeredCount++;
        if (target->isCorrect()) {
            correctCount++;
            scores[index] = true;
            cout << "√ 回答正确！" << endl;
        } else {
            cout << "× 回答错误。正确答案是：" << target->getCorrectAnswer() << endl;
        }
        cout << "当前平均分：" << fixed << setprecision(2)
             << getAverageScore() << " 分" << endl;
    }

    // ---------- 随机答题（从未作答题目中抽取） ----------
    void answerRandomQuestion() {
        if (questionCount == 0) {
            cout << "题库为空，无法答题。" << endl;
            return;
        }

        vector<int> unanswered;
        for (const auto& q : questions) {
            if (!q.isAnswered()) unanswered.push_back(q.getId());
        }

        if (unanswered.empty()) {
            cout << "所有题目都已作答完毕！" << endl;
            return;
        }

        int idx = rand() % unanswered.size();
        answerQuestion(unanswered[idx]);
    }

    // ---------- 查看成绩 ----------
    void showScore() const {
        cout << "\n========== 成绩统计 ==========" << endl;
        cout << "题库名称　：" << name << endl;
        cout << "题目总数　：" << questionCount << endl;
        cout << "已作答题数：" << answeredCount << endl;
        cout << "答对题数　：" << correctCount << endl;
        cout << "平均分　　：" << fixed << setprecision(2)
             << getAverageScore() << " 分" << endl;

        if (answeredCount > 0) {
            cout << "\n详细答题情况：" << endl;
            for (const auto& q : questions) {
                if (q.isAnswered()) {
                    cout << "  题目 " << q.getId() << "："
                         << (q.isCorrect() ? "正确" : "错误")
                         << "（你的答案：" << q.getUserAnswer()
                         << "，正确答案：" << q.getCorrectAnswer() << "）" << endl;
                }
            }
        }
    }
};

// ============================================================
// 主函数：菜单交互
// ============================================================
int main() {
    srand((unsigned)time(nullptr));

    QuestionBank bank;
    string bankName;
    cout << "请输入题库名称：";
    cin >> bankName;
    bank.init(bankName);

    int choice;
    do {
        cout << "\n========== 三角形题库系统 ==========" << endl;
        cout << "1. 添加题目（手动输入三角形边长）" << endl;
        cout << "2. 删除题目" << endl;
        cout << "3. 查询所有题目" << endl;
        cout << "4. 按编号答题" << endl;
        cout << "5. 随机答题" << endl;
        cout << "6. 查看成绩与平均分" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择操作：";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "无效输入，请重新选择。" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            bank.addQuestion();
            break;
        case 2: {
            int id;
            cout << "请输入要删除的题目编号：";
            cin >> id;
            bank.deleteQuestion(id);
            break;
        }
        case 3:
            bank.listQuestions();
            break;
        case 4: {
            int id;
            cout << "请输入要作答的题目编号：";
            cin >> id;
            bank.answerQuestion(id);
            break;
        }
        case 5:
            bank.answerRandomQuestion();
            break;
        case 6:
            bank.showScore();
            break;
        case 0:
            cout << "感谢使用，再见！" << endl;
            break;
        default:
            cout << "无效选择，请重新输入。" << endl;
        }
    } while (choice != 0);

    return 0;
