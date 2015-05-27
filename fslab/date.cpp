#include<iostream>
using namespace std;
class date
{
	int day, month, year;
public: 
	void getdata();
	date operator+(int );
	int operator -(date );
	friend ostream & operator<<(ostream &,date &);
};
int b[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
int a[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

int date:: operator-(date d2)
{
	date res;
	int noly=0,nod,temp=d2.year;
	for(temp;temp<=year;temp++)
		if(temp%4==0)
			noly++;
		res.day=day-d2.day;
		if(res.day<0)
		{
			month--;
			res.day=day+a[month];
		}
		res.month=month-d2.month;
		if(res.month<0)
		{
			res.month=month+12;
			year--;
		}
		res.year=year-d2.year;
		if(res.year<0)
		{
			return -1;
		}
		nod=res.day+(res.year*365);
		for(int i=1;i<=res.month;i++)
			nod=nod+a[i];
		nod+=noly;
		return nod;
}


void date::getdata()
{
	cout<<endl<<"Date"; cin>>day;
	cout<<endl<<"Month:";cin>>month;
	cout<<endl<<"Year:";cin>>year;
}

int main()
{
	date d1,d2,d3;
	int n;
	cout<<"\nEnter the valid first date: ";
	d1.getdata();
	cout<<"\nEnter the valid second date which is less than or equal to the first date:";
	d2.getdata();
	n=d1-d2;
	cout<<n;
}