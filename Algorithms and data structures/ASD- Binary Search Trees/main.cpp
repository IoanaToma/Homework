#include <iostream>

using namespace std;

struct nod
{
    int info;
    nod *st;
    nod *dr;
};

void SRD (nod *rad)
{
    if (rad->st)
        SRD (rad->st);
    cout << rad->info << " ";
    if (rad->dr)
        SRD (rad->dr);

}

void insert (nod *&rad, int x)
{
    if (!rad)
    {
        nod *q;
        q = new nod;
        q->info = x;
        q->st = NULL;
        q->dr = NULL;
        rad = q;
    }
    else if (x < rad->info)
            insert (rad->st, x);
         else if (x > rad->info)
                insert (rad->dr, x);
}

int search (nod *rad, int x)
{
    if (rad->info == x) return 1;
        else
            if (x < rad->info && rad->st)
                search (rad->st, x);
             else
                if (x > rad->info && rad->dr)
                    search (rad->dr, x);
                else return 0;
}

int findMax (nod *rad)
{
    if (!rad->dr) return rad->info;
        else findMax (rad->dr);
}

nod *search1 (nod *rad, int x)
{
        if (rad->info == x) return NULL;
        if ((rad->st && rad->st->info == x) || (rad->dr && rad->dr->info == x))
            return rad;
        else
            if (x < rad->info && rad->st)
                search1 (rad->st, x);
             else
                if (x > rad->info && rad->dr)
                    search1 (rad->dr, x);
}

void deletex (nod *&rad, int x)
{
    nod *p, *r;
    if (x != rad->info)
    {
        p = search1 (rad, x);
        if (p->dr->info == x) r = p->dr;
            else r = p->st;
        if (!r->st && !r->dr)
        {
            if (p->dr->info == x) p->dr = NULL;
            else p->st = NULL;
            delete r;
        }
        else
            {
                if (r->st && !r->dr)
                {
                    if (p->dr == r) p->dr = r->st;
                    else p->st = r->st;
                    delete r;
                }
                if (!r->st && r->dr)
                {
                    if (p->dr == r) p->dr = r->dr;
                    else p->st = r->dr;
 //                   delete r;
                }
                if (r->st && r->dr)
                {
                    nod *q, *t;
                    int aux;
                    q = r->st;
                    while (q->dr)
                        q = q->dr;
                    t = search1(rad, q->info);
                    aux = r->info;
                    r->info = q->info;
                    q->info = aux;
                    t->dr = q->st;
                    delete q;
                }
            }
    }
    if (rad->info == x)
    {
        nod *q, *t;
        int aux;
        q = rad->st;
        while (q->dr->dr) q = q->dr;
        t = q->dr;
        aux = rad->info;
        rad->info = t->info;
        t->info = aux;
        q->dr = t->st;
        delete t;
    }

}

int main()
{
    nod *rad;
    int x;
    rad = new nod;
    rad = NULL;

    cout << "Dati primul nod al arborelui:";
    cin >> x;
    while (x)
    {
        insert (rad, x);
        cout << "Dati noul nod:";
        cin >> x;
    }

    SRD (rad);
    cout << endl;

    int y;
    cout << "Dati elementul pe care doriti sa il cautati:";
    cin >> y;
    cout << search (rad, y);
    cout << endl;

    cout << findMax (rad);
    cout << endl;

    cout << "Dati valoarea nodului pe care doriti sa il stergeti:";
    cin >> x;
    deletex(rad, x);

    cout << endl;
    SRD (rad);
    cout << endl;


    return 0;
}
