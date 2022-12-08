#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <time.h>
#include <fstream>

using namespace std;

const string str = "_________________________";
const wstring drum[16] = {L"100", L"120",  L"140", L"150", L"160", L"180", L"200", L"220", L"240", L"250", L"260", L"280", L"300", L"+", L"переход хода"};
const wstring OutputDrum = L"НА БАРАБАНЕ";
 
struct question {

    string que, ans;

    question(string que, string ans)
    {
        this->que = que;
        this->ans = ans;
    }

};

vector <question> InputQuestionsFromTheTextFile()
{
    ifstream file("Questions.txt");
    
    if (!file.is_open()) {
        wcout << L"Ошибка открытия файла с вопросами!\n";
        exit(false);
    } 

    vector <question> Questions;
    while(!file.eof())
    {
        string line;
        getline(file, line);

        int PosOfDoublet = line.find(':');
        string que = line.substr(0, PosOfDoublet + 1);
        while(que[0] == ' ') que.erase(que.begin());
        while(que[que.size() - 1] == ' ') que.erase(que.end() - 1);

        string ans = line.substr(PosOfDoublet + 2, line.size() - PosOfDoublet - 1);
        while(ans[0] == ' ') ans.erase(ans.begin());
        while(ans[ans.size() - 1] == ' ') ans.erase(ans.end() - 1);

        Questions.push_back(question(que, ans));
    }
    
    file.close();

    return Questions;
}

void pause()
{
    cin.clear();
    while(cin.get() != '\n');
}

wstring SpinDrum()
{
    wstring Points = drum[rand() % 16];
    return Points;
}

void PlusOnDrum(vector <bool>& Letters, string& s, string& ans) {
    int i = 0;
}

void PointsOnDrum(vector <bool>& Letters, string& s, string& ans, vector <int>& Players) {

}

void Print(string que, string s, const vector <int> PlayersScore) 
{
    setlocale(LC_ALL, "Russian");

    cout << que << "    ";
    for(auto i: s) cout << i << ' ';
    cout << "\n";
    wcout << L"Баланс игроков:        1 игрок         2 игрок         3 игрок\n";
    cout << "                          " << PlayersScore[0] << "               " << PlayersScore[1] << "               " << PlayersScore[2] << "\n"; 
}

question ChoosingRandomQuestion(vector <question>& Questions)
{
    int NumOfQue = rand() % Questions.size();
    string que = Questions[NumOfQue].que;
    string ans = Questions[NumOfQue].ans;
    Questions.erase(Questions.begin() + NumOfQue); 

    return question(que, ans);
}

int main()
{
    srand((unsigned)time(NULL));
    setlocale(LC_ALL, "Russian");

    vector <question> Questions = InputQuestionsFromTheTextFile();
    question RoundQue = ChoosingRandomQuestion(Questions);
    string que = RoundQue.que, ans = RoundQue.ans;
    string s = str.substr(0, ans.size());
    vector <int> PlayersScore(3, 0);
    int CurPlayer = 0;
    Print(que, s, PlayersScore);
    vector <bool> Letters(26, false);

    while(true) {

        wstring Points = SpinDrum();
        wcout << L"Ход " << CurPlayer + 1 << L"-го игрока           " << OutputDrum << "               " << Points;
        
        if (Points == L"переход хода") {
            CurPlayer = (CurPlayer + 1) % 3;
            pause();
            continue;
        } else if (Points == L"+") {
            
        } else {
            continue;
        }

        pause();

    }
    
    return 0;
}