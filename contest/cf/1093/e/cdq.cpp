int main(){
	scanf("%*d%d",&w);
	int tp,a,b,c,d;
	while(scanf("%d",&tp)){
		if(tp==3)break;
		scanf("%d%d%d",&a,&b,&c);
		if(tp==1)arr[++top]=op{0,a,b,c};
		else{
			scanf("%d",&d);
			++qcnt;
			arr[++top]=op{-qcnt,a-1,b,d};
			arr[++top]=op{qcnt,c,b,d};
		}
	}
	cdq(1,top);
	for(int i=1;i<=qcnt;i++)printf("%d\n",ans[i]);
	return 0;
}
