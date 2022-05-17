#include<bits/stdc++.h>
using namespace std;

int main(){
    int N; cin >> N;
    vector<double> a(N),b(N),c(N),d(N);
    for(int _=0; _<2; _++){
        for(int i=0; i<N; i++) cin >> a[i] >> b[i];
        int x = 0, y = 0;
        for(int i=0; i<N; i++){
            x += a[i];
            y += b[i];
            a[i] *= N;
            b[i] *= N;
        }
        for(int i=0; i<N; i++){
            a[i] -= x;
            b[i] -= y;
        }
        swap(a,c);
        swap(b,d);
    }
    for(int i=0; i<N; i++){
        if(a[i]!=0 || b[i]!=0){
            swap(a[i],a[0]);
            swap(b[i],b[0]);
        }
    }
    string ans = "No";
    const double eps = 1e-6;
    for(int i=0; i<N; i++){
        double angle = atan2(d[i],c[i])-atan2(b[0],a[0]);
        bool flag = true;
        for(int j=0; j<N; j++){
            double A = a[j]*cos(angle)-b[j]*sin(angle);
            double B = a[j]*sin(angle)+b[j]*cos(angle);
            bool flag2 = false;
            for(int k=0; k<N; k++){
                if(std::abs(A-c[k])<=eps && std::abs(B-d[k])<=eps) flag2 = true;
            }
            flag &= flag2;
        }
        if(flag) ans = "Yes";
    }
    cout << ans << endl;
}
