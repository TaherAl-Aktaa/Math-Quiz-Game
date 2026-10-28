#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

enum enOperationType { Addition, Substration, Division, Multiplication, MixOp };

enum enQuestionLevel { Easy, Normal, Hard, MixLvl };


struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuiz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionsLevel;
    enOperationType OperationType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool HavePassed = false;
};

void ResetScreen()
{
    system("cls");
    system("color 0f");
}

int ReadPostiveNumber(string Massege)
{
    int Number;

    do {
        cout << Massege << endl;
        cin >> Number;

    } while (Number <= 0);

    return Number;
}

int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

int CalculateResult(int Number1, int Number2, enOperationType OperationType)
{
    switch (OperationType)
    {
    case Addition:
        return Number1 + Number2;
        break;
    case Substration:
        return Number1 - Number2;
        break;
    case Division:
        return Number1 / Number2;
        break;
    case Multiplication:
        return Number1 * Number2;
        break;
    }
}

int ReadNumber()
{
    int Number;
    cin >> Number;
    return Number;
}

enQuestionLevel ReadQuesionsLevel()
{
    short QuestionLevel;

    cout << "Choose the level of the quizzes\n";

    do
    {
        cout << "[1]Easy, [2]Normal, [3]Hard, [4]Mix\n";
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return enQuestionLevel(QuestionLevel - 1);
}

enOperationType ReadOperationType()
{
    short OperationType;

    cout << "\nWhat kind of operation you want\n";
    do
    {
        cout << "[1] Addition(+), [2] Substraction(-), [3] Division(/), [4] Multiplication(*), [5] Mix\n";
        cin >> OperationType;

    } while (OperationType < 0 || OperationType > 5);

    return enOperationType(OperationType - 1);
}

enQuestionLevel GetMixLevel()
{
    return enQuestionLevel(RandomNumber(0, 2));
}

enOperationType GetMixOperation()
{
    return enOperationType(RandomNumber(0, 3));
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::MixLvl)
        QuestionLevel = GetMixLevel();

    Question.QuestionLevel = QuestionLevel;

    if (OperationType == enOperationType::MixOp)
        OperationType = GetMixOperation();

    Question.OperationType = OperationType;

    switch (QuestionLevel)
    {
    case Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = CalculateResult(Question.Number1, Question.Number2, Question.OperationType);
        return Question;
        break;
    case Normal:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = CalculateResult(Question.Number1, Question.Number2, Question.OperationType);
        return Question;
        break;
    case Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = CalculateResult(Question.Number1, Question.Number2, Question.OperationType);
        return Question;
        break;
    }
}

string GetOperationTypeText(enOperationType OperationType)
{
    switch (OperationType)
    {
    case Addition:
        return"+";
        break;
    case Substration:
        return"-";
        break;
    case Division:
        return"/";
        break;
    case Multiplication:
        return"*";
        break;
    case MixOp:
        return"Mix";
        break;
    default:
        break;
    }
}

void GenerateQuizQuestion(stQuiz& Quiz)
{
    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
    {
        Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionsLevel, Quiz.OperationType);
    }
}

void PrintTheQuestion(stQuiz& Quiz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "] \n\n";
    cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quiz.QuestionList[QuestionNumber].Number2 << "\n";
    cout << GetOperationTypeText(Quiz.QuestionList[QuestionNumber].OperationType);
    cout << "\n____________" << endl;
}

void SetScreenColor(bool AnswerResult)
{
    if (AnswerResult)
        system("color 2f");
    else
        system("color 4f");
}

void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
    if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;

        cout << "Wrong answer :-(\n";
        cout << "The right answer is : ";
        cout << Quiz.QuestionList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        Quiz.NumberOfRightAnswers++;

        cout << "Right answer :-)\n";
    }
    cout << endl;

    SetScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuiz& Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quiz, QuestionNumber);
        Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadNumber();
        CorrectTheQuestionAnswer(Quiz, QuestionNumber);
    }

    Quiz.HavePassed = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "Pass :-)";
    else
        return "Fail :-(";
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevel[4] = { "Easy", "Normal", "Hard", "Mix" };
    return arrQuestionLevel[QuestionLevel];
}

void PrintQuizResult(stQuiz Quiz)
{
    cout << "\n______________________________\n\n";
    cout << "Final Results is " << GetFinalResultsText(Quiz.HavePassed);
    cout << "\n______________________________\n\n";

    cout << "Number of questions : " << Quiz.NumberOfQuestions << endl;
    cout << "Questions level     : " << GetQuestionLevelText(Quiz.QuestionsLevel) << "\n";
    cout << "Operation type      : " << GetOperationTypeText(Quiz.OperationType) << "\n";
    cout << "Number of right answers : " << Quiz.NumberOfRightAnswers << "\n";
    cout << "Number of wrong answers : " << Quiz.NumberOfWrongAnswers << "\n";
    cout << "_________________________________________" << endl;
}

void PlayMathGame()
{
    stQuiz Quiz;
    Quiz.NumberOfQuestions = ReadPostiveNumber("Enter how many questions you want to answer");
    Quiz.QuestionsLevel = ReadQuesionsLevel();
    Quiz.OperationType = ReadOperationType();

    GenerateQuizQuestion(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);
    PrintQuizResult(Quiz);
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        PlayMathGame();

        cout << "Do you want to play agian? Y/N\n";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}