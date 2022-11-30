#include "EngineOperation.h"



//class Engine_Operation {
//private:
//    int I = 0;
//    double Hm = 0, Hv = 0, C = 0, a = 0, Toh = 0, Tenv = 0;
//    vector<int> M,
//                V;
//
//public:
//    double Vf = 0,
//           Mf = 0,
//           Teng = 0;
//
//    bool tenv_is_Set = false;

    //int getToh() const { return Toh; }
    //double getTenv() const { return Tenv; }
    //int getI() const { return I; }
    //double getHm() const { return Hm; }
    //double getHv() const { return Hv; }
    //double getC() const { return C; }

void EngineOperation::Engine_Working()
{
    if (Check_Params())
    {
        Check_M_V_Ratio();
        a = (Mf / I); //�������, ���� ����� ��������� ��������� ��� ��������

        if (Vf < V[V.size() - 1]) Vf += a; //����������� �������� ��������� �� ������ ��������� (������ ���, ���� ������� �� �������� ������)
        else Vf = V[V.size() - 1];
                                    //����� ����������, ����� �� ����� ����� � ��������� �� ���-�� ������ ����� �������
        Teng = Teng + (Calc_Vh() - Calc_Vc()); // � t ��������� �������� �������� ������� � ���������� ���������
    }

}

void EngineOperation::Load_Params(int I, int Toh, int Tenv, double Hm, double Hv, double C, vector<int> M, vector<int> V)
{
    this->I = I;
    this->Toh = Toh;
    this->Tenv = Tenv;
    this->Hm = Hm;
    this->Hv = Hv;
    this->C = C;
    //2 ������� ��� ��������. ������ ���� �����, �.�. Array.Copy() �� �������� � �������� ���������. �����: �������� � ������� (������������ ������)
    //_M = new int[M.Length];
    //_V = new int[V.Length];
    //Array.Copy(M, _M.ToArray(), M.Length);
    //Array.Copy(V, _V.ToArray(), V.Length);
    //******************************************************
    //this->M = { M, M + (sizeof(M) / sizeof(M[0])) };      *  ������ ����� 1 ������� ���������
    //this->V = { V, V + (sizeof(V) / sizeof(V[0])) };      **
    //                                                      ** -> ��������, ������� ������� ��������
    //memcpy(&this->M, &M, sizeof(this->M));                **  
    //memcpy(&this->V, &V, sizeof(this->V));                *  ����������� - ���� ����������, �� ����� ������ �� ������ ���� ������������� ������ 
    //******************************************************   � ������� ������� (��. ��������� ������)
    //������ - �� ������, ����� ��������� ������������ ��������, ��� �������!
    this->M = M;
    this->V = V;


    if (Check_Params())
    {
        //Console.ForegroundColor = ConsoleColor.Green;
        cout << "All parameters are set correctly!" << endl;
        //Console.ResetColor();
    }

    Teng = Tenv;//����������� ��������� ����� ����������� ���������� �����
    Mf = M[0];//����� ����� ���� �� ������, �.�. ����� ������ ����� �� ����� ��������� Check_M_V_Ratio, � �����������
               //Mf = _M[i], �� �������������.
    Vf = V[0];

}

double EngineOperation::Calc_Vh()
{
    return (Mf * Hm) + (pow(Vf, 2) * Hv);
}


double EngineOperation::Calc_Vc()
{
    return C * (Tenv - Teng);
}


void EngineOperation::Check_M_V_Ratio()
{
    for (int i = 0; i <= M.size() - 1; i++)
    {
        if (Vf >= V[i]) Mf = M[i];
    }
}

bool EngineOperation::Check_Params()
{
    bool intCheck = false,
        doubleCheck = false,
        arrIntCheck = false;

    //Console.ForegroundColor = ConsoleColor.Red;

    if (I != 0 && Toh != 0 && tenv_is_Set != false) intCheck = true;
    else
    {
        if (I == 0) cout << "Error! \'I\' is emty" << endl;
        if (Toh == 0) cout << "Error! \'Toh\' is emty" << endl;
        if (Tenv == 0) cout << "Error! \'Tenv\' not set" << endl;
    }

    if (Hm != 0 && Hv != 0 && C != 0) doubleCheck = true;
    else
    {
        if (Hm == 0) cout << "Error! \'Hm\' is emty" << endl;
        if (Hv == 0) cout << "Error! \'Hv\' is emty" << endl;
        if (C == 0) cout << "Error! \'C\' is emty" << endl;
    }
    if (M.size() != 0 && V.size() != 0 && M.size() == V.size()) arrIntCheck = true;
    else {
        if (M.size() == 0) cout << "Error! \'M\' is emty" << endl;
        if (V.size() == 0) cout << "Error! \'V\' is emty" << endl;
        if (M.size() != V.size()) cout << "Error! \'M\' and \'V\' is not equal" << endl;
    }

    if (intCheck == true && doubleCheck == true && arrIntCheck == true)
    {
        //Console.ForegroundColor = ConsoleColor.Green;
        //Console.WriteLine("All parameters are set correctly!");
        //Console.ResetColor();
        return true;
    }
    else
    {
        //Console.ForegroundColor = ConsoleColor.Red;
        //Console.WriteLine("Check_Params is failed");
        //Console.ResetColor();
        return false;
    }

}
//};