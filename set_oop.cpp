#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

class Multime
{
    public:
        Multime(){
            card = 0;
        }
        
        void vect_mult()
        {
            if(card==0) return;
            
            int *X,cardX = 0;
            sort(M,M+card);
            
            cardX++; // elem 1
            for(int i=1;i<card;i++)
                if(M[i] != M[i-1]) cardX++;
                
            X = (int*)malloc(sizeof(int) * cardX);
            X[0] = M[0];cardX = 1;
            
            for(int i=1;i<card;i++)
                if(M[i] != M[i-1]) X[cardX++] = M[i];
                
            free(M);
            M = X;
            card = cardX;
        }
        
        friend istream &operator>> (istream &in, Multime &D)
        {
            //cout<<"Cardinalul:";
            in>>D.card;
            D.M = (int*)malloc(sizeof(int) * D.card);
            
            for(int i = 0;i < D.card; ++i)
                in>>D.M[i];
            
            D.vect_mult();
            
            return in;
        }
        
        friend ostream &operator<< (ostream &out, Multime &D)
        {
            out<<D.card<<"\n";
            
            for(int i = 0;i < D.card; ++i)
                out<<D.M[i]<<" ";
            
            out<<"\n";
            return out;
        }
        
        Multime operator+(Multime& A) {
            Multime B;
            int i;
            
            B.card = this->card + A.card;
            
            B.M = (int*)malloc(sizeof(int) * B.card);
            for(i=0;i < this->card;++i)
                B.M[i] = this->M[i];
            
            for(;i < B.card;++i)
                B.M[i] = A.M[i - this->card];
            
            B.vect_mult();
            return B;
        }
        
        Multime operator*(Multime& A) {
            Multime B,C;
            int i;
            
            B.card = this->card + A.card;
            
            B.M = (int*)malloc(sizeof(int) * B.card);
            for(i=0;i < this->card;++i)
                B.M[i] = this->M[i];
            
            for(;i < B.card;++i)
                B.M[i] = A.M[i - this->card];
            
            sort(B.M,B.M + B.card);
            
            for(i=1;i<B.card;++i)
                if(B.M[i] == B.M[i-1]) C.card++;
            
            C.M = (int*)malloc(sizeof(int) * C.card);
            C.card = 0;
            
            for(i=1;i<B.card;++i)
                if(B.M[i] == B.M[i-1]) C.M[card++] = B.M[i];
            
            return C;
        }

        Multime operator-(Multime &A) {
        	map<int, bool> T;
        	Multime B;
        	int i;

        	for(i=0;i<A.card;i++)
        		T.insert(make_pair(A.M[i],true));

        	for(i=0;i<this->card;++i)
        		if(T.find(this->M[i]) == T.end())
        			B.card++;

        	B.M = (int*)malloc(sizeof(int) * B.card);
        	B.card = 0;

        	for(i=0;i<this->card;++i)
        		 if(T.find(this->M[i]) == T.end())
        			B.M[B.card++] = this->M[i];

        	return B;
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

		friend istream &operator>> (istream &in,Pereche &P)
        {
        	in>>P.first>>P.second;

        	return in;
        }

        friend ostream &operator<< (ostream &out,Pereche &P){
        	out<<P.first<<" "<<P.second<<"\n";

        	return out;
        }

	private:
		int first;
		int second;
};

class Multime_Pereche{
	public:
		Multime_Pereche(){
			card = 0;
		}

		void insert_per(Pereche p)
		{
			int i;
			for(i = 0;i < card;++i)
				if(Mul_Per[i].first == p.first &&
				   Mul_Per[i].second == p.second) return;

			Mul_Per = (Pereche*)realloc(sizeof(Pereche) * (++card));
			Mul_Per[card-1] = p;
		}

		friend istream &operator>> (istream &in, Multime_Pereche &A)
		{
			in>>A.card;
            A.Mul_Per = (Pereche*)malloc(sizeof(Pereche) * A.card);
            
            for(int i = 0;i < A.card; ++i)
                in>>A.Mul_Per[i];
            
        	///TO DO vec_mult function
            
            return in;
		}

		friend ostream &operator<< (ostream out, Multime_Pereche &A)
		{
			out<<A.card<<"\n";
            
            for(int i = 0;i < A.card; ++i)
                out<<A.Mul_Per[i].first<<" "<<A.Mul_Per[i].second<<"\n";
            
        	///TO DO vec_mult function
            
            return out;
		}

	private:
		Pereche *Mul_Per;
		int card;
};

Multime_Pereche prod_cartezian(Multime A, Multime B)
{
	Multime_Pereche C;

	for(int i=0;i < A.card;++i)
		for(int j=0;j < B.card;++j)
		{
			Pereche p(A.M[i], B.M[j]);
			C.insert_per(p);
		}

	return C;
}

int main()
{
    Multime A,B;
    cin>>A>>B;
    Multime C = A * B;
    cout<<C;
}
