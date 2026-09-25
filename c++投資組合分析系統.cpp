#include <iostream>
#include <string> 
#include <vector>
#include <fstream>

using namespace std;

struct Investment
{
	string symbol;
	double buyprice;
	double currentprice;
	int shares;
};
double calculateProfit(Investment stock)
{
	double buyTotal = stock.buyprice * stock.shares;
	double currentTotal = stock.currentprice * stock.shares;
	
	return currentTotal - buyTotal;
	
}
double calculateReturnRate(Investment stock)
{
	double buyTotal = stock.buyprice * stock.shares;
	double currentTotal = stock.currentprice * stock.shares;
	double profit = currentTotal - buyTotal;
	
	return profit / buyTotal *100;
}
void savePortfolio(vector<Investment> portfolio)
{
    ofstream file("investment.csv");

    file << "Symbol,BuyPrice,CurrentPrice,Shares,Investment,CurrentValue,Profit,ReturnRate,AllocationRate" << endl;

	double totalInvestment = 0;
	
	for(int i = 0; i < portfolio.size(); i++)
	{
		totalInvestment += portfolio[i].buyprice * portfolio[i].shares;
	}
    for(int i = 0; i < portfolio.size(); i++)
    {
        double investment = portfolio[i].buyprice * portfolio[i].shares;

        double currentValue = portfolio[i].currentprice * portfolio[i].shares;

        double profit = currentValue - investment;

        double returnRate = profit / investment * 100;
        
        double allocationRate = investment / totalInvestment * 100;

        file << portfolio[i].symbol << ","
             << portfolio[i].buyprice << ","
             << portfolio[i].currentprice << ","
             << portfolio[i].shares << ","
             << investment << ","
             << currentValue << ","
             << profit << ","
             << returnRate << ","
             << allocationRate << endl;
    }

    file.close();
}
int main()
{
	vector<Investment> portfolio;
	
	int choice;
	
	do
	{
		Investment stock;
		
		cout << endl;
		cout << "========================" << endl;
		cout << "     投資組合分析系統     " << endl;
		cout << "========================" << endl;
		cout << "1.新增投資" << endl;
		cout << "2.查看投資組合" << endl;
		cout << "3.查看投資報酬" << endl;
		cout << "4.資產配置分析" << endl;
		cout << "5.投資組合分析" << endl;
		cout << "6.離開" << endl;
		cout << "請選擇：";
		
		cin >> choice; 
		
		switch(choice)
		{
			case 1:
			{
				cout << "請輸入投資標的：";
    			cin >> stock.symbol;

    			cout << "請輸入買入價格：";
    			cin >> stock.buyprice;

    			cout << "請輸入目前價格：";
    			cin >> stock.currentprice;

    			cout << "請輸入持有股數：";
    			cin >> stock.shares;

    			portfolio.push_back(stock);
    			
    			savePortfolio(portfolio);

    			cout << "投資資料新增成功！" << endl;
    			
				break;
			}
			case 2:
				cout << endl;
				cout << "----------我的投資組合----------" << endl;
				
				if (portfolio.empty())
				{
					cout << "目前沒有投資資料" << endl; 
				}
				else
				{
					for(int i = 0; i < portfolio.size(); i++)
					{
						double profit = calculateProfit(portfolio[i]);
						double returnRate = calculateReturnRate(portfolio[i]);
		
						cout << endl;
						cout << "第" << i + 1 << "筆" << endl;
						cout << "投資標的：" << portfolio[i].symbol << endl;
						cout << "買入價格：" << portfolio[i].buyprice << endl;
						cout << "目前價格：" << portfolio[i].currentprice << endl;
						cout << "持有股數：" << portfolio[i].shares << endl;
						cout << "損益：" << profit << "元" << endl;
						cout << "報酬率：" << returnRate << "%" << endl; 
					}
				}
				break;
			case 3:
			{
				if (portfolio.empty())
				{
					cout << "目前沒有投資資料" << endl; 
				}
				else
				{
					double totalInvestment = 0;
					double totalValue = 0;
					
					for(int i = 0; i < portfolio.size(); i++)
					{
						totalInvestment += portfolio[i].buyprice * portfolio[i].shares;
						totalValue += portfolio[i].currentprice * portfolio[i].shares;
					}
					double totalProfit = totalValue - totalInvestment;
					double totalReturnRate = totalProfit / totalInvestment * 100;
					
					cout << endl;
					cout << "==========投資組合報酬分析==========" << endl;
					cout << "總投入金額：" << totalInvestment << "元" << endl;
					cout << "目前總市值：" << totalValue << "元" << endl;
					cout << "總損益：" << totalProfit << "元" << endl;
					cout << "整體報酬率：" << totalReturnRate << "%" << endl; 
				}
				break;
			}
			case 4:
			{	
				cout << "==========資產配置分析==========" << endl;
				
				if (portfolio.empty())
				{
					cout << "目前沒有投資資料" << endl; 
				}
				else
				{
					double totalInvestment = 0;
					//總投入金額
					for(int i = 0; i < portfolio.size(); i++)
					{
						totalInvestment += portfolio[i].buyprice * portfolio[i].shares;
					} 
					//每項投資的配置比例
					for(int i =0; i < portfolio.size(); i++)
					{
						double investmentAmount = portfolio[i].buyprice * portfolio[i].shares;
						double allocationRate = investmentAmount / totalInvestment * 100;
						
						cout << endl;
						cout << "投資標的：" << portfolio[i].symbol << endl;
						cout << "投入金額：" << investmentAmount << "元" << endl;
						cout << "配置比例：" << allocationRate << "%" << endl; 
					} 
				}
				break;
			
			}	
			case 5:
			{ 
				cout << endl;
				cout << "==========投資組合分析==========" << endl;
				
				if(portfolio.empty())
				{
					cout << "目前沒有投資資料,無法進行風險分析" << endl; 
				}
				else
				{
					double totalInvestment = 0;
					
					//總投入金額
					for(int i = 0; i < portfolio.size(); i++)
					{
						totalInvestment += portfolio[i].buyprice * portfolio[i].shares;
					}
					
					bool highConcentration = false;
					
					//分析每項投資的配置比例
					for(int i =0; i < portfolio.size(); i++)
					{
						double investmentAmount = portfolio[i].buyprice * portfolio[i].shares;
						double allocationRate = investmentAmount / totalInvestment * 100;
						
						cout << endl;
						cout << "投資標的：" << portfolio[i].symbol << endl;
						cout << "配置比例：" << allocationRate << "%" << endl; 
						
						if(allocationRate > 50)
						{
							cout << "單一資產集中度較高！" << endl;
							highConcentration = true; 
						}
					} 
					
					cout << endl;
					cout << "----------分析結果----------" << endl;
					
					if(highConcentration)
					{
						cout << "風險提醒：投資組合存在較高單一資產集中度" << endl; 
					}
					else
					{
						cout << "目前未發現單一資產高集中度情況" << endl; 
					}
				}
				break;
			}	
			case 6:
				
				cout << "程式結束,謝謝使用!" << endl;
				break;
				
			default:
				cout << "無效選項,請重新輸入!" << endl; 
		}
			
	}while (choice !=6);
	
	
	return 0; 
}
