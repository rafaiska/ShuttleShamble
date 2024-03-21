#include <iostream>
#include <vector>

class Passoca
{
    public:
        int a;
        int b;
        int c;
        Passoca(int a, int b, int c) {this-> a = a; this-> b = b; this-> c = c;}
};

void probe(std::vector<Passoca*>& vv)
{
    for (Passoca* pp: vv)
    {
        pp->a += 1;
        pp->b += 2;
        pp->c += 3;
        std::cout << pp->a << pp->b << pp->c << '\n';
    }
}

int main(int argc, char* argv[])
{
    std::vector<Passoca*> v;

    v.push_back(new Passoca(1, 2, 3));
    v.push_back(new Passoca(4, 5, 6));
    v.push_back(new Passoca(7, 8, 9));

    probe(v);

    for (Passoca* p: v)
    {
        std::cout << p->a << p->b << p->c << '\n';
        delete p;
    }
    v.clear();

    return 0;
}