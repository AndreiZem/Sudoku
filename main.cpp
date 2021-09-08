// Sudoku.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int pole[10][10][10];
int sudoku[10][10];

ofstream file_out("out.txt");

void SetNum(int, int, int);
void OutFile();
void Filosofia();

int p_0_iskl_n();
int p_1_in_3x3(int, int);
int p_2_in_dl(int);
int p_3_in_vs(int);

int mi_1_in_3x3(int, int);
int mi_1_ud_g(int, int, int);
int mi_1_ud_v(int , int , int );


int main()
{
    setlocale(LC_ALL, "ru");
    cout << "Решаю СУДОКУ\n";

    ifstream file_in("sudoku.txt", ios::in);
    if (!file_in) {
        cout << "Error when try to open file " << endl;
        return -1;
    }

    file_out << "Решаею судоку:" << endl;


      cout << "Ctart\n";


    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            sudoku[i][j] = 0;
            for (int n = 1; n <= 9; n++) pole[i][j][n] = 1;
        }

    char Ch[2];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            do
            {
                file_in.read(Ch, 1);
              cout << Ch[0] ;
            } while ((Ch[0] == ' ') || (Ch[0] == 0xd) || (Ch[0] == 0xa));

            if (Ch[0] != '.')
                SetNum(i, j, int(Ch[0]) - 0x30);
        }
    }

    OutFile();

    int booll;
    do
    {


        booll = 0;

        booll += p_0_iskl_n();

        // 1. проверка на наличие единственного числа в квадрате 3*3
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                booll+=p_1_in_3x3(i, j);

        for (int i = 0; i < 8; i++)
        {
            booll += p_2_in_dl(i);
            booll += p_3_in_vs(i);
        }

        //
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                booll += mi_1_in_3x3(i, j);

    } while (booll > 0);


    Filosofia();


    file_in.close();
    file_out.close();

}

void SetNum(int x, int y, int Num)
{

    for (int n = 1; n <= 9; n++)  pole[x][y][n] = 0;

    // убираем это число из конкретного квадрата 3х3
    for (int i = (x/3)*3; i <= (x / 3)*3+2; i++)
        for (int j = (y/3)*3; j <= (y/3) * 3 +2; j++)
            pole[i][j][Num] = 0;

    // убираем это число из горизонтальной и вертикальной полосы
    for (int ij = 0; ij < 9; ij++)
        pole[ij][y][Num] = pole[x][ij][Num] = 0;

    // остовляем конкретное число в ячейке x y
    sudoku[x][y] = Num;
    //   pole[x][y][Num] = 1;

    // Filosofia();
}


void OutFile()
{
    file_out << endl;
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0) file_out << endl;

        for (int j = 0; j < 9; j++)

        {
            if (j % 3 == 0)  file_out << " ";

            if (sudoku[i][j] != 0)  file_out << sudoku[i][j];
            else file_out << "`";

        }
        file_out << endl;

    }
}
void Filosofia()

{

    file_out << endl;
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0) file_out << endl;

        for (int j = 0; j < 9; j++)

        {
            if (j % 3 == 0)  file_out << "|";


            for (int n = 1; n <= 9; n++)
                if (pole[i][j][n] == 1) file_out<<n;
                else file_out << "-";
            file_out << " ";
        }
        file_out << endl;

    }


}

int p_1_in_3x3(int x, int y)
{
    int Res = 0;
    int ii, jj;
    for (int n = 1; n <= 9; n++)
    {
        int s = 0;
        for (int i = x * 3; i < x * 3 + 3; i++)
            for (int j = y * 3; j < y * 3 + 3; j++)
                if( pole[i][j][n]==1) s++, ii=i, jj=j;

        if (s == 1)
        {
            file_out<< endl << "=================" << endl << "в поле ["<<ii+1<<","<<jj+1<<"] стаим "<< n<<" (одна в квадрате)";
            SetNum(ii, jj, n);
            OutFile();
            Res++;
        }

    }
    return(Res);
}


int p_2_in_dl(int a)
{
    int Res = 0;
    int ii, jj;
    for (int n = 1; n <= 9; n++)
    {
        int s = 0;
        for (int i =0 ; i < 9; i++)
            if (pole[i][a][n] == 1) s++, ii = i;

        if (s == 1)
        {
            file_out << endl << "=================" << endl << "в поле [" << ii + 1 << "," << a + 1 << "] стаим " << n << " (одна по "<< a+1 << " вертикали)";
            SetNum(ii, a, n);
            OutFile();
            Res++;
        }

    }
    return(Res);
}

