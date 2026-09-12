#include <vector>
#include "receiver.h"

void linear_comb( std::vector<std::vector<std::pair<std::string,int>>> data, std::vector<std::pair<std::string,int>> curr, std::vector<int> used, std::vector<std::pair<int,std::vector<int>>> &possible, std::vector<int> temp, int n){
	
	bool g = true;
	int w=n;
	while( g ){
    		w--;
    	     	g=false;
    	     	for(int i=0; i< used.size(); i++) { if(w == used[i]) g=true;}
    	}
    	
	if(w>=0) linear_comb(data, curr, used, possible, temp, w );
	int y1,y2,y3,e;

	for(const auto& pair : curr) { if( pair.first == "side" ) y1 = pair.second; }
	for(const auto& pair : data[n]) { if( pair.first == "side" ) y2 = pair.second; }
	if(y1 == y2){
		for (const auto& pair : data[n]) {
        		if(pair.first != "side"){
        		for( e= 0; e< curr.size();e++) { if( curr[e].first == pair.first ) break; }
        		if(e != curr.size()) curr[e].second += pair.second;
    			else {curr.push_back(std::make_pair(pair.first,pair.second));} 
    		}
    		}
	}
	else{
		for (const auto& pair : data[n]) {
        		if(pair.first != "side"){
        		for( e= 0; e< curr.size();e++) { if( curr[e].first == pair.first ) break; }
        		if(e != curr.size()) curr[e].second -= pair.second;
    			else curr.push_back(std::make_pair(pair.first,-pair.second));
    		}}
	} 
	temp.push_back(n);	
	if(w>=0) linear_comb(data, curr, used, possible, temp, w ); 	
	bool flag1,flag = true; flag1 = false;
	for (const auto& pair : curr) {
		flag1 = true;
        	if(pair.first != "side" && pair.first != "price"){
        		if(pair.second != 0) flag = false; 	
        	}
    	} 
	if(flag && flag1){  
		int size = temp.size();int z1,z2;
		for(const auto& pair : curr) { if( pair.first == "price" ) z1 = pair.second; }
         	possible.push_back(std::make_pair(0, std::vector<int>{}));
         	z2 = possible.size()-1;
         	possible[z2].first = z1;
         	possible[z2].second.resize(size);
		for(int i=0; i<size; i++){			    
			 possible[z2].second[i] = temp[i];	 			
		}	
	}
}

void check_cancellation( std::vector<std::vector<std::pair<std::string,int>>> data, std::vector<std::pair<std::string,int>> curr, std::vector<int> &used, int n, int &l){
	
	bool g = true;
	int w = n;
	while( g ){
    		w--;
    	    g=false;
    	 	for(int i=0; i< used.size(); i++) { if(w == used[i]) g=true;}
    }
	int y1,y2,y3,k1;
	for(const auto& pair : curr) { if( pair.first == "side" ) y1 = pair.second; }
	for(const auto& pair : data[n]) { if( pair.first == "side" ) y2 = pair.second; }
	if( y1 == y2){
			bool flag = true;
    		for(const auto& pair : data[n]) {
	    	for(const auto& pair1 : curr) { if( pair1.first == pair.first ) y3 = pair1.second; }
	    	if(pair.first != "side" && pair.first != "price"){
        		if( pair.second != y3 ) flag = false; 	
        	}
			if(pair.first == "price") {
				if(y1 == 2){ //if k1 == -1 change l to n and return else dont change l and push that n to used and return;
					if(pair.second > y3) k1 = -1; 
					else k1 = 1;
				}
				else{
					if(pair.second < y3) k1 = -1; 
					else k1 = 1;
				}
			}
			}
    		for (const auto& pair : curr) {
    		for(const auto& pair1 : data[n]) { if( pair1.first == pair.first ) y3 = pair1.second; }
	    	if(pair.first != "side" && pair.first != "price"){
        		if( pair.second != y3 ) flag = false; 	
        	}
    		}
    		if(flag){
				if(k1 == -1) {l = 0;return;} 
				else used.push_back(n); 
			}
	}
	if(w>=0) check_cancellation( data, curr, used, w, l );	
	if( y1 != y2 && l == -1 ){      	
    		bool flag = true;
    		for (const auto& pair : data[n]) {
	    	for(const auto& pair1 : curr) { if( pair1.first == pair.first ) y3 = pair1.second; }
	    	if(pair.first != "side"){
        		if( pair.second != y3 ) flag = false; 	
        	}
    		}
    		for (const auto& pair : curr) {
    		for(const auto& pair1 : data[n]) { if( pair1.first == pair.first ) y3 = pair1.second; }
	    	if(pair.first != "side"){
        		if( pair.second != y3 ) flag = false; 	
        	}
    		}
    		if(flag) {l = n; used.push_back(l); return;}
    	}
}

