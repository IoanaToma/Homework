#include <iostream>

using namespace std;

struct nod
{
    int info;
    nod *st;
    nod *dr;
    int LeftSize;
};

void insert (nod *&root, int x)
{
    if (!root)
    {
        nod *q;
        q = new nod;
        q->info = x;
        q->st = NULL;
        q->dr = NULL;
        root = q;
        root->LeftSize = 0;
    }
    else if (x < root->info)
            {
                insert (root->st, x);
                root->LeftSize ++;
            }
         else if (x > root->info)
                insert (root->dr, x);

}

void SRD (nod *rad)
{
    if (rad->st)
        SRD (rad->st);
    cout << rad->info << "/" << rad->LeftSize << " ";
    if (rad->dr)
        SRD (rad->dr);

}

int cautare (nod *rad, int k)
{
    if (k == rad->LeftSize)
        return rad->info;
    else
        if (k < rad->LeftSize)
            cautare (rad->st, k);
        else
            cautare (rad->dr, k-rad->LeftSize-1);

}


int main()
{
    nod *root;
    int x, k;
    root = new nod;
    root = NULL;

    cout << "Dati radacina arborelui:";
    cin >> x;
    while (x)
    {
        insert (root, x);
        cout << "Dati noul nod:";
        cin >> x;

    }

    cout << endl;
    SRD(root);
    cout << endl;

    cout << "Dati k:";
    cin >> k;
    cout << cautare(root, k);
    cout << endl;

    return 0;
}
