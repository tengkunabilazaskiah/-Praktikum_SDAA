#include <iostream>
using namespace std;



void bikin_segitiga(int baris_sebelumnya[], int baris_sekarang[], int ukuran_baris)
{
    baris_sekarang[0] = 1;
    for (int i = 1; i < ukuran_baris - 1; ++i)
    {
        baris_sekarang[i] = baris_sebelumnya[i - 1] + baris_sebelumnya[i];
    }
    baris_sekarang[ukuran_baris - 1] = 1;
}

void segitiga_pascal(int n, int segitiga[][3], int baris = 0)
{
    if (baris == n)
        return;
    if (baris == 0)
    {
        segitiga[baris][0] = 1;
    }
    else
    {
        bikin_segitiga(segitiga[baris - 1], segitiga[baris], baris + 1);
    }
    segitiga_pascal(n, segitiga, baris + 1);
}

void segitiga_kanan(int segitiga[][3], int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            cout << segitiga[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    const int tingkat = 3;
    int segitiga[tingkat][tingkat] = {0};
    segitiga_pascal(tingkat, segitiga);
    segitiga_kanan(segitiga, tingkat);
    return 0;
}
