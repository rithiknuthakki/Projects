#include "market.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

market::market(int argc, char** argv)
{
    std::ifstream inputFile("output.txt");
    std::string line;
    std::string token;
    std::vector<std::string> tokens;
    int nw, o=1; int l_index=0;
    while (true) {
        nw=0;
        std::getline(inputFile, line);
        if(line == "!@") continue;
        if(line == "@!") break;
        if(o==1) {o=2;continue;}
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
        if(nw < 7) {tokens.clear();continue;}
        if(l_index >= data.size()) {
        	data.resize(l_index *2+1);
            time.resize(l_index *2+1);
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
        else data[l_index].push_back(std::make_pair(tokens[3] , 1 ) ); //std::cout<<tokens[nw-3]<<std::endl;
	    data[l_index].push_back(std::make_pair("price" , std::stoi(tokens[nw-3]) ) ); //std::cout<<tokens[nw-2]<<std::endl;
        data[l_index].push_back(std::make_pair("quantity" , std::stoi(tokens[nw-2]) ) );
        time[l_index].push_back(std::stoi(tokens[0])) ;
        if(std::stoi(tokens[nw-1]) != -1) time[l_index].push_back(std::stoi(tokens[0]) + std::stoi(tokens[nw -1]) );
        else time[l_index].push_back(-1);
        broker.push_back(tokens[1]);       
        if( tokens[2] == "SELL" ) data[l_index].push_back(std::make_pair("side" , 1 ) );
    	else if( tokens[2] == "BUY" ) data[l_index].push_back(std::make_pair("side" , 2 )); 
        else {data.pop_back();broker.pop_back();time.pop_back();tokens.clear();continue;}
                
        tokens.clear();
        l_index ++;
    } 
    data_size=l_index;
}

void market::start()
{   
    int Money_Transfered = 0;
    int num_trades = 0;
    int num_shares = 0;
    std::vector<std::pair<std::string,int>> Buy;
    std::vector<std::pair<std::string,int>> Sell; 
    std::vector<std::pair<std::string,int>> Profit;
    for(int i=1;i<data_size;i++){
        int n = data[i].size();
        int j = i-1; 
        std::vector<int> line;
        std::vector<int> price;
        std::vector<int> start;
        int bin = 0;
        int sin = 0;
        int pin = 0;
        while(j >= 0 ){
            while((data[i].size() != data[j].size()) || ((time[i][0] > time[j][1]) && (time[j][1] != -1)) || (data[i][n-1].second == data[j][n-1].second) || (data[j][n-2].second == 0)){
                j--;
                if(j == -1) break;
            }
            if(j  == -1) continue;
            int p = 0;
            for(int k=0;k<n-3;k++){
                int l;
                for(l=0;l<n-3;l++){
                    if(data[j][k].first == data[i][l].first){
                        break;
                    }
                }
                if(l != n-3){
                    if(data[j][k].second == data[i][l].second){
                       continue; 
                    }
                    else {p = 1;}
                }
                else {p = 1;}
                // if((data[i][k].first != data[j][k].first) || (data[i][k].second != data[j][k].second)) p = 1;
            }
            if(p == 1) {j--;continue;}
            price.push_back(data[j][n-3].second);
            line.push_back(j);
            start.push_back(time[j][0]);
            j--;
        }
        if(price.size() == 0) continue;
        int z = 0;
        if(data[i][n-1].second == 1){ 
            while(data[i][n-2].second != 0){
                int y=0;
                bool pin1 = false;
                bool pin2 = false;
                for(int x=0;x<price.size()-1;x++){
                    if(price[y] < price[x+1] || (price[y] == price[x+1] && start[y] > start[x+1]) || (price[y] == price[x+1] && start[y] == start[x+1] && broker[line[y]] > broker[line[x+1]])){
                        y = x+1;
                    }
                }
                j = line[y];
                if(price[y] < data[i][n-3].second){z = 1; break;}
                price[y] = -1;
                int exchange;
                if(data[i][n-2].second  < data[j][n-2].second){
                    exchange = data[i][n-2].second;
                    data[j][n-2].second -= data[i][n-2].second;
                    data[i][n-2].second = 0;
                }
                else{
                    exchange = data[j][n-2].second;
                    data[i][n-2].second -= data[j][n-2].second;
                    data[j][n-2].second = 0;
                }
                // if(broker[i] == broker[j]){
                //     if(data[i][n-3].second != data[j][n-3].second){
                //         continue;
                //     }
                // }
                std::cout<<broker[j]<<" purchased "<<exchange<<" share of ";
                if(n==4) std::cout<<data[i][0].first<<" ";
                else{
                    for(int t=0;t<n-3;t++) std::cout<<data[i][t].first<<" "<<data[i][t].second<<" ";
                }
                std::cout<<"from "<<broker[i]<<" for $"<<data[j][n-3].second<<"/share"<<std::endl;
                for(bin=0;bin<Buy.size();bin++){
                    if(Buy[bin].first == broker[j]){
                        Buy[bin].second += exchange;
                        break;
                    }
                }
                if(bin == Buy.size()){
                    Buy.push_back({broker[j],exchange});
                }
                for(sin=0;sin<Sell.size();sin++){
                    if(Sell[sin].first == broker[i]){
                        Sell[sin].second += exchange;
                        break;
                    }
                }
                if(sin == Sell.size()){
                    Sell.push_back({broker[i],exchange});
                }
                for(pin=0;pin<Profit.size();pin++){
                    if(Profit[pin].first == broker[j]){
                        pin1 = true;
                        Profit[pin].second -= exchange * data[j][n-3].second;
                    }
                    if(Profit[pin].first == broker[i]){
                        pin2 = true;
                        Profit[pin].second += exchange * data[j][n-3].second;
                    }
                }
                if(pin1 == false && pin2 == false && broker[i] == broker[j]){
                    pin1 = true;
                    pin2 = true;
                    Profit.push_back({broker[i],0});
                }
                if(pin1 == false){
                    Profit.push_back({broker[j],((-1)*exchange*data[j][n-3].second)});
                }
                if(pin2 == false){
                    Profit.push_back({broker[i],exchange*data[j][n-3].second});
                }
                Money_Transfered += exchange * data[j][n-3].second;
                num_trades++;
                num_shares += exchange;
            }
        }
        else if (data[i][n-1].second == 2){
            while(data[i][n-2].second != 0){
                int y=0;
                bool pin1 = false;
                bool pin2 = false;
                for(int x=0;x<price.size()-1;x++){
                    if(price[y] > price[x+1] || (price[y] == price[x+1] && start[y] > start[x+1]) || (price[y] == price[x+1] && start[y] == start[x+1] && broker[line[y]] > broker[line[x+1]])){
                        y = x+1;
                    }
                }
                j = line[y];
                if(price[y] > data[i][n-3].second){z = 1; break;}
                price[y] = data[i][n-3].second + 1 ;
                int exchange;
                if(data[i][n-2].second  < data[j][n-2].second){
                    exchange = data[i][n-2].second;
                    data[j][n-2].second -= data[i][n-2].second;
                    data[i][n-2].second = 0;
                }
                else{
                    exchange = data[j][n-2].second;
                    data[i][n-2].second -= data[j][n-2].second;
                    data[j][n-2].second = 0;
                }
                // if(broker[i] == broker[j]){
                //     if(data[i][n-3].second != data[j][n-3].second){
                //         continue;
                //     }
                // }
                std::cout<<broker[i]<<" purchased "<<exchange<<" share of ";
                if(n==4) std::cout<<data[i][0].first<<" ";
                else{
                    for(int t=0;t<n-3;t++) std::cout<<data[i][t].first<<" "<<data[i][t].second<<" ";
                }
                std::cout<<"from "<<broker[j]<<" for $"<<data[j][n-3].second<<"/share"<<std::endl;
                for(bin=0;bin<Buy.size();bin++){
                    if(Buy[bin].first == broker[i]){
                        Buy[bin].second += exchange;
                        break;
                    }
                }
                if(bin == Buy.size()){
                    Buy.push_back({broker[i],exchange});
                }
                for(sin=0;sin<Sell.size();sin++){
                    if(Sell[sin].first == broker[j]){
                        Sell[sin].second += exchange;
                        break;
                    }
                }
                if(sin == Sell.size()){
                    Sell.push_back({broker[j],exchange});
                }
                for(pin=0;pin<Profit.size();pin++){
                    if(Profit[pin].first == broker[i]){
                        pin1 = true;
                        Profit[pin].second -= exchange * data[j][n-3].second;
                    }
                    if(Profit[pin].first == broker[j]){
                        pin2 = true;
                        Profit[pin].second += exchange * data[j][n-3].second;
                    }
                }
                if(pin1 == false && pin2 == false && broker[i] == broker[j]){
                    pin1 = true;
                    pin2 = true;
                    Profit.push_back({broker[i],0});
                }
                if(pin1 == false){
                    Profit.push_back({broker[i],((-1)*exchange*data[j][n-3].second)});
                }
                if(pin2 == false){
                    Profit.push_back({broker[j],exchange*data[j][n-3].second});
                }
                Money_Transfered += exchange * data[j][n-3].second;
                num_trades++;
                num_shares += exchange;
            }
        }
        price.clear();
        line.clear();
        start.clear();
        if(z == 1){continue;}
    }
    std::cout<<std::endl<<"---End of Day---"<<std::endl;
    std::cout<<"Total Amount of Money Transferred: $"<<Money_Transfered<<std::endl;
    std::cout<<"Number of Completed Trades: "<<num_trades<<std::endl;
    std::cout<<"Number of Shares Traded: "<<num_shares<<std::endl;
    for(int i=0;i<Profit.size();i++){
        int bout=0,sout=0;
        for(bout=0;bout<Buy.size();bout++){
            if(Buy[bout].first == Profit[i].first){
                break;
            }
        }
        for(sout=0;sout<Sell.size();sout++){
            if(Sell[sout].first == Profit[i].first){
                break;
            }
        }
        std::cout<<Profit[i].first<<" bought ";
        if(bout == Buy.size()){
            std::cout<<"0";
        }
        else{
            std::cout<<Buy[bout].second;
        } 
        std::cout<<" and sold ";
        if(sout == Sell.size()){
            std::cout<<"0";
        }
        else{
            std::cout<<Sell[sout].second;
        }
        std::cout<<" for a net transfer of $"<<Profit[i].second<<std::endl; 
    }
    for(int i=0;i<broker.size();i++){
        int j;
        for(j=0;j<Profit.size();j++){
            if(broker[i] == Profit[j].first){
                break;
            }
        }
        if(j == Profit.size()){
            std::cout<<broker[i]<<" bought 0 and sold 0 for a net transfer of $0"<<std::endl;
        }
    }
}