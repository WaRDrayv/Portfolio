#include "TestBench.h"
int ProtectFromChars(string variable);
void Menu();

int main()
{
    Menu();
}


void Menu()
{
    int I = 10,//Момент инерции двигателя (кг*м^2)
        Toh = 110,//Температура перегрева

        Tenv = 0;//Температура окружающей среды

    double Hm = 0.01,//Коэффициент зависимости скорости нагрева от крутящего момента (С^0/H*m*сек)
        Hv = 0.0001,//Коэффициент зависимости скорости нfuhtdf от скорости вращения коленвала (С^0*сек/рад^2)
        C = 0.1;//Коэффициент зависимости скорости охлаждения от температуры двигателя и окружающей среды (1/сек)
    vector<int> M = { 20, 75, 100, 105, 75, 0 },//Кусочно-линейная зависимость крутящего момента, вырабатываемого двигателем от скорости вращения коленвалом (Н*м)
                V = { 0, 75, 150, 200, 250, 300 };//Скорость вращения коленвалом (радиан/сек)

    static TestBench testbench;//Штож в плюсах я не мастер, наверное это "верное" решение

    //Console.ForegroundColor = ConsoleColor.Yellow;
    cout << "Menu" << endl << endl;
    //Console.ResetColor();
    cout << "1 - Start test engine in Test Bench" << endl;
    cout << "2 - Load engine parametrs" << endl;
    cout << "3 - Set envairment temperature" << endl;
    cout << "4 - Load TEST parametrs (Toh = 2200)" << endl;
    cout << "0 - Exite" << endl;


    char opt, opt2;
    string strEnter;
    //cin.getline(opt, 1);
    cin >> opt;
    if (opt >= '0' && opt <= '9')
    {
        switch (opt)
        {
        case '1':
            //Console.Clear();
            system("cls");
            if (testbench.engine.Check_Params())
            {
                testbench.Start_Engine_Test_Overheating();
                cout << "\n1 - Return to Menu " << endl;
                cout << "0 - Exite Program" << endl;

                cin >> opt2;
                if (opt2 == 1)
                {
                    system("cls");
                    Menu();
                }
                else if (opt2 == 0) return;

            }
            else
            {
                if (Tenv == 0)
                {
                    cout << "Please, set environment temperature" << endl;

                    cin >> strEnter;
                    Tenv = ProtectFromChars(strEnter);
                    testbench.engine.tenv_is_Set = true;
                }
                testbench.Engine_Load_Params(I, Toh, Tenv, Hm, Hv, C, M, V);
                testbench.Start_Engine_Test_Overheating();
                cout << "\n1 - Return to Menu " << endl;
                cout << "0 - Exite Program" << endl;
                cin >> opt2;
                if (opt2 == 1)
                {
                    system("clr");
                    Menu();
                }
                else if (opt2 == 0) return;
            }

            break;

        case '2':
            if (Tenv == 0)
            {
                cout << "Please, set environment temperature" << endl;
                cin >> strEnter;
                Tenv = ProtectFromChars(strEnter);
                testbench.engine.tenv_is_Set = true;
                system("clr");
            }
            testbench.Engine_Load_Params(I, Toh, Tenv, Hm, Hv, C, M, V);
            Menu();
            break;

        case '3':
            cout << "Please, set environment temperature" << endl;
            //Tenv = int.Parse(Console.ReadLine());
            cin >> strEnter;
            Tenv = ProtectFromChars(strEnter);
            testbench.engine.tenv_is_Set = true;
            testbench.Engine_Load_Params(I, Toh, Tenv, Hm, Hv, C, M, V);
            system("clr");
            Menu();
            break;

        case '4':
            system("clr");
            cout << "Please, set environment temperature" << endl;
            cin >> strEnter;
            Tenv = ProtectFromChars(strEnter);
            testbench.engine.tenv_is_Set = true;
            system("clr");
            testbench.Engine_Load_Params(I, 2200, Tenv, Hm, Hv, C, M, V);
            Menu();
            break;

        case '0':
            return;
            //exit(0);
            break;


        default:
            break;
        }
    }
    else
    {
        cout << "Incorrect option, please, use only numbers!" << endl;
        Menu();
    }
}
/// <summary>
/// Метод проверяет наличие цифр, если обнаруживает всё что не цифра - отсекает.
/// </summary>
/// <param name="variable">Полученные данные в метод в виде строки</param>
/// <returns>Возвращаем только цифры</returns>
int ProtectFromChars(string variable)
{
    string result = "";
    for (char varif : variable)
    {
        if (varif >= '0' && varif <= '9') result += varif;//тут делаем "полегче" чем в шарпе

    }
    if (result == "") return 0;//Без этой конструкции при вводе спецсимволом вернёт ошибку
    else if (variable.substr(0, 1) == "-") //Костыль. Поскольку "-" не является цифрой, код выше его отсекает. Поскольку работаем
    {                                         //с строками и возвращаем число, добавим условия предварительного прибавления отрицания числу
        result = "-" + result;
        return stoi(result);//Вернём велеколепное отрицательное
    }
    else return stoi(result);// А если нет - то ок, пусть будет положительное
}

void TEST()
{
    vector<int> M = { 20, 75, 100, 105, 75, 0 },//Кусочно-линейная зависимость крутящего момента, вырабатываемого двигателем от скорости вращения коленвалом (Н*м)
                V = { 0, 75, 150, 200, 250, 300 };

    EngineOperation engin = EngineOperation();
    engin.Load_Params(10, 110, 10, 0.01, 0.0001, 0.1, M, V);
    for (int i = 0; i <= 100; i++)
    {
        engin.Engine_Working();
        cout << "Vf : {engin.Vf}, Mf : {engin.Mf}, T : {engin.Teng}";
    }

}