int p_3_in_vs(int a)
{
    int Res = 0;
    int ii, jj;
    for (int n = 1; n <= 9; n++)
    {
        int s = 0;
        for (int i = 0; i < 9; i++)
            if (pole[a][i][n] == 1) s++, ii = i;

        if (s == 1)
        {
            file_out << endl << "=================" << endl << "в поле [" << a + 1 << "," << ii + 1 << "] стаим " << n << " (одна по " << a + 1 << " горизонтали)";
            SetNum(a, ii, n);
            OutFile();
            Res++;
        }

    }
    return(Res);

}

int p_0_iskl_n()
{
    int Res = 0;
    int s ;
    int Num ;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            s = 0;
            Num = 0;
            for (int n = 1; n <= 9; n++)
                if (pole[i][j][n] == 1) s++,Num=n;

            if (s == 1)
            {
                file_out << endl << "=================" << endl << "в поле [" << i + 1 << "," << j + 1 << "] стаим " << Num << " (исключили пересечения)";
                SetNum(i, j, Num);
                OutFile();
                Res++;
            }
        }

    return(Res);

}

int mi_1_in_3x3(int x, int y)
{


    int Res = 0;
    int R;
    for (int n = 1; n <= 9; n++)
    {
        int s = 1;
        int xox = 0;
        for (int i = x * 3; i < x * 3 + 3; i++)
            for (int j = y * 3; j < y * 3 + 3; j++)
            {
                if (pole[i][j][n] == 1) xox += s;
                s *= 2;
            }

        if (((xox ^ 0x3) == 0) || ((xox ^ 0x5) == 0) || ((xox ^ 0x6) == 0) || ((xox ^ 0x7) == 0))
        {
            R =  mi_1_ud_g(x * 3 + 0, y, n);
            if (R>0)  Filosofia() , file_out << endl << "```" << endl << "в поле [" << x + 1 << "," << y + 1 << "] на число  " << n;
            Res += R;
        }

        if (((xox ^ 0x18) == 0) || ((xox ^ 0x28) == 0) || ((xox ^ 0x30) == 0) || ((xox ^ 0x38) == 0))
        {
            R = mi_1_ud_g(x * 3 + 1, y, n);
            if (R > 0)  Filosofia(), file_out << endl << "---" << endl << "в поле [" << x + 1 << "," << y + 1 << "] на число  " << n;
            Res += R;

        }

        if (((xox ^ 0xc0) == 0) || ((xox ^ 0x1c0) == 0) || ((xox ^ 0x180) == 0) || ((xox ^ 0x140) == 0))
        {
            R = mi_1_ud_g(x * 3 + 2, y, n);
            if (R > 0) Filosofia(), file_out << endl << "___" << endl << "в поле [" << x + 1 << "," << y + 1 << "] на число  " << n;
            Res += R;
        }



        if (((xox ^ 0x9) == 0) || ((xox ^ 0x49) == 0) || ((xox ^ 0x41) == 0) || ((xox ^ 0x48) == 0))
        {

            R = mi_1_ud_v(y * 3 + 0, x, n);
            if (R > 0) Filosofia(), file_out << endl << "|--" << endl << "в поле [" << x + 1 << "," << y + 1 << "] на число  " << n;
            Res += R;

        }

        if (((xox ^ 0x12) == 0) || ((xox ^ 0x92) == 0) || ((xox ^ 0x82) == 0) || ((xox ^ 0x90) == 0))
        {

            R = mi_1_ud_v(y * 3 + 1, x, n);
            if (R > 0) Filosofia(), file_out << endl << "-|-" << endl << "в поле [" << x + 1 << "," << y + 1 << "] на число  " << n;
            Res += R;
        }

        if (((xox ^ 0x120) == 0) || ((xox ^ 0x104) == 0) || ((xox ^ 0x24) == 0) || ((xox ^ 0x124) == 0))
        {
            R = mi_1_ud_v(y * 3 + 2, x, n);
            if (R > 0) Filosofia(), file_out << endl << "--|" << endl << "в поле [" << x + 1 << "," << y + 1 << "] на число  " << n;
            Res += R;
        }






    }
    return(Res);
}
int mi_1_ud_g(int x, int y, int n)
{
    int Res = 0;
    for (int j = 0; j < 9; j++)
    {
        if ((j < y * 3) || (j > (y * 3 + 2)))
            if (pole[x][j][n] == 1) pole[x][j][n] = 0, Res = 1;

    }

    return(Res);
}

int mi_1_ud_v(int x, int y, int n)
{
    int Res = 0;
    for (int j = 0; j < 9; j++)
    {
        if ((j < y * 3) || (j > (y * 3 + 2)))
            if (pole[j][x][n] == 1) pole[j][x][n] = 0, Res = 1;

    }

    return(Res);
}



