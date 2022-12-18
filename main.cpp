#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <Windows.h>
#include <map>
#include <time.h>
#include <fstream>

using namespace std;

const string str = "_________________________";
const wstring drum[15] = { L"100", L"120",  L"140", L"150", L"160", L"180", L"200", L"220", L"240", L"250", L"260", L"280", L"300", L"+", L"переход хода" };
const wstring OutputDrum = L"НА БАРАБАНЕ";
static map <wchar_t, bool> Letters;

struct question {

    string que, ans;

    question(string que, string ans)
    {
        this->que = que;
        this->ans = ans;
    }

};

void pause()
{
    cin.clear();
    while (cin.get() != '\n');
}

vector <question> InputQuestionsFromTheTextFile()
{
    ifstream file("Questions.txt");

    if (!file.is_open()) {
        wcout << L"Ошибка открытия файла с вопросами!\n";
        pause();
        exit(false);
    }

    vector <question> Questions;
    while (!file.eof())
    {
        string line;
        getline(file, line);

        int PosOfDoublet = line.find(':');
        string que = line.substr(0, PosOfDoublet + 1);
        while (que[0] == ' ') que.erase(que.begin());
        while (que[que.size() - 1] == ' ') que.erase(que.end() - 1);

        string ans = line.substr(PosOfDoublet + 2, line.size() - PosOfDoublet - 1);
        while (ans[0] == ' ') ans.erase(ans.begin());
        while (ans[ans.size() - 1] == ' ') ans.erase(ans.end() - 1);

        Questions.push_back(question(que, ans));
    }

    file.close();

    return Questions;
}

void Print(string que, string s, const vector <int> PlayersScore)
{
    cout << que << "    ";
    for (auto i : s) cout << i << ' ';
    cout << "\n";
    wcout << L"Баланс игроков:        1 игрок         2 игрок         3 игрок\n";
    cout << "                       " << PlayersScore[0] << "               " << PlayersScore[1] << "               " << PlayersScore[2] << "\n";
}

wstring SpinDrum()
{
    wstring Points = drum[rand() % 15];
    return Points;
}

void PlusOnDrum(string& que, string& s, string& ans, int& CurPlayer)
{
    cout << que << "    ";
    for (auto i : s) cout << i << ' ';
    cout << "\n";

    wcout << L"Выбирите номер буквы, которую хотите открыть:           ";
    int a;
    do {
        try
        {
            string test;
            getline(cin, test);
            if (test.size() >= 2) {
                while (test[0] == ' ') test.erase(test.begin());
                while (test.size() > 1 && test[test.size() - 1] == ' ') test.erase(test.end() - 1);
            }
            bool flag = false;
            for (int i = 0; i < test.size(); i++) {
                if (test[i] < '0' || test[i] > '9') {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                wcout << L"Вы ввели что-то непонятное, введите номер буквы еще раз            ";
                continue;
            }

            int myint = stoi(test);

            if (myint > 0 && myint <= ans.size()) {
                a = myint;
                break;
            }
            else {
                wcout << L"Вы ввели что-то непонятное, введите номер буквы еще раз            ";
                continue;
            }
        }
        catch (std::exception& e)
        {
            wcout << L"Вы ввели что-то непонятное, введите номер буквы еще раз            ";
            continue;
        }

    } while (true);

    if (s[a - 1] != '_' || Letters[ans[a - 1] - 64]) {
        wcout << L"Вы, конечно, умный! Такая буква уже открыта.\n";
        CurPlayer = (CurPlayer + 1) % 3;
    }
    else {
        wcout << L"Открыть букву под номером " << a << "\n";
        if (ans[a - 1] == int('Ё')) Letters[ans[a - 1] - 72] = true;
        else Letters[ans[a - 1] - 64] = true;
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i] == ans[a - 1]) {
                s[i] = ans[i];
            }
        }
        cout << que << "    ";
        for (auto i : s) cout << i << ' ';
        cout << "\n";
    }

}