void linear_comb3( std::vector<std::vector<std::pair<std::string,int>>> data, std::vector<std::pair<std::string,int>> curr, std::vector<std::pair<int,std::vector<int>>> &possible, std::vector<int> temp, int n){
	
	int w = n-1;
	while( w >= 0 && data[w][ data[w].size() -2 ].second == 0 ) w--;
	if(w>=0) linear_comb3(data, curr, possible, temp, w );
	
	temp.push_back(n);
	temp.push_back(0);
	int t_index = temp.size()-1;
	int a2 = data[n].size(); 
	int a1 = data[n][ a2 -2 ].second;  
	for(int x = 0 ; x < a1 ; x++){
		
		int y1,y2,y3,e;
		for(const auto& pair : curr) { if( pair.first == "side" ) y1 = pair.second; }
		for(const auto& pair : data[n]) { if( pair.first == "side" ) y2 = pair.second; }
		if(y1 == y2){
			for (const auto& pair : data[n]) {
				if(pair.first != "side" && pair.first != "number"){
				for( e= 0; e< curr.size();e++) { if( curr[e].first == pair.first ) break; }
				if(e != curr.size()) curr[e].second += pair.second;
	    			else {curr.push_back(std::make_pair(pair.first,pair.second));} 
	    		}
	    		}
		}
		else{
			for (const auto& pair : data[n]) {
				if(pair.first != "side" && pair.first != "number"){
				for( e= 0; e< curr.size();e++) { if( curr[e].first == pair.first ) break; }
				if(e != curr.size()) curr[e].second -= pair.second;
	    			else curr.push_back(std::make_pair(pair.first,-pair.second));
	    		}}
		} 	
			
		temp[t_index]++;
		if(w>=0) linear_comb3(data, curr, possible, temp, w );	
		bool flag1,flag = true; 
		flag1 = false;
		for (const auto& pair : curr) {
			flag1 = true;
        		if(pair.first != "side" && pair.first != "price" && pair.first != "number"){
        			if(pair.second != 0) flag = false; 	
        		}
    		}
		if(flag && flag1){	
			int size = temp.size();int z1,z2;
			for(const auto& pair : curr) { if( pair.first == "price" ) z1 = pair.second; }
		 	possible.push_back(std::make_pair(0, std::vector<int>{}));
		 	z2 = possible.size()-1;
		 	possible[z2].first = z1;
		 	possible[z2].second.resize(size);
			for(int i=0; i<size; i++){			    
				 possible[z2].second[i] = temp[i]; 	 			
			}		
		}
	}
}

