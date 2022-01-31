template<typename T, int N>
struct Matrix{
	T m[N][N];
	Matrix(){memset(m, 0LL, sizeof(m));}
	void add(T& a,const T& b)const{a+=b;a%=MOD;}//Change this
	T mul(const T& a,const T& b)const{return ((ll)a*(ll)b)%MOD;}// Change this
	Matrix operator*(const Matrix& other)const{
		Matrix c= Matrix();
		F0R(i,N)F0R(k,N)F0R(j,N) add(c.m[i][j], mul(m[i][k],other.m[k][j]));
		return c;
	}
};
using matrix = Matrix<int,2>; // Set this
matrix bin_pow(const matrix& c, ll n){
	if(n==1)return c;
	matrix m = bin_pow(c,n/2);
	return (n&1)?m*m*c:m*m;
}