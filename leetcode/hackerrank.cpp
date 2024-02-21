#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


#define ll long long int
ll INF = LONG_MAX/1000;

pair<ll,ll> calcLiftTime(int n, int i, int e1, int t1){
    ll time = 0;
    time = (t1 * i);
    ll energy = (t1 * i);
    return {time, energy};
}

ll calcStairsTime(int n, int i, int e2, int c, int energy){
    ll time = 0;
    for(int j = i; j < n; j++){
        double tt = ((double)c/(double)energy);
        time += (ll)ceil(tt);
        energy -= e2;
        if(energy < 0 && j < n)
        {
            return INF;
        }
    }
    
    return (ll)time;
}

long getMinDifference(int n, int e1, int t1, int e2, int c) {
    int l = 0, r = n;
    ll ans = n * e1;
    
    while(l <= r){
        int mid = (l + r)/2;
        pair<ll,ll>p = calcLiftTime(n, mid, e1, t1);
        ll liftTime = p.first;
        ll energy = p.second;
        ll stairsTime = calcStairsTime(n, mid, e2, c, energy);
        cout<<mid<<" "<<liftTime<<" "<<energy<<" "<<stairsTime<<endl;

        if(stairsTime == INF){
            l = mid + 1;
        }
        else if(ans == n * e1 || abs(liftTime - stairsTime) >= ans){
            ans = min(ans, abs(stairsTime - liftTime));
            r = mid - 1;
        }
        else
        {
            ans = abs(liftTime - stairsTime);
            l = mid + 1;
        }
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string e1_temp;
    getline(cin, e1_temp);

    int e1 = stoi(ltrim(rtrim(e1_temp)));

    string t1_temp;
    getline(cin, t1_temp);

    int t1 = stoi(ltrim(rtrim(t1_temp)));

    string e2_temp;
    getline(cin, e2_temp);

    int e2 = stoi(ltrim(rtrim(e2_temp)));

    string c_temp;
    getline(cin, c_temp);

    int c = stoi(ltrim(rtrim(c_temp)));

    long result = getMinDifference(n, e1, t1, e2, c);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

/*
6
20
20
4
5
*/