void check_cancellation3( std::vector<std::vector<std::pair<std::string,int>>> &data, std::vector<std::pair<std::string,int>> &curr, int n, int l_index){
	
	int w = n-1;
	while( w >= 0 && data[w][ data[w].size() -2 ].second == 0 ) w--;
	
	int y1,y2,y3;
	for(const auto& pair : curr) { if( pair.first == "side" ) y1 = pair.second; }
	for(const auto& pair : data[n]) { if( pair.first == "side" ) y2 = pair.second; }
	if( y1 != y2 ){      	
    		bool flag = true;
    		for (const auto& pair : data[n]) {
	    	for(const auto& pair1 : curr) { if( pair1.first == pair.first ) y3 = pair1.second; }
	    	if(pair.first != "side" && pair.first != "number"){
        		if( pair.second != y3 ) flag = false; 	
        	}
    		}
    		for (const auto& pair : curr) {
    		for(const auto& pair1 : data[n]) { if( pair1.first == pair.first ) y3 = pair1.second; }
	    	if(pair.first != "side" && pair.first != "number"){
        		if( pair.second != y3 ) flag = false; 	
        	}
    		}
    		int b = data[l_index].size() -2;int c = data[n].size() -2;
    		for(int d = 0; d<curr.size();d++){ if( curr[d].first == "number") y3 = d;}
    		if(flag) { 
    			if( data[l_index][b].second > data[n][c].second ){
    				data[l_index][b].second -= data[n][c].second;
    				data[n][c].second = 0;
					curr[y3].second = data[l_index][b].second; 
    			}
    			else{
    				data[n][c].second -= data[l_index][b].second;
    				data[l_index][b].second = 0;
					curr[y3].second = 0; 	
    			}	
    			return;
    		}
    	}
		else{      	
    		bool flag = true;
    		for (const auto& pair : data[n]) {
	    	for(const auto& pair1 : curr) { if( pair1.first == pair.first ) y3 = pair1.second; }
	    	if(pair.first != "side" && pair.first != "number"){
        		if( pair.second != y3 ) flag = false; 	
        	}
    		}
    		for (const auto& pair : curr) {
    		for(const auto& pair1 : data[n]) { if( pair1.first == pair.first ) y3 = pair1.second; }
	    	if(pair.first != "side" && pair.first != "number"){
        		if( pair.second != y3 ) flag = false; 	
        	}
    		}
    		int b = data[l_index].size() -2;int c = data[n].size() -2;
    		for(int d = 0; d<curr.size();d++){ if( curr[d].first == "number") y3 = d;}
    		if(flag){ 
    			data[l_index][b].second += data[n][c].second;
    			data[n][c].second = 0;
				return;
			}
    	}
    	if(w >= 0) check_cancellation3( data, curr, w , l_index);
}

