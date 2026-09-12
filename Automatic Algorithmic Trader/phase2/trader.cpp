// This is your trader. Place your orders from here
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void merge(std::vector<int>& A,std::vector<int>& B, int l, int m, int r) {
    int a = m - l + 1;
    int b = r - m;
    int L[a];
    int R[b];
    int P[a];
    int Q[b];
    for (int i = 0; i < a; i++) {
        L[i] = A[l + i];
        P[i] = B[l + i];
    }
    for (int j = 0; j < b; j++) {
        R[j] = A[m + 1 + j];
        Q[j] = B[m + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < a && j < b) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            B[k] = P[i];
            i++;
        } 
        else {
            A[k] = R[j];
            B[k] = Q[j];
            j++;
        }
        k++;
    }
    while (i < a) {
        A[k] = L[i];
        B[k] = P[i];
        i++;
        k++;
    }
    while (j < b) {
        A[k] = R[j];
        B[k] = Q[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& A,std::vector<int>& B, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(A, B, l, m);
        mergeSort(A, B, m + 1, r);
        merge(A, B, l, m, r);
    }
}

int Median(std::vector<std::vector<std::pair<std::string,int>>> data, std::vector<std::pair<std::string,int>> stock){
    std::vector<int> prices;
    std::vector<int> quantities;
    int total=0;
    int x=0;
    int y=0;
    for(int i=0;i<data.size();i++){
        if(stock.size() == data[i].size()){
            int j;
            for(j=0;j<stock.size()-3;j++){
                int k;
                for(k=0;k<stock.size()-3;k++){
                    if(stock[j].first == data[i][k].first){
                        break;
                    }
                }
                if(k != stock.size()-3){
                    if(stock[j].second == data[i][k].second){
                        continue;
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
            }
            if(j != stock.size()-3){
                continue;
            }
            prices.push_back(data[i][data[i].size()-3].second);
            quantities.push_back(data[i][data[i].size()-2].second);
            total += data[i][data[i].size()-2].second;
        }
    }
    mergeSort(prices,quantities,0,prices.size()-1);
    if(total%2 == 0 && total != 0){
        total = total/2;
        while((total-quantities[y])>0){
            total = total-quantities[y];
            y++; 
        }
        if((total+1-quantities[y])<=0){
            x = prices[y];
        }
        else{
            x = ((prices[y]+prices[y+1])/2);
        }
    }
    else if(total%2 == 1){
        total = (total+1)/2;
        while((total-quantities[y])>0){
            total = total - quantities[y];
            y++;
        }
        x = prices[y];
    }
    return x;
}

int function(std::vector<std::pair<std::string,int>> curr, std::vector<std::vector<std::pair<std::string,int>>> data, std::vector<std::vector<int>> times, int i, int t, int bs){
int n = curr.size()+3;
    int j = i-1;
    while(j >= 0 ){
        while((n != data[j].size() ) || (( t > times[j][1]) && (times[j][1] != -1)) || (data[j][n-2].second == 0)){
            j--;
            if(j == -1) break;     
        }  
        if(j  == -1) return -1;  
        int p = 0;int a1=0,a2=0; bool flag = true;
        for(int k=0;k<n-3;k++){               
            if(bs == data[j][n-1].second ){  
                int f=0;  
                for(int d=0;d<n-3;d++) if(curr[k].first==data[j][d].first) {f=data[j][d].second;break;}
                if(f==0) {p=1;break;} 
                if(k==0) {a1 = curr[k].second; a2 = f;}
                else{
                    if(a1*f != a2*curr[k].second) flag = false;
                        a1 = curr[k].second; a2 = f; 
                    } 
                if(k != 0 && flag == false ) {p = 1;break;}
                if(a1*a2 < 0) {p = 1;break;} 
                
            }
            else{ 
                int f=0;
                for(int d=0;d<n-3;d++) if(curr[k].first==data[j][d].first) {f=data[j][d].second;break;}
                if(f==0) {p=1;break;}
                if(k==0) {a1 = curr[k].second; a2 = f;}
                else{
                    if(a1*f != a2*curr[k].second) flag = false;
                    a1 = curr[k].second; a2 = f; 
                } 
                if(k != 0 && flag == false ) {p = 1;break;}
                if(a1*a2 > 0) {p = 1;break;}
            }
        }
        if(p == 1) {j--;continue;}
        return j;
    }
    return -1;
}

void possible(std::vector<std::pair<std::string,int>> curr, std::vector<std::vector<std::pair<std::string,int>>> data, std::vector<std::vector<int>> times, int i, int t, int bs, std::vector<int> &temp){
int n = curr.size()+3;
    int j = i-1;
    while(j >= 0 ){
        while((( t > times[j][1]) && (times[j][1] != -1)) || (data[j][data[j].size()-2].second == 0)){
            j--;
            if(j == -1) break;      
        }  
        if(j  == -1) break;  
        if(bs == data[j][data[j].size()-1].second ){  
            int f=0;   
            for(int d=0;d<data[j].size()-3;d++) if(curr[0].first==data[j][d].first) {f=data[j][d].second;break;} 
            if(f*curr[0].second > 0) temp.push_back(j); 
        } 
        else{  
            int f=0;  
            for(int d=0;d<data[j].size()-3;d++) if(curr[0].first==data[j][d].first) {f=data[j][d].second;break;} 
            if(f*curr[0].second < 0) temp.push_back(j); 
        }
        j--;
    }
}

void f2(std::vector<std::vector<std::pair<std::string,int>>> &data,std::vector<std::pair<std::string,int>> curr, int &total_lines,int time,int j){
    int p = Median(data,curr);
    if(p==0) return; 
    if(curr[ curr.size()-1].second == 1) {if(p <= curr[ curr.size()-3].second) return;}
    else {if(p >= curr[ curr.size()-3].second) return;}

    std::cout<<time<<" 22B0946_22B1008 ";
    if( curr[ curr.size()-1].second == 1) std::cout<<"BUY ";
    else std::cout<<"SELL ";
    if(curr.size() != 4) for(int a=0; a < curr.size() -3;a++ ) std::cout<<curr[a].first<<" "<<curr[a].second<<" ";
    else std::cout<<curr[0].first<<" ";
    std::cout<<"$"<<p <<" #"<<curr[curr.size()-2].second<<" 0"<<std::endl;
    total_lines++;

    data[j][ data[j].size()-2 ].second = 0;
}

int reader(int time) {
    static std::vector<std::vector<std::pair<std::string,int>>> data;
	static std::vector<std::vector<int>> times;
	static int data_size = 0;
    static int total_lines = 1;
    static int l_index = 0;

    std::ifstream inputFile("output.txt");    
    std::string line;
    std::string token;
    std::vector<std::string> tokens;
    
    int i=0,nw = 0;
    while(i<total_lines){
        std::getline(inputFile, line);
        i++;
    }    

    while(true){
    nw = 0;
    if(!std::getline(inputFile, line)) break; 
    if(line == "!@") return 1;
    //tokenizers
    for (char i : line){
        if (i != ' ') {
            if( i !='$' && i != '#') token += i;
        }
        else{
            tokens.push_back(token);nw++;
            token = "";
        }
    }
    tokens.push_back(token);nw++;
    token ="";
    if(nw < 7) continue;
    if(l_index >= data.size()) {
    	data.resize(l_index *2+1);
        times.resize(l_index *2+1);
    }
    int a = 0;
    for(char c : tokens[nw-3]){
        if(c < '0' || c > '9') {a = 1;break;}
    }
    if(a == 1) {tokens.clear();continue;}
    for(char c : tokens[nw-2]){
        if(c < '0' || c > '9') {a = 1;break;}
    }
    if(a == 1) {tokens.clear();continue;}
    if(nw != 7 ) {
        if((nw-6)%2 != 0) {tokens.clear();continue;}
        for( int i=3 ; i< nw -3; i=i+2){
            for(char c : tokens[i+1]){
                if((c < '0' || c > '9') && c != '-') {a = 1; break;}
            }
            if(a == 1) break;
	    data[l_index].push_back(std::make_pair(tokens[i] , std::stoi(tokens[i+1]) ) );
	    }
        if(a == 1) {
            if(data[l_index].size() != 0){
                data.pop_back();
            }
            tokens.clear();continue;
        }
    }
    else data[l_index].push_back(std::make_pair(tokens[3] , 1 ) ); 
	data[l_index].push_back(std::make_pair("price" , std::stoi(tokens[nw-3]) ) ); 
    data[l_index].push_back(std::make_pair("quantity" , std::stoi(tokens[nw-2]) ) );
    times[l_index].push_back(std::stoi(tokens[0])) ;
    if(std::stoi(tokens[nw-1]) != -1) times[l_index].push_back(std::stoi(tokens[0]) + std::stoi(tokens[nw -1]) );
    else times[l_index].push_back(-1);
    if( tokens[2] == "SELL" ) data[l_index].push_back(std::make_pair("side" , 1 ) );
    else if( tokens[2] == "BUY" ) data[l_index].push_back(std::make_pair("side" , 2 )); 
    else {data.pop_back();times.pop_back();tokens.clear();continue;}
    
    tokens.clear();
    l_index ++;
    total_lines++;
    
    }
    data_size=l_index;
    //new inputs may be taken
    if(total_lines != i){
    //To find arbitrage and to print output continue
    int e = total_lines;
    for(int j = l_index -1 ; j >= l_index-e + i ; j--){ 
        std::vector<std::pair<std::string,int>> curr; 
        for (int i1=0;i1 < data[j].size()-3;i1 ++){
    		curr.push_back(std::make_pair( data[j][i1].first, data[j][i1].second ));
    	} 
        int f;
        if(data[j][data[j].size() -1].second == 1) f=2;
        else f=1;
        int z = function(curr,data,times,j,times[j][0],f);
        if(z == -1) { 
            std::vector<int> temp; 
            possible(curr,data,times,j,times[j][0],f,temp); 
            if(temp.size() == 0 ) { f2(data,data[j],total_lines,time,j);continue;} 
            
            for(int p=0;p<temp.size();p++){
                curr.clear();
                z = temp[p]; 
                int q, s = data[j][0].second; 
                if(s<0) s*= -1;
                std::string y;
                for(int i1=0;i1 < data[z].size()-3;i1 ++) if(data[j][0].first == data[z][i1].first) {q = data[z][i1].second;break;}       
                if(q<0) q*= -1;
                if(data[j][ data[j].size() -1 ].second == data[z][ data[z].size() -1 ].second){
                    for(int i1=1;i1 < data[j].size()-3;i1 ++) curr.push_back(std::make_pair( data[j][i1].first, data[j][i1].second*q )); 
                    for(int i1=0;i1 < data[z].size()-3;i1 ++) {
                        int e = 0, e1 = curr.size();
                        for(int i2=0;i2 < e1 ;i2 ++) if(curr[i2].first == data[z][i1].first) {e = i2;break;}
                        if(data[z][i1].first != data[j][0].first) {
                            if(e==0) {curr.push_back(std::make_pair( data[z][i1].first, data[z][i1].second*s )); y = data[z][i1].first;} 
                            else  curr[e].second += (data[z][i1].second*s); 
                        }
                    }
                }
                else{ 
                    for(int i1=1;i1 < data[j].size()-3;i1 ++) curr.push_back(std::make_pair( data[j][i1].first, data[j][i1].second*q )); 
                    for(int i1=0;i1 < data[z].size()-3;i1 ++) {
                        int e = 0, e1 = curr.size();
                        for(int i2=0;i2 < e1 ;i2 ++) if(curr[i2].first == data[z][i1].first) {e = i2;break;}
                        if(data[z][i1].first != data[j][0].first) {
                            if(e==0) {curr.push_back(std::make_pair( data[z][i1].first, (-1)*data[z][i1].second*s )); y = data[z][i1].first;} 
                            else curr[e].second -= (data[z][i1].second*s); 
                        }
                    }
                }
                std::vector<std::pair<std::string,int>> c;  
                for(int i1=0;i1 < curr.size();i1++) if(curr[i1].second != 0) c.push_back(std::make_pair( curr[i1].first, curr[i1].second )); 
                int g = function(c,data,times,j,times[j][0],f); 
                if(g==-1) continue;
                else{
                    int u,v;
                    int trades_g,trades_j,trades_z;
                    if(y.size() != 0 ){
                    for(int i1=0;i1 < data[g].size()-3;i1 ++) if(data[g][i1].first == y) {u = data[g][i1].second;break;}
                    for(int i1=0;i1 < data[z].size()-3;i1 ++) if(data[z][i1].first == y) {v = data[z][i1].second;break;} if(v<0) v*= -1;if(u<0) u*= -1;
                    trades_j = std::min( data[j][ data[j].size()-2].second*s*v, std::min(data[z][ data[z].size()-2].second * q*v , data[g][ data[g].size()-2].second * q*u ) );
                    trades_z = std::min( data[z][ data[z].size()-2].second*q*v, std::min(data[j][ data[j].size()-2].second * s*v , data[g][ data[g].size()-2].second * u*q  ) );
                    trades_g = std::min( data[g][ data[g].size()-2].second*q*u, std::min(data[z][ data[z].size()-2].second * v*q , data[j][ data[j].size()-2].second * v*s ) );
                    trades_j /= (s*v); trades_z /= (q*v);trades_g /= (q*u);
                    if(trades_j*s != trades_z*q || trades_z*v != trades_g*u){
                        if(trades_j*s <= trades_z*q && trades_j*s*u <= trades_g*q*v) {trades_z = trades_j*s/q; trades_g = trades_z*v/u;}
                        else if(trades_z*q <= trades_j*s && trades_z*v <= trades_g*u) {trades_j = trades_z*q/s; trades_g = trades_z*v/u;}
                        else {trades_z = trades_g*u/v; trades_j = trades_z*q/s; }
                    }}
                    else{
                    v = data[g][0].second;
                    for(int i1=0;i1 < data[j].size()-3;i1 ++) if(data[j][i1].first == data[g][0].first) {u = data[j][i1].second;break;}
                    if(v<0) v*= -1;if(u<0) u*= -1;
                    trades_j = std::min( data[j][ data[j].size()-2].second, std::min(data[z][ data[z].size()-2].second * q/s , data[g][ data[g].size()-2].second *v/u ) );
                    trades_z = std::min( data[z][ data[z].size()-2].second, std::min(data[j][ data[j].size()-2].second * s/q , data[g][ data[g].size()-2].second *v*s/(u*q)  ) );
                    trades_g = std::min( data[g][ data[g].size()-2].second, std::min(data[z][ data[z].size()-2].second * u*q/(s*v) , data[j][ data[j].size()-2].second *u/v ) );
                    if(trades_j*s != trades_z*q || trades_j*u != trades_g*v){
                        if(trades_j*s <= trades_z*q && trades_j*u <= trades_g*v) {trades_z = trades_j*s/q; trades_g = trades_j*u/v;}
                        else if(trades_z*q <= trades_j*s && trades_z*u*q <= trades_g*v*s) {trades_j = trades_z*q/s; trades_g = trades_j*u/v;}
                        else {trades_j = trades_g*v/u; trades_z = trades_j*s/q; }
                    }}
                    //profit or loss
                    int profit=0;
                    if(data[j][ data[j].size()-1].second == 2) profit += (trades_j*data[j][data[j].size()-3].second);
                    else  profit -= (trades_j*data[j][data[j].size()-3].second);
                    if(data[z][ data[z].size()-1].second == 2) profit += (trades_z*data[z][data[z].size()-3].second);
                    else  profit -= (trades_z*data[z][data[z].size()-3].second);
                    if(data[g][ data[g].size()-1].second == 2) profit += (trades_g*data[g][data[g].size()-3].second);
                    else  profit -= (trades_g*data[g][data[g].size()-3].second);
                    if(profit <= 0) continue;

                    int t1,t2,t3,t;
                    if(times[j][1] == -1 ) t1 = 10000; else t1 = times[j][1]+times[j][0] -time;
                    if(times[z][1] == -1 ) t2 = 10000; else t2 = times[z][1]+times[z][0] -time;
                    if(times[g][1] == -1 ) t3 = 10000; else t3 = times[g][1]+times[g][0] -time; 
                    t = std::min(t1,t2);
                    t = std::min(t,t3); 

                    std::cout<<time<<" 22B0946_22B1008 ";
                    if( data[j][ data[j].size()-1].second == 1) std::cout<<"BUY ";
                    else std::cout<<"SELL ";
                    if(data[j].size() != 4) for(int a=0; a < data[j].size() -3;a++ ) std::cout<<data[j][a].first<<" "<<data[j][a].second<<" ";
                    else std::cout<<data[j][0].first<<" ";
                    std::cout<<"$"<<data[j][data[j].size()-3].second<<" #"<<trades_j<<" "<<t<<std::endl;
        
                    std::cout<<time<<" 22B0946_22B1008 ";
                    if( data[z][ data[z].size()-1].second == 1) std::cout<<"BUY ";
                    else std::cout<<"SELL ";
                    if(data[z].size() != 4) for(int a=0; a < data[z].size() -3;a++ ) std::cout<<data[z][a].first<<" "<<data[z][a].second<<" ";
                    else std::cout<<data[z][0].first<<" ";
                    std::cout<<"$"<<data[z][data[z].size()-3].second<<" #"<<trades_z<<" "<<t<<std::endl;

                    std::cout<<time<<" 22B0946_22B1008 ";
                    if( data[g][ data[g].size()-1].second == 1) std::cout<<"BUY ";
                    else std::cout<<"SELL ";
                    if(data[g].size() != 4) for(int a=0; a < data[g].size() -3;a++ ) std::cout<<data[g][a].first<<" "<<data[g][a].second<<" ";
                    else std::cout<<data[g][0].first<<" ";
                    std::cout<<"$"<<data[g][data[g].size()-3].second<<" #"<<trades_g<<" "<<t<<std::endl;

                    data[j][ data[j].size()-2 ].second -= trades_j;
                    data[z][ data[z].size()-2 ].second -= trades_z;
                    data[g][ data[g].size()-2 ].second -= trades_g;
                    total_lines+=3; 
                }
            }
        } //median, calculations again check, improve for 3 quantity if possible,
        else{
        int q; if(data[j].size() == 4) {f2(data,data[j],total_lines,time,j);continue;} //think about it  
        for(int p=0;p<curr.size();p++) if(data[z][0].first == curr[p].first) q = curr[p].second;
        int w = data[z][0].second;
        if(q<0) q*= -1; if(w<0) w*= -1;
        int trades_j = std::min( data[j][ data[j].size()-2].second, data[z][ data[z].size()-2].second * w /q);
        int trades_z = std::min( data[z][ data[z].size()-2].second, data[j][ data[j].size()-2].second *q/ w);
        if(trades_j*q != trades_z*w){
            if(trades_j*q <= trades_z*w) trades_z = trades_j*q/w;
            else trades_j = trades_z*w/q;
        }

        int profit=0;
        if(data[j][ data[j].size()-1].second == 2) profit += (trades_j*data[j][data[j].size()-3].second);
        else  profit -= (trades_j*data[j][data[j].size()-3].second);
        if(data[z][ data[z].size()-1].second == 2) profit += (trades_z*data[z][data[z].size()-3].second);
        else  profit -= (trades_z*data[z][data[z].size()-3].second);
        if(profit <= 0) {f2(data,data[j],total_lines,time,j);continue;}

        int t;
        if(times[j][1]== -1 && times[z][1]==-1) t=-1;
        else if(times[j][1] == -1 ) t = times[z][1]+times[z][0] -time;
        else if(times[z][1] == -1 ) t = times[j][1]+times[j][0] -time;
        else t = std::min(times[z][1]+times[z][0], times[j][1]+times[j][0]) - time; 
        
        std::cout<<time<<" 22B0946_22B1008 ";
        if( data[j][ data[j].size()-1].second == 1) std::cout<<"BUY ";
        else std::cout<<"SELL ";
        if(data[j].size() != 4)for(int a=0; a < data[j].size() -3;a++ ) std::cout<<data[j][a].first<<" "<<data[j][a].second<<" ";
        else std::cout<<data[j][0].first<<" ";
        std::cout<<"$"<<data[j][data[j].size()-3].second<<" #"<<trades_j<<" "<<t<<std::endl;
        
        std::cout<<time<<" 22B0946_22B1008 ";
        if( data[z][ data[z].size()-1].second == 1) std::cout<<"BUY ";
        else std::cout<<"SELL ";
        if(data[z].size() != 4) for(int a=0; a < data[z].size() -3;a++ ) std::cout<<data[z][a].first<<" "<<data[z][a].second<<" ";
        else std::cout<<data[z][0].first<<" ";
        std::cout<<"$"<<data[z][data[z].size()-3].second<<" #"<<trades_z<<" "<<t<<std::endl;

        data[j][ data[j].size()-2 ].second -= trades_j;
        data[z][ data[z].size()-2 ].second -= trades_z;
        total_lines+=2; 
    }
    }
    }        
    return 0;
}

int trader(std::string *message)
{
    return 1;
}