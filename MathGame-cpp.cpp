#include <iostream>
using namespace std;

enum QuestionsLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };
enum OperationsType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

void ReadNumberOfQuestions(int& NumberOfQuestions) {
    cout << "How many Questions do you want to answer? ";
    cin >> NumberOfQuestions;
}

void ReadQuestionsLevel(QuestionsLevel& level) {
    int InputLevel;
    cout << "Enter Questions level [1] Easy, [2] Mid, [3] Hard, [4] Mix? ";
    cin >> InputLevel;
    level = QuestionsLevel(InputLevel);
}

void ReadOperationsType(OperationsType& OpType) {
    int OperationType;
    cout << "Enter Operations Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix? ";
    cin >> OperationType;
    OpType = OperationsType(OperationType);
}

int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

string TypeSymbolOp(OperationsType OpType) {
    switch (OpType) {
    case Add: return "+";
    case Sub: return "-";
    case Mul: return "*";
    case Div: return "/";
    default: return "?";
    }
}

int DoOperation(int num1, int num2, OperationsType OpType) {
    switch (OpType) {
    case Add: return num1 + num2;
    case Sub: return num1 - num2;
    case Mul: return num1 * num2;
    case Div: return (num2 != 0) ? num1 / num2 : 0;
    default: return 0;
    }
}

void GenerateQuestions(int NumberOfQuestions, QuestionsLevel level, OperationsType OpType, int& RightAnswers, int& WrongAnswers) {
    for (int questionNum = 1; questionNum <= NumberOfQuestions; ++questionNum) {
        int num1, num2, UserAnswerNumber;

        switch (level) {
        case Easy:
            num1 = RandomNumber(1, 10);
            num2 = RandomNumber(1, 10);
            break;
        case Mid:
            num1 = RandomNumber(10, 50);
            num2 = RandomNumber(10, 50);
            break;
        case Hard:
            num1 = RandomNumber(50, 100);
            num2 = RandomNumber(50, 100);
            break;
        case Mix:
            level = QuestionsLevel(RandomNumber(1, 3));
            switch (level) {
            case Easy:
                num1 = RandomNumber(1, 10);
                num2 = RandomNumber(1, 10);
                break;
            case Mid:
                num1 = RandomNumber(10, 50);
                num2 = RandomNumber(10, 50);
                break;
            case Hard:
                num1 = RandomNumber(50, 100);
                num2 = RandomNumber(50, 100);
                break;
            }
            break;
        }

        if (OpType == MixOp) {
            OpType = OperationsType(RandomNumber(1, 4));
        }

        cout << "Question [" << questionNum << "]: " << num1 << " " << TypeSymbolOp(OpType) << " " << num2 << " = ? ";
        cin >> UserAnswerNumber;

        int CorrectAnswer = DoOperation(num1, num2, OpType);

        if (CorrectAnswer == UserAnswerNumber) {
            cout << "Right Answer :)" << endl;
            RightAnswers++;
        }
        else {
            cout << "Wrong Answer :(" << endl;
            cout << "The right answer is: " << CorrectAnswer << endl;
            WrongAnswers++;
        }
    }
}

void DisplayFinalResult(int NumberOfQuestions, OperationsType OpType, QuestionsLevel level, int RightAnswers, int WrongAnswers) {
    string FinalResults;
    if (RightAnswers > WrongAnswers) {
        FinalResults = "PASS";
        system("color 2F");
    }
    else {
        FinalResults = "FAIL";
        system("color 4F");
    }

    cout << "------------------------" << endl;
    cout << "Final Results: " << FinalResults << endl;
    cout << "Number Of Questions: " << NumberOfQuestions << endl;
    cout << "Questions Level: " << level << endl;
    cout << "Operation Type: " << OpType << endl;
    cout << "Number Of Right Answers: " << RightAnswers << endl;
    cout << "Number Of Wrong Answers: " << WrongAnswers << endl;
    cout << "------------------------" << endl;
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

int main() {
    srand((unsigned)time(NULL));

    char playagainchoice;
    do {
        int NumberOfQuestions, RightAnswers = 0, WrongAnswers = 0;
        OperationsType OpType;
        QuestionsLevel level;

        ReadNumberOfQuestions(NumberOfQuestions);
        ReadQuestionsLevel(level);
        ReadOperationsType(OpType);

        GenerateQuestions(NumberOfQuestions, level, OpType, RightAnswers, WrongAnswers);
        DisplayFinalResult(NumberOfQuestions, OpType, level, RightAnswers, WrongAnswers);

        cout << "Do you want to play again? Y/N: ";
        cin >> playagainchoice;
        ResetScreen();

    } while (playagainchoice == 'y' || playagainchoice == 'Y');

    return 0;
}
