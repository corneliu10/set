#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdio>

using namespace std;

class Multime
{
public:
    Multime(){
        card = 0;
    }

    Multime(const Multime &A) {
        card = A.card;

        M = new int [card];

        for(int i = 0;i < card; ++i)
            M[i] = A.M[i];
    }

    ~Multime() {
        if(card==1)
            delete M;
        else
            delete[] M;
    }

    void vect_mult()
    {
        if(card==0) return;

        int *X,cardX = 0;
        sort(M,M+card);

        cardX++; // elem 1
        for(int i=1;i<card;i++)
            if(M[i] != M[i-1]) cardX++;

        X = new int [cardX]; //(int*)malloc(sizeof(int) * cardX);
        X[0] = M[0];cardX = 1;

        for(int i=1;i<card;i++)
            if(M[i] != M[i-1]) X[cardX++] = M[i];
        
        delete[] M;
        M = X;
        card = cardX;
    }

    friend istream &operator>> (istream &in, Multime &D)
    {
        //cout<<"Cardinalul:";
        if(D.card > 0)
            delete[] D.M;
            
        in>>D.card;
        D.M = new int [D.card]; //(int*)malloc(sizeof(int) * D.card);

        for(int i = 0;i < D.card; ++i)
            in>>D.M[i];

        D.vect_mult();

        return in;
    }

    friend ostream &operator<< (ostream &out, Multime &D)
    {
        if(D.card == 0)
        {
            out<<"{}\n";

            return out;
        }

        out<<D.card<<"\n{";

        for(int i = 0;i < D.card - 1; ++i)
            out<<D.M[i]<<",";

        out<<D.M[D.card - 1];

        out<<"}\n";
        return out;
    }

    Multime operator+(const int x) {
        Multime B;
        int i;

        B.card = this->card + 1;
        B.M = new int [B.card];

        for(i=0;i < this->card;++i)
            B.M[i] = this->M[i];

        B.M[i] = x;

        B.vect_mult();

        return B;
    }

    Multime operator+(const Multime& A) {
        Multime B;
        int i;

        B.card = this->card + A.card;

        B.M = new int [B.card]; //(int*)malloc(sizeof(int) * B.card);
        for(i=0;i < this->card;++i)
            B.M[i] = this->M[i];

        for(;i < B.card;++i)
            B.M[i] = A.M[i - this->card];

        B.vect_mult();
        return B;
    }

    Multime operator*(const Multime& A) {
        Multime B,C;
        int i;

        B.card = this->card + A.card;

        B.M = new int [B.card]; //(int*)malloc(sizeof(int) * B.card);
        for(i=0;i < this->card;++i)
            B.M[i] = this->M[i];

        for(;i < B.card;++i)
            B.M[i] = A.M[i - this->card];

        sort(B.M,B.M + B.card);

        for(i=1;i<B.card;++i)
            if(B.M[i] == B.M[i-1]) C.card++;

        C.M = new int [C.card]; //(int*)malloc(sizeof(int) * C.card);
        C.card = 0;

        for(i=1;i<B.card;++i)
            if(B.M[i] == B.M[i-1]) C.M[C.card++] = B.M[i];

        return C;
    }

    Multime operator-(const Multime &A) {
        Multime B;
        int i, j;
        bool gas;

        for(i = 0;i < this->card; i++) {
            gas = true;
            for(j = 0;j < A.card; j++)
                if(A.M[j] == this->M[i]) {
                    gas = false;
                    break;
                }

            if(gas) B.card++;
        }


        B.M = new int [B.card];
        B.card = 0;

        for(i = 0;i < this->card; i++) {
            gas = true;
            for(j = 0;j < A.card; j++)
                if(A.M[j] == this->M[i]) {
                    gas = false;
                    break;
                }

            if(gas) B.M[B.card++] = this->M[i];
        }

        return B;
    }

    Multime& operator=(const Multime &A) {
        delete[] M;
        card = A.card;

        M = new int [card];
        for(int i=0;i < card; ++i)
            M[i] = A.M[i];
        
        return *this;
    }

    bool operator==(const Multime &A) const{
        if(card != A.card) return false;

        for(int i=0; i < card;++i)
            if(M[i] != A.M[i]) return false;

        return true;
    }

    bool operator!=(const Multime &A)  const{
        if(card != A.card) return true;

        for(int i=0;i < card;++i)
            if(A.M[i] != M[i]) return true;

        return false;
    }

    bool operator<(const Multime &A) const {
        if(card < A.card) return false;
        else return true;
    }

    int get_card()
    {
        return card;
    }

    /*int get_M_elem(int i)
    {
        if(card > i)
            return M[i];
        else
            return -1;
    }*/
    
    int &operator[](int i) {
        if(i < 0 || i >= card)
            throw std::invalid_argument("index out of range");
        else
            return M[i];
    }

private:
    int *M;
    int card;
};

class Pereche{

public:
    Pereche(){
        first = 0;
        second = 0;
    }

    Pereche(int x, int y){
        first = x;
        second = y;
    }

    Pereche(const Pereche &P) {
        first = P.first;
        second = P.second;
    }

