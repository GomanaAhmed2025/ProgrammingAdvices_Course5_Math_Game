#include<iostream>
#include <ctime>
using namespace std;


enum enOperationType { Addition = 1, Subtruction = 2, Multiplication = 3, Division = 4, MixOP = 5 };
enum enQuistionLevel { Easy = 1, Medium = 2, Hard = 3, Mix = 4 };

int RandomNumber(int From, int To)
{
    int RanNum = 0;
    RanNum = rand() % (To - From + 1) + From;
    return RanNum; 
}

struct stQuestionInfo
{
    int Number1 = 0;
    int Number2 = 0;
    enQuistionLevel Level;
    enOperationType OpType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stGameInfo 
{
    stQuestionInfo QuistionsList[100];
    short NumberOfQuestions = 0;
    enOperationType  OperationType;
    enQuistionLevel QuistionLevel;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool isPass = false;
};

void SetScreenColor(bool Right)
{
    if (Right)
        system("color A7");
    else
    {
        system("color C7");
        cout << "\a";
    }
}

short ReadNumberOfQuestions()
{
    short QuestionsNumber;
    do
    {
        cout << "How Many Questions Do You Want To Answer ? ";
        cin >> QuestionsNumber;
    } while (QuestionsNumber < 1 || QuestionsNumber>100);

    return QuestionsNumber;
}

enQuistionLevel ReadQuestionLevel()
{
    short QuistionLevel;

    do
    {
        cout << "Enter Questions Level : [ 1) Easy , 2) Medium , 3) Hard , 4) Mix ] ? ";
        cin >> QuistionLevel;
    } while (QuistionLevel < 1 || QuistionLevel>4);

    return (enQuistionLevel)QuistionLevel;
}

enOperationType ReadOperationType()
{
    short OperationType;

    do
    {
        cout << "Enter Operation Type : [ 1) Addition , 2) Subtruction , 3) Multiplication , 4) Division , 5) Mix ] ? ";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);

    return (enOperationType)OperationType;
}

string GetOperationTypeSympol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Addition:
           return "+";

    case enOperationType::Subtruction:
        return "-";

    case enOperationType::Multiplication:
        return "*";

    case enOperationType::Division:
        return "/";

    default:
        return "MixOP";

    }
}

string GetQuestionLevelAsText(enQuistionLevel Level)
{
    string ArrLevel[4] = { "Easy","Medium","Hard","Mixed" };
    return ArrLevel[Level - 1];
}

int SimpleCalculator(int Num1, int Num2, enOperationType OperationType)
{
    switch (OperationType)
    {
    case enOperationType::Addition:
        return Num1 + Num2;

    case enOperationType::Subtruction:
        return Num1 - Num2;

    case enOperationType::Multiplication:
        return Num1 * Num2;

    case enOperationType::Division:
        return Num1 / Num2;
    }
}

enOperationType GetRandomOperationType()
{
    short OpType =  RandomNumber(1, 4);
    return (enOperationType)OpType;
}

stQuestionInfo GenerateEachQuestion(enQuistionLevel Level, enOperationType OpType)
{
    stQuestionInfo Question;

    if (Level == enQuistionLevel::Mix)
        Level = (enQuistionLevel)RandomNumber(1, 3);

    if (OpType == enOperationType::MixOP)
        OpType = GetRandomOperationType();

    Question.OpType = OpType;

    switch (Level)
    {
    case enQuistionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        Question.Level = Level;

        return Question;

    case enQuistionLevel::Medium:
        Question.Number1 = RandomNumber(11, 50);
        Question.Number2 = RandomNumber(11, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        Question.Level = Level;

        return Question;

    case enQuistionLevel::Hard:
        Question.Number1 = RandomNumber(51, 100);
        Question.Number2 = RandomNumber(51, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        Question.Level = Level;

        return Question;
    }

    return Question;
}

void GenerateGameQuestions(stGameInfo& Quiz)
{
    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
        Quiz.QuistionsList[Question] = GenerateEachQuestion(Quiz.QuistionLevel, Quiz.OperationType);
}

int ReadUserAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stGameInfo& Quiz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "] \n\n";
    cout << Quiz.QuistionsList[QuestionNumber].Number1 << endl;
    cout << Quiz.QuistionsList[QuestionNumber].Number2 << " " << endl;
    cout << GetOperationTypeSympol(Quiz.QuistionsList[QuestionNumber].OpType);
    cout << "\n___________" << endl;
}

void CorrectTheQuestionAnswer(stGameInfo& Quiz, short QuestionNumber)
{
    if (Quiz.QuistionsList[QuestionNumber].PlayerAnswer != Quiz.QuistionsList[QuestionNumber].CorrectAnswer)
    {
        Quiz.QuistionsList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;

        cout << "IT'S WORNG :-( \n";
        cout << "The Right Answer Is : " << Quiz.QuistionsList[QuestionNumber].CorrectAnswer << endl;
    }

    else
    {
        Quiz.QuistionsList[QuestionNumber].AnswerResult = true;
        Quiz.NumberOfRightAnswers++;

        cout << "IT'S RIGHT :-) \n";
    }

    cout << endl;

    SetScreenColor(Quiz.QuistionsList[QuestionNumber].AnswerResult);
}

string GetFinalResultAsText(bool isPass)
{
    if (isPass)
        return "Pass :-)";
    else
        return "Fail :-(";
}

void AskAndCorrectQuestionListAnswer(stGameInfo& Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quiz, QuestionNumber);

        Quiz.QuistionsList[QuestionNumber].PlayerAnswer = ReadUserAnswer();

        CorrectTheQuestionAnswer(Quiz, QuestionNumber);

    }

    Quiz.isPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

void PrintQuizResult(stGameInfo& Quizz)
{
    cout << "\n ____________________________________\n\n";
    cout << "   Final Result Is : " << GetFinalResultAsText(Quizz.isPass) << endl;
    cout << "\n ____________________________________\n\n";

    cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level     : " << GetQuestionLevelAsText(Quizz.QuistionLevel) << endl;
    cout << "Operation Type      : " <<GetOperationTypeSympol(Quizz.OperationType) << endl;
    cout << "Number Of Right Answers = " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number Of Wrong Answers = " << Quizz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n";
}

void PlayMathGame()
{
    stGameInfo Quiz;

    Quiz.NumberOfQuestions = ReadNumberOfQuestions();
    Quiz.QuistionLevel = ReadQuestionLevel();
    Quiz.OperationType = ReadOperationType();

    GenerateGameQuestions(Quiz);

    AskAndCorrectQuestionListAnswer(Quiz);

    PrintQuizResult(Quiz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain;

    do
    {
        ResetScreen();
        PlayMathGame();

        cout << "Do You Want To Play Again? (Y/N): ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{

    srand((unsigned)time(NULL));
    StartGame();

    return 0;
    
}

