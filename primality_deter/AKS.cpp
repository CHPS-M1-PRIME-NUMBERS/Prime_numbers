#include "AKS.hpp"

// cette fonction vérifie que n est un "perfect power", si cette fonction renvoie true n est composé sinon aks peut continuer a s'executer
bool is_perfect_power(unsigned int n)
{
								unsigned int b, a2;
								double a;
								unsigned int tmp;
								for (b=2; b <= log2(n); b++)
								{
																a = pow(n,1.0/b);
																if((a - (unsigned int)a) == 0) {
																								return true;
																}
								}
								return false;
}

unsigned int max ( unsigned int a,unsigned int b)
{
								if ( a > b )
								{
																return a;
								}
								else{
																return b;
								}
}

unsigned int find_r(unsigned int n)
{
								unsigned int maxk = floor(pow(log2(n),2));
								unsigned int maxr = max(ceil(pow(log2(n),5)),3);
								bool nextR = true;
								unsigned int r,k;
								for (r=2; nextR && (r < maxr); r++)
								{
																nextR=false;
																for(k=1; (!nextR) && (k <= maxk); k++)
																{
																								nextR=( (modpow(n,k,r) == 1) || (modpow(n,k,r) ==0));
																}
								}
								r--;
								return r;
}

unsigned int GCD(unsigned int a, unsigned int b){
								unsigned int r = 1;
								while(a%b != 0)
								{
																r = a%b;
																a = b;
																b = r;
								}
								return r;
}
unsigned int EulerPhi(unsigned int n)
{
								float res=n;
								unsigned int p;
								for ( p=2; (p*p) <= n; p++)
								{
																if(n%p ==0)
																{
																								while(n%p == 0)
																								{
																																n/= p;
																																res *= (1.0 - (1.0/(float)p));
																								}
																}
								}
								if (n >1)
																res *= (1.0 - (1.0/(float)n));
								return res;
}

bool step_5(unsigned int n, unsigned int r){
								unsigned int max = floor(sqrt(EulerPhi(r))*log2(n));
								CPolyMod p1(r, n); // x
								p1 = p1.Pow(n); // x^n

								unsigned int a;
								for (a = 1; a <= max; ++a) {
																CPolyMod p2(r, n); // x
																p2 -= a; // x - a
																p2 = p2.Pow(n); // (x - a)^n
																p2 += a; // (x - a)^n + a
																if (p1 != p2) {
																								return false;
																}
								}
								return true;
}

bool aks(unsigned int n)
{
								unsigned int r,i,gcd;
								if (is_perfect_power(n))
								{
																return false;
								}else{
																r=find_r(n);
																for(i=r; i > 1; i--)
																{
																								if ((gcd=GCD(i,n)) > 1 && gcd < n)
																								{
																																return false;
																								}
																}
																if ( n <= r )
																{
																								return true;
																}
																if (!step_5(n,r)) {
																								return false;
																}
								}
								std::cout<<n<<" prime"<<std::endl;
								return true;
}
