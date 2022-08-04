namespace IO{
    inline char gc()
    {
		static char buf[1000000],*S=buf+1000000,*T=buf+1000000;
		return S==T&&(T=(S=buf)+fread(buf,1,1000000,stdin),S==T)?EOF:*S++;
    }
    template<typename T>
    inline T read()
    {
		T x=0;char ssd=gc();
		while(ssd<'0'||ssd>'9')ssd=gc();
		while(ssd>='0'&&ssd<='9')x=(x<<3)+(x<<1)+(ssd-'0'),ssd=gc();
		return x;
    }
}
