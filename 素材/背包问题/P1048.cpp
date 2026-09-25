#include<bits/stdc++.h>
using namespace std ;
int ti[1005] , v[1005] ;
int f[1005] ;
int main()
{
    int t , m ;
    cin >> t >> m ;
    for(int i = 1 ; i <= m ; ++i)
        cin >> ti[i] >> v[i] ;
    for(int i = 1 ; i <= m ; ++i)
        for(int j = t ; j >= ti[i] ; --j)
            f[j] = max(f[j] , f[j - ti[i]] + v[i]) ;
    cout << f[t] ;
    return 0 ;
}