void PointsOnDrum(string& que, string& s,
    string& ans, vector <int>& PlayersScore,
    int& CurPlayer, wstring Points) {

    char io = ' ';
    string u = "";
    bool flag = false;
    do {
        if (flag) wcout << L"Я не расслышал. Повторите еще раз.\n";
        wcout << L"БУКВА                    ";
        cin.clear();
        getline(cin, u);
        if (u.size() >= 2) {
            while (u[0] == ' ') u.erase(u.begin());
            while (u.size() > 1 && u[u.size() - 1] == ' ') u.erase(u.end() - 1);
        }
        flag = true;
        if (u.size() > 1) continue;
        io = u[0];

        if (int(io) >= -96 && int(io) <= -91) {
            io = char(int(io) - 32);
        }
        else if (int(io) == -15) {
            io = char(int(io) - 1);
        }
        else if (int(io) >= -90 && int(io) <= -81) {
            io = char(int(io) - 32);
        }
        else if (int(io) >= -32 && int(io) <= -17) {
            io = char(int(io) - 80);
        }

    } while (('А' - 64 > io || io > 'Я' - 64) && int(io) - 72 != int('Ё'));

    if (Letters[io]) {
        wcout << L"Вы, конечно, умный! Такая буква уже была.\n";
        CurPlayer = (CurPlayer + 1) % 3;
    }
    else {
        Letters[io] = true;
        int k = 0;
        bool f = false;
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i] - 64 == io || ((ans[i] == int(io) - 72) && (int(io) - 72 == int('Ё')))) {
                k++;
                f = true;
                s[i] = ans[i];
            }
        }

        if (f) {
            wcout << L"Есть такая буква.\n";
            PlayersScore[CurPlayer] += k * stoi(Points);
            Print(que, s, PlayersScore);
        }
        else {
            wcout << L"Нет такой буквы.\n";
            CurPlayer = (CurPlayer + 1) % 3;
        }
    }

}


question ChoosingRandomQuestion(vector <question>& Questions)
{
    int NumOfQue;
    NumOfQue = rand() % Questions.size();

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
    string s;
    vector <int> PlayersScore(3, 0);
    int CurPlayer = 0;
    string rep;


    bool ContinueGame = true;
    while(ContinueGame)
    {
        system("cls");
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        fill(PlayersScore.begin(), PlayersScore.end(), 0);
        
        question RoundQue = ChoosingRandomQuestion(Questions);
        string que = RoundQue.que, ans = RoundQue.ans;

        CurPlayer = 0;

        s = str.substr(0, ans.size());

        Print(que, s, PlayersScore);

        Letters.clear();
        while (true) {

            bool f = true;
            for (char i : s) {
                if (i == '_') {
                    f = false;
                    break;
                }
            }
            if (f) break;

            wstring Points = SpinDrum();
            wcout << CurPlayer + 1 << L"-ый игрок. Нажмите Enter, чтобы прокрутить барабан ";
            pause();
            wcout << L"Ход " << CurPlayer + 1 << L"-го игрока           " << OutputDrum << "               " << Points << "\n";

            if (Points == L"переход хода") {
                CurPlayer = (CurPlayer + 1) % 3;
            }
            else if (Points == L"+") {
                PlusOnDrum(que, s, ans, CurPlayer);
            }
            else {
                PointsOnDrum(que, s, ans, PlayersScore, CurPlayer, Points);
            }


        }

        if (Questions.size() == 0) {
            wcout << L"Новые вопросы закончились. Игра закончилась.\n";
            wcout << L"Нажмите SHIFT, чтобы выйти из приложения.\n";
            while (true)
                if (GetAsyncKeyState(VK_SHIFT)) {
                    exit(false);
                }
        }
        
        wcout << L"Выиграл " << CurPlayer + 1 << L"-й игрок. Баланс игрока " << PlayersScore[CurPlayer] << L" очков. Ура-ура-ура ...\n";
        wcout << L"Если вы хотите начать новую игру нажмите TAB, иначе нажмите кнопку SHIFT, чтобы выйти из игры.\n";

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        ContinueGame = false;
        while (Questions.size() > 0)
            if (GetAsyncKeyState(VK_TAB)) {
                ContinueGame = true;
                Sleep(150);
                break;
            }
            else if (GetAsyncKeyState(VK_SHIFT)) {
                exit(false);
            }

    }

    return 0;
}