int main(int argc, char **argv) {
    char choice = argv[1][0];
    Receiver rcv;
	bool foundDollar = false;
    std::string message = rcv.readIML();
	while(!foundDollar){
		std::string message1 = rcv.readIML();
		message.append(message1);
		if(message.find("$") != std::string::npos){
			foundDollar = true;
		}
	}

    if(choice == '1'){
    char* input = new char[message.length() + 1];
    std::strcpy(input, message.c_str());
    char *line, *word;
    char *saveptr;
	bool present = false;
	int least = -2147483648 ;
    std::vector<std::pair<std::string,int>> prices;
	std::vector<std::pair<std::string,int>> buy;
	std::vector<std::pair<std::string,int>> sell;
    line = strtok_r( input, "#", &saveptr ); 
    while( line != nullptr ){
    	char *ptr;
    	word = strtok_r( line, " ", &ptr );
    	int nw=0;
    	std::vector<std::string> words;
    	while( word != nullptr ){
    	     words.push_back(word);
    	     nw++;
    	     word = strtok_r( nullptr, " ", &ptr ); 
    	}
    	if(nw == 3){
			 int j = 0;
			 int bin = 0;
			 int sin = 0;
			 for(int i = 0;i<prices.size();i++){
				if(prices[i].first == words[0]){
					present = true;
					break;
				}
				j++;
			 }
			 for(int k = 0;k<buy.size();k++){
				if(buy[k].first == words[0]){
					break;
				}
				bin++;
			 }
			 for(int l = 0;l<sell.size();l++){
				if(sell[l].first == words[0]){
					break;
				}
				sin++;
			 }
    	     if(present){
				  if( words[2] == "b" && std::stoi(words[1]) > prices[j].second && (sin == sell.size()) ){
					if(buy.size() != bin){
					    if(buy[bin].second >= std::stoi(words[1])){
					    	std::cout<<"No Trade"<<std::endl;
					    }
					    else{
							buy[bin].second = least;
    	     	  	        prices[j].second = std::stoi(words[1]);
    	     		        std::cout<<words[0]<<" "<<words[1]<<" "<<"s"<<std::endl;
					    }
					}
					else{
						prices[j].second = std::stoi(words[1]);
    	     		    std::cout<<words[0]<<" "<<words[1]<<" "<<"s"<<std::endl;
					}
    	     	  }
    	     	  else if( words[2] == "b" && std::stoi(words[1]) > prices[j].second && (sell[sin].second != std::stoi(words[1])) ){
					if(buy.size() != bin){
					    if(buy[bin].second >= std::stoi(words[1])){
					    	std::cout<<"No Trade"<<std::endl;
					    }
					    else{
							buy[bin].second = least;
    	     	  	        prices[j].second = std::stoi(words[1]);
    	     		        std::cout<<words[0]<<" "<<words[1]<<" "<<"s"<<std::endl;
					    }
					}
					else{
						prices[j].second = std::stoi(words[1]);
    	     		    std::cout<<words[0]<<" "<<words[1]<<" "<<"s"<<std::endl;
					}
    	     	  }
				  else if( words[2] == "s" && std::stoi(words[1]) < prices[j].second && (bin == buy.size()) ){
					if(sell.size() != sin){
					    if(sell[sin].second <= std::stoi(words[1]) && sell[sin].second != least){
					    	std::cout<<"No Trade"<<std::endl;
				    	}
				    	else{
							sell[sin].second = least;
    	     	         	prices[j].second = std::stoi(words[1]);
    	     	    	    std::cout<<words[0]<<" "<<words[1]<<" "<<"b"<<std::endl;
				    	}
					}
					else{
						prices[j].second = std::stoi(words[1]);
    	     	    	std::cout<<words[0]<<" "<<words[1]<<" "<<"b"<<std::endl;
					}
    	     	  }
    	     	  else if( words[2] == "s" && std::stoi(words[1]) < prices[j].second && (buy[bin].second != std::stoi(words[1])) ){
					if(sell.size() != sin){
					    if(sell[sin].second <= std::stoi(words[1]) && sell[sin].second != least){
					    	std::cout<<"No Trade"<<std::endl;
				    	}
				    	else{
							sell[sin].second = least;
    	     	         	prices[j].second = std::stoi(words[1]);
    	     	    	    std::cout<<words[0]<<" "<<words[1]<<" "<<"b"<<std::endl;
				    	}
					}
					else{
						prices[j].second = std::stoi(words[1]);
    	     	    	std::cout<<words[0]<<" "<<words[1]<<" "<<"b"<<std::endl;
					}
    	     	  }
                  else if( words[2] == "b" && std::stoi(words[1]) > prices[j].second && (sell[sin].second == std::stoi(words[1])) ){
					if(buy.size() != 0 && buy[bin].second <= std::stoi(words[1])){
						buy[bin].second = least;
					}
                    sell[sin].second = least;
                    std::cout<<"No Trade"<<std::endl;
    	     	  }
                  else if( words[2] == "s" && std::stoi(words[1]) < prices[j].second && (buy[bin].second == std::stoi(words[1])) ){
					if(sell.size() != 0 &&sell[sin].second >= std::stoi(words[1])){
						sell[sin].second = least;
					}
                    buy[bin].second = least;
                    std::cout<<"No Trade"<<std::endl;
    	     	  }
    	     	  else{
                    if( words[2] == "b" && buy.size() != bin ){
                        if(buy[bin].second == least){
                            buy[bin].second = std::stoi(words[1]);
                        }
                        else{
                            if(std::stoi(words[1]) > buy[bin].second){
                            buy[bin].second = std::stoi(words[1]);
                            }
                        }
                    }
					else if( words[2] == "b" && buy.size() == bin ){
						buy.push_back({words[0],std::stoi(words[1])});
					}
                    else if( words[2] == "s" && sell.size() != sin ){
                        if(sell[sin].second == least){
                            sell[sin].second = std::stoi(words[1]);
                        }
                        else{
                            if(std::stoi(words[1]) < sell[sin].second){
                            sell[sin].second = std::stoi(words[1]);
                            }
                        }
                    }
					else if( words[2] == "s" && sell.size() == sin){
						sell.push_back({words[0],std::stoi(words[1])});
					}
                    std::cout<<"No Trade"<<std::endl;
                  }
				  present = false;
    	     }
    	     else{
    	     	prices.push_back({words[0],std::stoi(words[1])});
    	     	std::cout<<words[0]<<" "<<words[1]<<" ";
    	     	if( words[2] == "b" ) {std::cout<<"s"<<"\n";}
    	     	if( words[2] == "s" ) {std::cout<<"b"<<"\n";}
    	     }
    	}
    	saveptr++;
    	line = strtok_r( nullptr, "#", &saveptr);
    }
    }
    if(choice == '2'){
    char* input = new char[message.length() + 1];
    std::strcpy(input, message.c_str());
    char *line, *word;
    char *saveptr;
    std::vector<std::vector<std::pair<std::string,int>>> data;
    int l_index = 0;
    int profit = 0; //
    std::vector<int> used;
    line = strtok_r( input, "#", &saveptr ); 
    while( line != nullptr ){
    	char *ptr;
    	word = strtok_r( line, " ", &ptr );
    	int nw=0;
    	std::vector<std::string> words;
    	while( word != nullptr ){
    	     words.push_back(word);
    	     nw++;
    	     word = strtok_r( nullptr, " ", &ptr ); 
    	}
    	if(nw > 3 && nw %2 == 0){
    	     if (l_index >= data.size()) {
        	data.resize(l_index + 1);
             }
    	     for( int i=0; i< nw -2;i+=2) {
    	     	data[l_index].push_back(std::make_pair(words[i] , std::stoi(words[i+1]) ) );
    	     }
    	     data[l_index].push_back(std::make_pair("price" , std::stoi(words[nw-2]) ) );
    	     if( words[nw -1] == "s" ) data[l_index].push_back(std::make_pair("side" , 1 ) );
    	     else data[l_index].push_back(std::make_pair("side" , 2 ) );
    	     if(l_index != 0 ){
    	     	std::vector<std::pair<std::string,int>> curr;
    	     	std::vector<std::pair<int,std::vector<int>>> possible;
    	     	curr.resize( data[l_index].size() );
    	     	int i1 = 0;
    	     	for (const auto& pair : data[l_index]) {
        		curr[i1].first = pair.first;
        		curr[i1].second = pair.second;i1++;
    	     	}
    	     	std::vector<int> temp;
    	     	temp.push_back(l_index);
    	     	int n = l_index;
    	     	bool g = true;
    	     	while( g ){
    	     	n--;
    	     	g=false;
    	     	for(int i=0; i< used.size(); i++) { if(n == used[i]) g=true;}
    	     	}
    	     	int ll = -1;
    	     	if(n>=0){    	     		
    	     		check_cancellation(data,curr,used,n,ll);
    	     		if(ll != -1 ) {used.push_back(l_index); }
    	     	}	
    	     	if(ll == -1 ){
				n = l_index;
				g = true;
				while( g ){
    	     	n--;
    	     	g=false;
    	     	for(int i=0; i< used.size(); i++) { if(n == used[i]) g=true;}
    	     	}
    	     	if(n>=0) linear_comb(data, curr, used, possible, temp, n );
    	     	//check maximum profit in possible and update used and priniting
    		int x1,p = 0;  
    		for (const auto& pair : curr) { if( pair.first == "side" ) x1 = pair.second;}
    		for (const auto& pair : possible) {
        		if(x1 == 2 ) {if(p<pair.first) p=pair.first;}
        		else {if(p>pair.first) p=pair.first;}
    	     	}
    	    if(x1 == 1 ) p*= -1;
   	     	if(p!=0){
    	     		profit += p; 
    	     		if(x1 == 1 ) p*= -1;
    	     		int z= used.size(); int y;
    	     		for(const auto& pair : possible) { if( pair.first == p ) y = pair.second.size(); }
    	     		for(int q=0;q<possible.size(); q++) { if(possible[q].first == p ) p=q;}
    	     		for(int i= 0;i< y ; i++ ) {
    	     			used.resize(z+y);
    	     			used[i+z]=possible[p].second[i];
    	     		}
    	     		for(int i=0; i < possible[p].second.size();i++){
    	     			y = possible[p].second[i];
    	     			int w1 = data[y].size();
			    	for(int i=0;i< w1 - 2; i++ ) std::cout<<data[y][i].first<<" "<<data[y][i].second<<" ";
			    	std::cout<<data[y][w1 - 2].second<<" ";
			    	if(data[y][w1 -1].second == 1 ) std::cout<<"b"<<std::endl;
			    	else std::cout<<"s"<<std::endl;
    	     		}
    	     	}
    	     	else std::cout<<"No Trade"<<std::endl;
    	     }
    	     else std::cout<<"No Trade"<<std::endl;
    	     }
    	     else std::cout<<"No Trade"<<std::endl;
    	     l_index++; 
    	}
    	saveptr++;
    	line = strtok_r( nullptr, "#", &saveptr);
    }
    std::cout<<profit<<std::endl;
    }
    if(choice == '3'){
    char* input = new char[message.length() + 1];
    std::strcpy(input, message.c_str());
    char *line, *word;
    char *saveptr;
     std::vector<std::vector<std::pair<std::string,int>>> data;
    int l_index = 0;
    int profit = 0; 
    line = strtok_r( input, "#", &saveptr ); 
    while( line != nullptr ){
    	char *ptr;
    	word = strtok_r( line, " ", &ptr );
    	int nw=0;
    	std::vector<std::string> words;
    	while( word != nullptr ){
    	     words.push_back(word);
    	     nw++;
    	     word = strtok_r( nullptr, " ", &ptr ); 
    	}
    	if(nw > 3 && nw %2 == 1){
    	     if (l_index >= data.size()) {
        	data.resize(l_index + 1);
             }
    	     for( int i=0; i< nw -3;i+=2) {
    	     	data[l_index].push_back(std::make_pair(words[i] , std::stoi(words[i+1]) ) );
    	     }
    	     data[l_index].push_back(std::make_pair("price" , std::stoi(words[nw-3]) ) );
    	     data[l_index].push_back(std::make_pair("number" , std::stoi(words[nw-2]) ) );
    	     if( words[nw -1] == "s" ) data[l_index].push_back(std::make_pair("side" , 1 ) );
    	     else data[l_index].push_back(std::make_pair("side" , 2 ) );
    	  
    	     if(l_index != 0 ){
    	     	std::vector<std::pair<std::string,int>> curr;
    	     	std::vector<std::pair<int,std::vector<int>>> possible;
    	     	curr.resize( data[l_index].size() );
    	     	int i1 = 0;
    	     	for (const auto& pair : data[l_index]) {
        		curr[i1].first = pair.first;
        		curr[i1].second = pair.second;i1++;
    	     	}
    	     	std::vector<int> temp;
    	     	temp.push_back(l_index);
    	     	temp.push_back(0);
    	     	int t_index = temp.size() -1;
    	     	int n = l_index -1;
    	     	while( n>=0 && data[n][ data[n].size() - 2 ].second == 0 ) n--; 
    	     	if(n>=0) check_cancellation3(data,curr,n,l_index);
				int f = data[l_index][ data[l_index].size() - 2 ].second; 

    	     	for(int e =0; e< f;e++){
    	     	temp[t_index]++; 
    	     	if(n>=0) linear_comb3(data, curr, possible, temp, n );
    	     	int i1 =0;
    	     	for (const auto& pair : data[l_index]) {
        		if(pair.first != "side" && pair.first != "number"){
        		curr[i1].second += pair.second;}
        		i1++;
    	     	}
    	     	}
    	     	
    	     	//check maximum profit in possible and update used and priniting
    		int f1,x1,p = 0;
    		for (const auto& pair : curr) { if( pair.first == "side" ) x1 = pair.second;}
    		for (const auto& pair : possible) {
        		if(x1 == 2 ) {if(p<pair.first) p=pair.first;}
        		else {if(p>pair.first) p=pair.first;}
    	     	}
    	     	if(x1 == 1 ) p*= -1;
   	     	if(p!=0){
    	     		profit += p;
    	     		if(x1 == 1 ) p*= -1;
    	     		for(int q=0;q<possible.size(); q++) { if(possible[q].first == p ) {p=q;break;}}
    	     		int y = possible[p].second.size();
    	     		for(int i= 0;i< y ; i+=2 ) {
  					f = possible[p].second[i]; 
  					f1 = possible[p].second[i+1];
  					data[f][ data[f].size() -2 ].second -= f1;   	     			
      	     		}
    	     		for(int i=0; i < possible[p].second.size();i+=2){
    	     			y = possible[p].second[i];
    	     			int w1 = data[y].size();
			    	for(int i=0;i< w1 - 3; i++ ) std::cout<<data[y][i].first<<" "<<data[y][i].second<<" ";
			    	std::cout<<data[y][w1 - 3].second<<" "<<possible[p].second[i+1]<<" ";
			    	if(data[y][w1 -1].second == 1 ) std::cout<<"b"<<std::endl;
			    	else std::cout<<"s"<<std::endl;
    	     		}
    	     	}
    	     	else std::cout<<"No Trade"<<std::endl;
    	     }
    	     else std::cout<<"No Trade"<<std::endl;
    	     l_index++; 
    	}
    	saveptr++;
    	line = strtok_r( nullptr, "#", &saveptr);
    }
    std::cout<<profit<<std::endl;
    }
	rcv.terminate();
    return 0;
}