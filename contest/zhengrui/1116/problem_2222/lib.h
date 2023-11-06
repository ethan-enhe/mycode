struct Data{
	unsigned short a,b,c,d;
};
Data operator+(Data a,Data b);

void init(int n,int k,Data d);
void update(int x,Data d);
Data query(int l,int r);
