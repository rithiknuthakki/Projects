#ifndef MARKET_H
#define MARKET_H
#include <vector>
#include <string>
class market
{
public:
	market(int argc, char** argv);
	void start();
private:
	std::vector<std::vector<std::pair<std::string,int>>> data;
	std::vector<std::vector<int>> time;
	std::vector<std::string> broker;
	int data_size = 0;
};
#endif
