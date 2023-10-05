#include <iostream>
#include <stdlib.h>
#include <windows.h>
using namespace std;
class BettlaShip
{
private:
    string Name;                // 玩家名子
    int AttackX, AttackY, Ship; // 攻擊的x位子與y位子
public:
    const static int row = 10;
    const static int column = 10;
    char matrix[column][row], attack[column][row];
    int matrixX = 0, matrixY = 0, vol[6] = {0, 2, 3, 3, 4, 5}, shipnum = 1, player;
    char Straight;
    BettlaShip() : Name("Player"), AttackX(.0), AttackY(.0), Ship(17) {}
    void Set(string _N)
    {
        Name = _N;
    }
    void map() // 地圖設定
    {
        char b = 0;
        for (int x = 0; x < row; x++)
        {
            for (int y = 0; y < column; y++)
            {
                matrix[y][x] = ' ';
                attack[y][x] = ' ';
            }
        }
        for (int x = 1; x < row; x++)
        {
            for (int y = 1; y < column; y++)
            {
                matrix[y][x] = '.';
                attack[y][x] = '.';
            }
        }
        for (int x = 1; x < row; x++)
        {
            b = 48 + x;
            matrix[0][x] = b;
            attack[0][x] = b;
        }
        b = 0;
        for (int y = 0; y < column; y++)
        {
            b = 48 + y;
            matrix[y][0] = b;
            attack[y][0] = b;
        }
    }
    void SetShip() // 玩家1設定位子
    {
        for (; shipnum < 6;)
        {
cout << "請"<<this->Name<<"輸入第" << shipnum<< "艘船頭位子:(R=行/C=列)(X)(Y)";
cin >> Straight >> matrixX>> matrixY;
check();
        }
    }
    void check()
    {
        if (Straight == 'R' || Straight == 'r' || Straight == 'c' || Straight == 'C') // 偵測輸入是否錯誤
        {
if (matrixX < 1 || matrixX > 11 || matrixY < 1 || matrixY > 11)
{
    cout << "輸入錯誤，請重新輸入" << endl;
    SetShip();
}
if (Straight == 'R' || Straight == 'r') // 偵測輸入位子是否會超過範圍
{
    if (matrixX + vol[shipnum] > row)
    {
        cout << "船的空間超過範圍，請重新輸入" << endl;
        SetShip();
    }
    else
    { // 偵測輸入位子是否會已經被佔用了
        for (int i = 0; i < vol[shipnum]; i++)
        {
            if (matrix[matrixY][matrixX + i] == 'S')
            {
                cout << "輸入的位子已經有一艘船了" << endl;
                SetShip();
            }
        }
    }
}
if (Straight == 'c' || Straight == 'C')
{
    if (matrixY + vol[shipnum] > column)
    {
        cout << "船的空間超過範圍，請重新輸入" << endl;
        SetShip();
    }
    else
    { // 偵測輸入位子是否會已經被佔用了
        for (int i = 0; i < vol[shipnum]; i++)
        {
            if (matrix[matrixY + i][matrixX] == 'S')
            {
                cout << "輸入的位子已經有一艘船了" << std::endl;
                SetShip();
            }
        }
    }
}
plant();
        }
        else
        {
cout << "輸入錯誤，請重新輸入" << endl;
SetShip();
        }
    }
    void plant() // 建立玩家軍艦的位子
    {
        if (Straight == 'c' || Straight == 'C')
        {
for (int i = 0; i < vol[shipnum]; i++)
{
    matrix[matrixY + i][matrixX] = 'S';
}
boat();
        }
        if (Straight == 'R' || Straight == 'r')
        {
for (int i = 0; i < vol[shipnum]; i++)
{
    matrix[matrixY][matrixX + i] = 'S';
}
boat();
        }
    }
    void boat()
    {
        system("cls");
        print();
        shipnum++;
        SetShip();
    }
    void print() // 讓自己可以看見自己所設的軍艦位子
    {
        system("cls");
        for (int x = 0; x < row; x++)
        {
for (int y = 0; y < column; y++)
{
    cout << matrix[x][y];
}
cout << endl;
        }
    }
    void AttackCin(BettlaShip *p0ther) // 輸入攻擊位子
    {
        if (!IsAttackAllShip(p0ther))
        {
printattack();
cout << this->Name << "請輸入要攻擊的位子:(X)(Y)";
cin >> AttackX >> AttackY;
AttackCinCheck(p0ther);
        }
    }
    void AttackCinCheck(BettlaShip *p0ther) // 判斷是否輸入錯誤
    {
        if (AttackX < 1 || AttackX > 9 || AttackY < 1 || AttackY > 9)
        {
cout << "輸入錯誤，請重新輸入" << endl;
AttackCin(p0ther);
        }
        else
AttackShipCheck(p0ther);
    }
    void AttackShipCheck(BettlaShip *p0ther) // 判斷是否有打中
    {
        if (!IsAttackAllShip(p0ther))
        {
if (p0ther->matrix[AttackY][AttackX] == 'S')
{
    printattack();
    this->attack[AttackY][AttackX] = 'O';
    Ship--;
    AttackCin(p0ther);
    system("cls");
}
else
{
    this->attack[AttackY][AttackX] = 'X';
    system("cls");
    cout << "請" << p0ther->Name << "準備輸入";
    Sleep(5000);
    system("PAUSE");
}
        }
    }
    void printattack() // 顯示海戰圖
    {
        system("cls");
        for (int x = 0; x < row; x++)
        {
for (int y = 0; y < column; y++)
{
    cout << attack[x][y];
}
cout << endl;
        }
    }
    bool IsAttackAllShip(BettlaShip *p0ther) // 判斷是否把敵人的船艦打完
    {
        if (Ship <= 0)
        {
cout << this->Name << "打到全部敵人船艦";
cout << endl
     << endl
     << this->Name << "戰艦圖" << endl;
for (int x = 0; x < row; x++)
{
    for (int y = 0; y < column; y++)
    {
        cout << this->matrix[x][y];
    }
    cout << endl;
}
cout << endl
     << endl
     << this->Name << "海戰圖" << endl;
for (int x = 0; x < row; x++)
{
    for (int y = 0; y < column; y++)
    {
        cout << this->attack[x][y];
    }
    cout << endl;
}
cout << endl
     << endl
     << p0ther->Name << "戰艦圖" << endl;
for (int x = 0; x < row; x++)
{
    for (int y = 0; y < column; y++)
    {
        cout << p0ther->matrix[x][y];
    }
    cout << endl;
}
cout << endl
     << endl
     << p0ther->Name << "海戰圖" << endl;
for (int x = 0; x < row; x++)
{
    for (int y = 0; y < column; y++)
    {
        cout << p0ther->attack[x][y];
    }
    cout << endl;
}
return true;
        }
        return false;
    }
};
class APlayer : public BettlaShip
{
public:
    string name;
    int x, y;
    APlayer()
    {
        string name;
        cout << "請輸入英文玩家名:";
        cin >> name;
        Set(name);
        map();
        SetShip();
    }
};
class BPlayer : public BettlaShip
{
public:
    BPlayer()
    {
        string name;
        cout << "請輸入英文玩家名:";
        cin >> name;
        Set(name);
        map();
        SetShip();
    }
};
int main()
{
    int player = 1, shootship, aship = 17, bship = 17, version;
    APlayer A;
    system("cls");
    cout << "請第2位玩家準備輸入" << endl
         << "載入中...." << endl;
    Sleep(5000);
    system("PAUSE");
    system("cls");
    BPlayer B;
    system("cls");
    cout << "準備攻擊" << endl
         << "載入中...." << endl;
    Sleep(5000);
    while (!A.IsAttackAllShip(&B) && !B.IsAttackAllShip(&A))
    {
        A.AttackCin(&B);
        if (A.IsAttackAllShip(&B))
        {
break;
        }
        B.AttackCin(&A);
        if (B.IsAttackAllShip(&A))
        {
break;
        }
    }
    return 0;
}