    ~Pereche() {

    }

    friend istream &operator>> (istream &in,Pereche &P)
    {
        int x,y;
        in>>x>>y;

        P.set_first(x); P.set_second(y);
        return in;
    }

    friend ostream &operator<< (ostream &out,Pereche &P){
        out<<"("<<P.get_first()<<","<<P.get_second()<<")\n";

        return out;
    }

    void operator=(const Pereche &P)
    {
        first = P.first;
        second = P.second;
    }

    bool operator==(const Pereche &P) {
        if(first != P.first) return false;
        if(second != P.second) return false;

        return true;
    }

    bool operator!=(const Pereche &P) {
        if((*this) == P) return false;

        return true;
    }

    bool operator<(const Pereche &P) {
        if(first < P.first) return true;
        else if(first == P.first && second < P.second) return true;
        else return false;
    }

    void set_first(int x)
    {
        first = x;
    }

    void set_second(int x)
    {
        second = x;
    }

    int get_first()
    {
        return first;
    }

    int get_second()
    {
        return second;
    }

private:
    int first;
    int second;
};

class Multime_Pereche{
    friend class Pereche;

public:

    Multime_Pereche ()
    {

    }

    Multime_Pereche (int n)
    {
        Mul_Per = new Pereche [n];
        card = n;
    }

    Multime_Pereche(const Multime_Pereche &A) {
        card = A.card;
        Mul_Per = new Pereche [card];

        for(int i = 0;i < card; ++i) {
            Mul_Per[i] = A.Mul_Per[i];
        }
    }

    ~Multime_Pereche() {
        delete [] Mul_Per;
    }
    
    /*void mult()
    {
        if(card==0) return;

        Pereche *X;
        int cardX = 0;
        //sort(M,M+card);

        cardX++; // elem 1
        for(int i=1;i<card - 1;i++)
            for(int j=i+1;j<card;j++)
            if(Mul_Per[i] != Mul_Per[j]) cardX++;

        X = new int [cardX]; //(int*)malloc(sizeof(int) * cardX);
        X[0] = M[0];cardX = 1;

        for(int i=1;i<card;i++)
            if(M[i] != M[i-1]) X[cardX++] = M[i];
        
        delete[] M;
        M = X;
        card = cardX;
    }*/

    friend istream &operator>> (istream &in, Multime_Pereche &A)
    {
        Pereche x;
        int n;
        in>>n;
        
        //A.Mul_Per = (Pereche*)malloc(sizeof(Pereche) * A
        if(A.card > 0)
            delete[] A.Mul_Per;
            
        A.Mul_Per = new Pereche [A.card];

        for(int i = 0;i < n; ++i)
        {
            in>>x;
            A.Mul_Per[i] = x;
        }

        ///TO DO vec_mult function

        return in;
    }

    friend ostream &operator<< (ostream &out, Multime_Pereche &A)
    {
        out<<A.card<<"\n";

        for(int i = 0;i < A.card; ++i)
            out<<"("<<A.Mul_Per[i].get_first()<<","<<A.Mul_Per[i].get_second()<<")\n";

        ///TO DO vec_mult function

        return out;
    }

    void operator= (const Multime_Pereche &A) {
        delete[] Mul_Per;

        card = A.card;
        Mul_Per = new Pereche [card];

        for(int i = 0;i < card; ++i)
            Mul_Per[i] = A.Mul_Per[i];

    }

    bool operator==(const Multime_Pereche &A) {
        if(card != A.card) return false;

        for(int i=0; i < card;++i)
            if(Mul_Per[i] != A.Mul_Per[i]) return false;

        return true;
    }

    bool operator!=(const Multime_Pereche &A) {
        if((*this) == A) return false;

        return true;
    }

    /* set_per(int i,Pereche x)
    {
        Mul_Per[i] = x;
    }*/
    
    Pereche &operator[](int i) {
        if(i < 0 || i >= card)
            throw std::invalid_argument("index out of range");
        else
            return Mul_Per[i];
    }

private:
    int card;
    Pereche *Mul_Per;
};

Multime_Pereche prod_cartezian(Multime A, Multime B)
{
    int ct = 0;
    Multime_Pereche C(A.get_card() * B.get_card());

    for(int i=0;i < A.get_card();++i)
        for(int j=0;j < B.get_card();++j)
        {
            Pereche p(A[i], B[j]);
            C[ct++] = p;
        }

    return C;
}

int main()
{
    freopen("data.in","r",stdin);
    //freopen("date.out","w",stdout);

    Multime A,B;
    cin>>A>>B;

    int x = 15;

    Multime C = A + x;
    cout<<"AUx:\n"<<C;

    C = A * B;
    cout<<"A intersectat cu B:\n"<<C;

    cout << "A == (A-B) U (A*B) ? " << (A == (A - B) + (A * B)) << "\n";

    C = A - B;
    cout<<"A - B:\n"<<C;

    C = B - A;
    cout<<"B - A:\n"<<C;

    Multime_Pereche mp = prod_cartezian(A,B);

    cout<<"AxB:\n"<<mp;

    return 0;
}
