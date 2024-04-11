#include<bits/stdc++.h>
using namespace std;
struct eight_puzzle{
    int cost;
    int hu;
    int time;
    string state;
    vector<string> path;
    eight_puzzle(int c,int h,int t,string s){
        cost=c;
        hu=h;
        time=t;
        state=s;
    }
    friend bool operator>(const eight_puzzle &a,const eight_puzzle &b){
        return (a.cost+a.hu!=b.cost+b.hu)?a.cost+a.hu>b.cost+b.hu:a.time>b.time;
    }
};
bool is_solve(string s){
    int cnt=0;
    for(int i=0;i<9;i++){
        if(s[i]=='0') continue;
        for(int j=i+1;j<9;j++){
            if(s[i]>s[j] && s[j]!='0') cnt++;
        }
    }
    if(cnt%2) return 0;
    return 1;
}
int catch_po(string s,char g){
    int po=0;
    for(int i=0;i<9;i++){
        if(s[i]==g){
            po=i;
            break;
        }
    }
    return po;
}
int can_move(string s){
    int mv=15;//up down left right
    int po=catch_po(s,'0');
    if(po<=2) mv-=8;
    if(po>=6) mv-=4;
    if(po%3==0) mv-=2;
    if(po%3==2) mv-=1;
    return mv;
}
vector<pair<string,string>> next_step(string in){
    int mv=can_move(in);
    string mv_n[4]={"up","down","left","right"};
    int  plu[4]={-3,3,-1,1};
    int po=catch_po(in,'0');
    vector<pair<string,string>> v;
    for(int i=3;i>=0;i--){
        if((mv>>i)&1){
            string s="move 0 to "+mv_n[3-i];
            swap(in[po],in[po+plu[3-i]]);
            v.push_back({s,in});
            swap(in[po],in[po+plu[3-i]]);
        }
    }
    return v;
}
int Manhattan_distance(string s){
    char a[9]={'1','2','3','4','5','6','7','8'};
    int cnt=0;
    for(int i=0;i<8;i++){
        int po=catch_po(s,a[i]);
        cnt+=abs(po/3-(i+1)/3)+abs(po%3-(i+1)%3);
    }
    return cnt;
}
void enqueue(priority_queue<eight_puzzle, vector<eight_puzzle>, greater<eight_puzzle>> &pq,eight_puzzle &tmp){
    pq.push(tmp);
}
eight_puzzle dequeue(priority_queue<eight_puzzle, vector<eight_puzzle>, greater<eight_puzzle>> &pq){
    if(pq.empty()){
        eight_puzzle p(0,0,0,"000000000");
        return p;
    }
    eight_puzzle p=pq.top();
    cout<<&p<<'\n';
    pq.pop();
    return p;
}
void bfs(string in){
    if(!is_solve(in)) cout<<"No solution!!\n";
    else if(in=="012345678") cout<<"It is the goal state.\n";
    else{
        priority_queue<eight_puzzle, vector<eight_puzzle>, greater<eight_puzzle>> pq;
        int cnt=0;
        eight_puzzle sta(0,Manhattan_distance(in),cnt++,in);
        enqueue(pq,sta);
        while(!pq.empty()){
            eight_puzzle st=pq.top();
            pq.pop();
            if(st.state=="012345678"){
                for(auto i:st.path){
                    cout<<i<<'\n';
                }
                break;
            }
            if(st.state=="000000000"){
                break;
            }
            vector<pair<string,string>> tmp=next_step(st.state);
            for(auto i:tmp){
                eight_puzzle tmp1(st.cost+1,Manhattan_distance(i.second),cnt++,i.second);
                for(auto j:st.path){
                    tmp1.path.push_back(j);
                }
                tmp1.path.push_back(i.first);
                enqueue(pq,tmp1);
            }
        }
    }
}
int main(){
    string s;
    cin>>s;
    bfs(s);
    return 0;
}
