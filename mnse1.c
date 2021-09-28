	//all required header files
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<time.h>
	#include<termios.h>
	
	//all required global variable declaration
	int l,f,i,j,k;
	int day,month,year,hour,min,sec;
	int adminvar=0;
	int ss[4]={8,12,16,20};
	char moviename[3][7][50];
	int movierate[3][7][3];
	int mn[3],sn,st[8];
	int totalfee;
	char cname[25],cmobi[12],ccard[18],cpin[5],password[10]="cinebook";
	unsigned long int regnumber=1;
	
	//structures
	 struct reserved
	 {
	 	unsigned long int regnum;
	 	char regname[25];
	 	char regmobi[15];
	 	int regday;
	 	int regmonth;
	 	int regyear;
	 	int regslot;
	 	int rday,rmonth,ryear,rhour,rmin,rsec;
	 	int reglang;
	 	int regcinenum;
	 	char regcine[50];
	 	int regseatcnt;
	 	int regseatnum[10];
	 	int regrate;
	 }info;
	 
	 struct vdata
	 {
	 	unsigned long int vregnumber;
	 	char vpassword[10];
	 	char vmoviename[3][7][50];
	 	int vmovierate[3][7][3];
		int vmn[3];
	 }vinfo;
	 
	 FILE *fp,*ft,*fr;
	
	//all function declarations
	void welcome();
	void home();
	void login();
	void customer();
	void cancelreg();
	void datetime();
	void language();
	void movie();
	void chooseseat();
	void submit();
	void admin();
	void choose();
	void changepass();
	void manage();
	void checkseat();
	void changerate();
	void changemovie();
	void thankyou();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	static struct termios old, new;
 
	// Initialize new terminal i/o settings
	void initTermios(int echo) 
	{
  		tcgetattr(0, &old); //grab old terminal i/o settings
  		new = old; //make new settings same as old settings
  		new.c_lflag &= ~ICANON; //disable buffered i/o
  		new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  		tcsetattr(0, TCSANOW, &new); //apply terminal io settings
	}
 
	// Restore old terminal i/o settings
	void resetTermios(void) 
	{
 		 tcsetattr(0, TCSANOW, &old);
	}
 
	// Read 1 character - echo defines echo mode
	char getch_(int echo) 
	{
 		 char ch;
 		 initTermios(echo);
 		 ch = getchar();
 		 resetTermios();
  		return ch;
	}
 
	//Read 1 character without echo getch() function definition
	char getch(void) 
	{
 		 return getch_(0);
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	int main()
	{	
		int size;
		fp=fopen("i1mnse.dat","rb+");
		if(fp==NULL) { fp=fopen("i1mnse.dat","wb+"); }
		fread(&vinfo,sizeof(vinfo),1,fp);
		fseek(fp,0,SEEK_END);
		size=ftell(fp);
		rewind(fp);
		if(size!=0) { regnumber=vinfo.vregnumber;
					  strcpy(password,vinfo.vpassword); }
		for(i=0;i<3;i++) { for(j=0;j<7;j++) { strcpy(moviename[i][j],vinfo.vmoviename[i][j]);
						   for(k=0;k<3;k++) { movierate[i][j][k]=vinfo.vmovierate[i][j][k]; } } 
											  mn[i]=vinfo.vmn[i]; }
		
		fr=fopen("i2mnse.dat","rb+");
		if(fr==NULL) { fr=fopen("i2mnse.dat","wb+"); }
		
		
		welcome();
		
		
		printf("\n\n...");
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	void login()
	{
		char c;
		do
		{
		printf("\033c");
		printf("\n   (*NOTE - For go to 'Home-page' enter '0' wherever through input in programme)");
		printf("\n\n\n");
		printf("\n                                  .....login as......                ");
		printf("\n               ------------------------------------------------------\n");
		printf("\n                    ----- ----------                ----- -------    ");
		printf("\n                    | 1 |  Customer                 | 2 |  Admin     ");
		printf("\n                    ----- ----------                ----- -------  \n");
		printf("\n               ------------------------------------------------------");
		printf("\n                                            ");
		c=getch();
		if(c=='0')
		{ home(); }
		if(c=='1')
		{ customer(); }
		if(c=='2')
		{ admin(); }
		}while(c!='0'&&c!='1'&&c!='2');
	}
	
	void customer()
	{
		char c;
		do
		{
		printf("\033c");
		printf("\n\n\n");
		printf("\n                                 .....make the choice......                   ");
		printf("\n          -------------------------------------------------------------------\n");
		printf("\n          ----- --------------------------       ----- ---------------------- ");
		printf("\n          | 1 |  Make reservation of seats       | 2 |  Cancel reserved seats ");
		printf("\n          ----- --------------------------       ----- ----------------------\n");
		printf("\n          ------------------------------------------------------------------- ");
		printf("\n                                            ");
		c=getch();
		if(c=='0')
		{ home(); }
		if(c=='1')
		{ datetime(); }
		if(c=='2')
		{ cancelreg(); }
		}while(c!='0'&&c!='1'&&c!='2');
	}
	
	void cancelreg()
	{
		time_t T= time(NULL);
    	struct  tm tm = *localtime(&T);
		int cnt,cnt2,cnt3;
		unsigned long int cancel;
		char mstr[12],c;
		c_again :
		cnt=0;
		cnt3=0;
		printf("\033c");
		printf("\n\n\n");
		printf("\n          ||| To cancel your reserved seats please fill required data |||      ");
		printf("\n      ---------------------------------------------------------------------- \n");
		printf("\n      ||| please enter your registration number      >>>   R-");
		scanf("%lu",&cancel);
		getch();
		if(cancel==0) { home(); }
		rewind(fr);
		while(fread(&info,sizeof(info),1,fr)==1)
		{	if(info.regnum==cancel)
			{
		printf("\n\n      ||| please enter your registered mobile number >>>   ");
		cnt2=0;
		while((c=getch())!='\n'||cnt2<10) { if(cnt2<10&&c!='\n'&&c!=127) {  mstr[cnt2++]=c;
												 							printf("%c",c);
												 							mstr[cnt2]='\0'; } }
		if(strcmp(mstr,"0")==0) { home(); }
			if(strcmp(info.regmobi,mstr)==0)
			{
		printf("\n\n      ||| Cancel the reserved seats for following ....                        ");
		printf("\n\n          Customer name :  %s",info.regname);
		printf("\n          Cinema name   :  %s",info.regcine);
		printf("\n\n          Show date     :  %02d/%02d/%04d",info.regday,info.regmonth,info.regyear);
		printf("\n\n          Slot          :  ");
			if(info.regslot==12)
				{ printf("%02dPM-%02dPM",info.regslot,(info.regslot+3)%12); }
			else if(info.regslot>12)
				{ printf("%02dPM-%02dPM",info.regslot%12,(info.regslot+3)%12); }
			else { printf("%02dAM-%02dAM",info.regslot,info.regslot+3); }
		printf("\n\n          Seat numbers  : ");
		for(k=0;k<(info.regseatcnt);k++) { printf(" %02d",info.regseatnum[k]); }
		
		if((tm.tm_year+1900)<info.regyear) { cnt3=1; }
		else if((tm.tm_year+1900)==info.regyear&&(tm.tm_mon+1)<info.regmonth) { cnt3=1; }
		else if((tm.tm_year+1900)==info.regyear&&(tm.tm_mon+1)==info.regmonth&&tm.tm_mday<info.regday) { cnt3=1; }
		else if((tm.tm_year+1900)==info.regyear&&(tm.tm_mon+1)==info.regmonth&&tm.tm_mday==info.regday&&tm.tm_hour<info.regslot) { cnt3=1; }
		
		if(cnt3==1) {
		printf("\n\n         To confirm (C/c) ....                     Otherwise (any) ....");
		printf("\n                                         ");
		c=getch();
		if(c=='0') { home(); }
		else if(c=='C'||c=='c')
		{	
			ft=fopen("i3mnse.dat","wb");
			rewind(fr);
			while(fread(&info,sizeof(info),1,fr)==1)
			{ if(info.regnum!=cancel) { fwrite(&info,sizeof(info),1,ft); } 
		else{ printf("\n\n                     ||| The seats are successfully cancelled |||");
		printf("\n\n             ||| Your paid %d Rs. will return to your bank account |||\n",info.regrate); } }
			fclose(ft);
			fclose(fr);
			remove("i2mnse.dat");
			rename("i3mnse.dat","i2mnse.dat");
			fr=fopen("i2mnse.dat","rb+");
		printf("\n\n      ----------------------------------------------------------------------\n");
		printf("\n             To Home (any) ....           ");
		getch();
		home();
		} else { goto h_again; }
		} else { printf("\n\n                         ||| The show is already gone |||");
		printf("\n\n                    ||| You can't recover your paid amount |||");
		printf("\n\n      ----------------------------------------------------------------------\n");
		printf("\n             To Home (any) ....           ");
		getch();
		home(); } }
			else {
		printf("\n\n\n      |||Your provided data doesn't match ....                             ");
		h_again :
		printf("\n      ---------------------------------------------------------------------- \n");
		printf("\n          Try again (C/c) ....                         To Home (any) ....      ");
		printf("\n                                           ");
		c=getch();
		if(c=='C'||c=='c') { goto c_again; }
		else { home(); } }
				cnt++; } }
		if(cnt==0) { goto c_again; }
	}
	
	void datetime()
	{
		int dy[3],mt[3],yr[3],d,t;
		char c;
		
		time_t T= time(NULL);
    	struct  tm tm = *localtime(&T);
    	day=tm.tm_mday;
    	month=tm.tm_mon+1;
    	year=tm.tm_year+1900;
    	hour=tm.tm_hour;
    	min=tm.tm_min;
    	sec=tm.tm_sec;
    	
    	do
		{
		printf("\033c");
		printf("\n\n\n");
		printf("\n                           ......select the date......                       ");
		printf("\n    ---------------------------------------------------------------------- \n");
		printf("\n    -----   ----------        -----   ----------        -----   ---------- \n");
		for(i=0;i<3;i++)
		{
		if(i>0) {
			if(month==4||month==6||month==9||month==11) { if((day+1)>30) { month++; }
														  if(day!=29) { day=(day+1)%30; } }
			else if(month==2) { if(year%4!=0) { if((day+1)>28) { month++; }
												if(day!=27) { day=(day+1)%28; } } 
								else { if((day+1)>29) { month++; }
									   if(day!=28) { day=(day+1)%29;} } }
			else { if((day+1)>31) { month=1,year++; }
			 	  if(day!=30) { day=(day+1)%31; } }   }
		dy[i]=day,mt[i]=month,yr[i]=year;
		printf("    | %d |   %02d/%02d/%04d    ",i+1,day,month,year);
		}
		printf("\n    -----   ----------        -----   ----------        -----   ---------- ");
		printf("\n\n    ---------------------------------------------------------------------- ");
		printf("\n      Home (0)                                         Enter choice ...    ");
		printf("\n    ---------------------------------------------------------------------- ");
		printf("\n\n                                         ");
		c=getch();
		if(c=='0')
		{ home(); }
		if(c=='1'||c=='2'||c=='3') { d=c-48; }
		if(d==1||d==2||d==3) { day=dy[d-1],month=mt[d-1],year=yr[d-1]; }
		}while(c!='0'&&c!='1'&&c!='2'&&c!='3');
		
		do
		{
		slot:
		printf("\033c");
		printf("\n\n\n");
		printf("\n                         ......select the show slot......              ");
	  printf("\n  ------------------------------------------------------------------------------\n");
	  printf("\n  --- --------------  --- --------------  --- --------------  --- --------------\n");
		for(i=0;i<4;i++)
		{
		printf("  |%d| ",i+1);
		if(tm.tm_hour<ss[i]||day!=tm.tm_mday)
		{ 
		if(ss[i]==12)
		{ printf("%02d PM to %02d PM",ss[i],(ss[i]+3)%12); }
		else if(ss[i]>12)
		{ printf("%02d PM to %02d PM",ss[i]%12,(ss[i]+3)%12); }
		else { printf("%02d AM to %02d AM",ss[i],ss[i]+3); }
		}
		else { printf("     ****     "); }
		}
		printf("\n  --- --------------  --- --------------  --- --------------  --- --------------");
	  printf("\n\n  ------------------------------------------------------------------------------");
		printf("\n     Home (0)                                              Enter choice ...     ");
		printf("\n  ------------------------------------------------------------------------------");
		printf("\n\n                                        ");
		c=getch();
		if(c=='0')
		{ home(); }
		if(c=='1'||c=='2'||c=='3'||c=='4') { t=c-48; }
		if(t==1||t==2||t==3||t==4) {
		if(ss[t-1]<=tm.tm_hour&&day==tm.tm_mday) { goto slot; }
		else {  hour=ss[t-1];
				language(); } }
		}while(c!='0'&&c!='1'&&c!='2'&&c!='3'&&c!='4');
	}
	


	void language()
	{
		char c;
		do
		{
		printf("\033c");
		printf("\n\n\n");
		printf("\n                           ......select the language......              ");
		printf("\n           ------------------------------------------------------------ ");
		printf("\n                                                                        ");
		printf("\n           -----   -------         -----  ------        -----   ------- ");
		printf("\n           | 1 |   English         | 2 |   Hindi        | 3 |   Marathi ");
		printf("\n           -----   -------         -----  ------        -----   ------- ");
		printf("\n\n           ------------------------------------------------------------ ");
		printf("\n            Home (0)                               Enter choice ....    ");
		printf("\n           ------------------------------------------------------------ ");
		printf("\n                                          ");
		c=getch();
		if(c=='0')
		{ home(); }
		if(c=='1'||c=='2'||c=='3') { l=c-49; }
		if(l==0||l==1||l==2) { if(adminvar==0) { movie(); } }
		}while(c!='0'&&c!='1'&&c!='2'&&c!='3');
	}
	
	void movie()
	{	
		char c;
		do
		{
		printf("\033c");
		printf("\n\n\n");
		printf("\n                           ......select the movie......                 ");
		printf("\n                                                                        ");
		printf("\n           -----   --------------------------------------------------   ");
		for(i=0;i<mn[l];i++) {
		printf("\n           | %02d |   %s",i+1,moviename[l][i]);
		printf("\n           -----   --------------------------------------------------   "); }
		printf("\n\n           ---------------------------------------------------------- ");
		printf("\n\n            Home (0)                               Enter choice ....    ");
		printf("\n           ----------------------------------------------------------   ");
		printf("\n                                          ");
		c=getch();
		if(c=='0')
		{ home(); }
		if(c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7') { f=c-49; }
		if(f<mn[l]&&f>=0) { if(adminvar==0) { chooseseat(); } }
		}while(f<0||f>=mn[l]);
	}
	
	void chooseseat()
	{	
		int cnt,cnt1,cnt2=0;
		int x=0,xc,r=0;
		char c;
		s_again :
		do {
		cnt=0;
		printf("\033c");
		xc=0;
		printf("\n\n");
		printf("\n                     |||>>>>> Select the seat <<<<<|||                     \n");
		printf("\n        ------------------------------------------------------------         ");
		printf("\n        ------------------------------------------------------------         ");
		printf("\n        |                          screen                          |         ");
		printf("\n        ------------------------------------------------------------       \n");
		for(i=0;i<10;i++) {
		if(i==0) { printf("\n                ---------silver seats (rate %d Rs.)---------\n",movierate[l][f][0]); }
		if(i==3) { printf("\n                ----------gold seats (rate %d Rs.)----------\n",movierate[l][f][1]); }
		if(i==7) { printf("\n                --------platinum seats (rate %d Rs.)--------\n",movierate[l][f][2]); }
		printf("      ");
		if(i==9) { printf("                "); }
		for(j=0;j<10;j++) { cnt++;
		if(j==5) { printf("  "); }
		if(cnt<=95)
		{   rewind(fr);
			while(fread(&info,sizeof(info),1,fr)==1) {
			for(k=0;k<(info.regseatcnt);k++) {
				if(info.regseatnum[k]==cnt&&strcmp(info.regcine,moviename[l][f])==0&&info.regcinenum==f&&info.reglang==l&&info.regslot==hour&&info.regday==day&&info.regmonth==month&&info.regyear==year) { r=1; } } }
			if(r==1) { printf("  ||||");
					   r=0;}
			else { printf("  |%02d|",cnt); }
		} }
		printf("\n\n"); }
		printf("\n        ------------------------------------------------------------         ");
		printf("\n        ------------------------------------------------------------       \n");
		printf("\n         |||| indicate the reserved seats                                    ");
		printf("\n        ------------------------------------------------------------         ");
		printf("\n\n        ( Maximum 8 seats can book at a time )");
		printf("\n        |>>>>>>> How many seats you want to book .... ");
		if(cnt2==0) { c=getch();
					  sn=c-48;
					  cnt2=1; }
		printf("%d",sn); }while(sn<0||sn>8);
		if(sn==0) { home(); }
		printf("\n        |>>>>>>> Enter the seat numbers .... ");
		for(;x<sn;x++) { 	if(x!=0&&xc==0) { for(j=0;j<x;j++) { printf("%d ",st[j]); } }
							xc=1;
							scanf("%d",&st[x]);
							if(st[x]==0) { home(); }
							cnt1=0;
							if(st[x]<1||st[x]>95) { goto s_again; }
		for(j=0;j<x;j++) { if(st[x]==st[j]) { cnt1++; }
						   if(cnt1!=0) { goto s_again; } }
		rewind(fr);
		while(fread(&info,sizeof(info),1,fr)==1) { for(k=0;k<(info.regseatcnt);k++) {
		if(info.regseatnum[k]==st[x]&&strcmp(info.regcine,moviename[l][f])==0&&info.regcinenum==f&&info.reglang==l&&info.regslot==hour&&info.regday==day&&info.regmonth==month&&info.regyear==year) { goto s_again; } } } }
		submit();
	}
	
	void submit()
	{	
		char c;
		printf("\033c");
		printf("\n\n");
		printf("\n                ------------------------------------------------           ");
		printf("\n                       You are going to book seats for.....             ");
		printf("\n       -----------------------------------------------------------------   ");
		printf("\n\n       |>>>> movie name   >>>>   %s",moviename[l][f]);
		printf("\n\n       |>>>> movie date   >>>>   %02d/%02d/%04d",day,month,year);
		printf("\n\n       |>>>> movie slot   >>>>   ");
		if(hour==12)
		{ printf("%02d PM to %02d PM",hour,(hour+3)%12); }
		else if(hour>12)
		{ printf("%02d PM to %02d PM",hour%12,(hour+3)%12); }
		else { printf("%02d AM to %02d AM",hour,hour+3); }
		printf("\n\n       |>>>> seat numbers >>>>   ");
		for(i=0;i<sn;i++) {
		printf("%d ",st[i]); }
		printf("\n       -----------------------------------------------------------------   ");
		printf("\n\n       Home (0)                                 To continue (enter) .... ");
		printf("\n                                       ");
		getch();
		c=getch();
		if(c=='0')
		{ home(); }
		
		int cnt1=0,cnt2;
		m_again :
		printf("\033c");
		printf("\n\n\n");
		printf("\n                ---------------------------------------------------            ");
		printf("\n                         |||>>>>> Fill required data <<<<<|||                  ");
		printf("\n       ---------------------------------------------------------------------   ");
		printf("\n\n      ||| please enter your name                     >>>   ");
		if(cnt1!=0) { printf("%s",cname); }
		else { fgets(cname,25,stdin); }
		cnt1=1;
		printf("\n      ||| please enter your mobile number (10-digit) >>>   ");
		cnt2=0;
		while((c=getch())!='\n'||cnt2<10) { if(c==127) { goto m_again; }
											if(cnt2<10&&c!='\n') {  cmobi[cnt2++]=c;
												 					printf("%c",c);
												 					cmobi[cnt2]='\0'; } }
		
		int sum1=0,sum2=0,sum3=0;
		for(i=0;i<sn;i++) {
		if(st[i]>=1&&st[i]<=30) { sum1++; }
		if(st[i]>=31&&st[i]<=70) { sum2++; }
		if(st[i]>=71&&st[i]<=95) { sum3++; } }
		totalfee=(sum1*movierate[l][f][0])+(sum2*movierate[l][f][1])+(sum3*movierate[l][f][2]);
		p_again :
		printf("\033c");
		printf("\n\n\n");
		printf("\n                ------------------------------------------------           ");
		printf("\n                   |||>>>>> Make payment and submit <<<<<|||               ");
		printf("\n       -----------------------------------------------------------------   ");
		printf("\n\n        |>>>( You need to pay %d Rs. for book all selected seats)<<<|",totalfee);
		printf("\n\n      ||| please enter your card number (16-digit)   >>>   ");
		cnt1=0;
		getch();
		while((c=getch())!='\n'||cnt1<16) { if(c==127) { goto p_again; }
											if(cnt1<16&&c!='\n') { ccard[cnt1]=c;
											if(cnt1%4==0&&cnt1!=0) { printf("-"); }
											printf("%c",c);
											ccard[++cnt1]='\0'; } }
		printf("\n\n      ||| please enter your card pin  (4-digit)      >>>   ");
		cnt2=0;
		while((c=getch())!='\n'||cnt2<4) { if(cnt2<4&&c!=127&&c!='\n') { cpin[cnt2++]=c;
											   							 printf("*"); 
											   							 cpin[cnt2]='\0'; } }
		time_t T= time(NULL);
    	struct  tm tm = *localtime(&T);
		
		fseek(fr,0,SEEK_END);
		rewind(fp);
		info.regnum=regnumber;
		regnumber++;
		vinfo.vregnumber=regnumber;
		strcpy(vinfo.vpassword,password);
		for(i=0;i<3;i++) { for(j=0;j<7;j++) { strcpy(vinfo.vmoviename[i][j],moviename[i][j]);
						   for(k=0;k<3;k++) { vinfo.vmovierate[i][j][k]=movierate[i][j][k]; } } 
											  vinfo.vmn[i]=mn[i]; }
		fwrite(&vinfo,sizeof(vinfo),1,fp);
		rewind(fp);
		
		info.rday=tm.tm_mday;
		info.rmonth=tm.tm_mon+1;
		info.ryear=tm.tm_year+1900;
		info.rhour=tm.tm_hour;
		info.rmin=tm.tm_min;
		info.rsec=tm.tm_sec;
		info.regday=day;
		info.regmonth=month;
		info.regyear=year;
		info.regslot=hour;
		info.reglang=l;
		info.regcinenum=f;
		info.regseatcnt=sn;
		for(i=0;i<sn;i++) { info.regseatnum[i]=st[i]; }
		info.regrate=totalfee;
		strcpy(info.regname,cname);
		strcpy(info.regmobi,cmobi);
		strcpy(info.regcine,moviename[l][f]);
		fwrite(&info,sizeof(info),1,fr);
		fseek(fr,0,SEEK_END);
		
		printf("\033c");
		printf("\n\n\n");
		printf("\n               -------------------------------------------------           ");
		printf("\n                You are successsfully booked seats for the show            ");
		printf("\n       ------------------------------------------------------------------  ");
		printf("\n\n          Please note your registration number : >>> R-%010lu <<<",regnumber-1);
		printf("\n\n       ( In case of cancel booking the registration number and registered  ");
		printf("\n                  mobile number is mandatory to fill as data )             ");
		printf("\n\n\n       Date:%02d/%02d/%04d    Customer name : %s",day,month,year,cname);
		printf("\n       Slot:");
		if(hour==12)
		{ printf("%02dPM - %02dPM",hour,(hour+3)%12); }
		else if(hour>12)
		{ printf("%02dPM - %02dPM",hour%12,(hour+3)%12); }
		else { printf("%02dAM - %02dAM",hour,hour+3); }
		printf("   Mobile no.    : %s",cmobi);
		printf("\n\n       Movie name :  %s",moviename[l][f]);
		printf("\n\n       Seat count :  %02d   Seat numbers : ",sn);
		for(i=0;i<sn;i++) { printf(" %02d",st[i]); }
		printf("\n\n");
		printf("\n                           |>>>>>>>>>>>>>>>                                ");
		printf("\n                                Enjoy the show...                          ");
		printf("\n                                       <<<<<<<<<<<<<|                      ");
		printf("\n       ------------------------------------------------------------------   ");
		printf("\n\n                                                 To Home (enter) ....      ");
		printf("\n                                       ");
		getch();
		home();
	}
	
	
	void admin()
	{
		char p[25],c,cn,i;
		int cnt=0;
		pass:
		cn=0;
		i=0;
		cnt++;
		if(cnt>3)
		{ home();
		  exit(1); }
		printf("\033c");
		printf("\n\n\n\n\n\n");
		printf("\n                           ---------------------------");
		printf("\n                            please enter the password ");
		printf("\n                           ---------------------------");
		printf("\n                                     ");
		while((c=getch())!='\n')
		{
			if(c==127) { goto pass; }
			if(i<8) { p[i++]=c;
			p[i]='\0';
			printf("*");
			cn++; }
			if(strcmp(p,password)==0) { choose(); }
			}
			if(strcmp(p,"0")==0) { home(); }
			if(strcmp(p,password)!=0) { goto pass; }
	}
	
	void choose()
	{
		char c;
		do
		{
		printf("\033c");
		printf("\n\n\n");
		printf("\n                                .....make choice......                    ");
		printf("\n            ------------------------------------------------------------\n");
		printf("\n                ----- -----------------     ----- -----------------       ");
		printf("\n                | 1 |  manage cinebook      | 2 |  change password        ");
		printf("\n                ----- -----------------     ----- -----------------       ");
		printf("\n                                  ----- ---------                         ");
		printf("\n                                  | 3 |   exit                            ");
		printf("\n                                  ----- ---------                       \n");
		printf("\n            ------------------------------------------------------------  ");
		printf("\n                                            ");
		c=getch();
		if(c=='0')
		{ home(); }
		if(c=='1')
		{ manage(); }
		if(c=='2')
		{ changepass(); }
		if(c=='3')
		{ thankyou(); }
		}while(c!='0'&&c!='1'&&c!='2'&&c!='3');
	}
	
	void changepass()
	{
		char c,p[10],p1[10],p2[10];
		int cnt1=0,i,j,k;
		pass :
		i=0;
		j=0;
		k=0;
		printf("\033c");
		printf("\n\n\n");
		printf("\n                       .....fill data to change password......            ");
		printf("\n            ------------------------------------------------------------\n");
		printf("\n                |||| enter the current password >>> ");
		if(cnt1==0) {
		while((c=getch())!='\n')
		{
			if(c==127) { goto pass; }
			if(i<8) { p[i++]=c;
			p[i]='\0';
			printf("*"); }
		} } else { printf("********"); }
			if(strcmp(p,password)==0) { 
		cnt1=1;
		printf("\n\n\n                |||| enter the new password     >>> ");
		do  {
			c=getch();
			if(c==127||(j!=8&&c=='\n')) { goto pass; }
			if(j<8) { p1[j++]=c;
			p1[j]='\0';
			printf("%c",c); }
		}while(j!=8);
		if(strcmp(p1,"0")==0) { home(); }
		printf("\n\n                |||| confirm new password       >>> ");
		do {
			c=getch();
			if(c==127||(k!=8&&c=='\n')) { goto pass; }
			if(k<8) { p2[k++]=c;
			p2[k]='\0';
			printf("%c",c); }
		}while(k!=8);
		if(strcmp(p2,"0")==0) { home(); }
		if(strcmp(p1,p2)==0) {
		strcpy(password,p1);
		rewind(fp);
		vinfo.vregnumber=regnumber;
		strcpy(vinfo.vpassword,password);
		for(i=0;i<3;i++) { for(j=0;j<7;j++) { strcpy(vinfo.vmoviename[i][j],moviename[i][j]);
						   for(k=0;k<3;k++) { vinfo.vmovierate[i][j][k]=movierate[i][j][k]; } } 
											  vinfo.vmn[i]=mn[i]; }
		fwrite(&vinfo,sizeof(vinfo),1,fp);
		rewind(fp);
		printf("\n\n\n                     |||| the password successfully changed ||||            ");
		printf("\n            ------------------------------------------------------------  \n");
		printf("\n                 To home ( any key ) .... ");
		getch();
		home(); } else { goto pass; }
			 }
			if(strcmp(p,"0")==0) { home(); }
			if(strcmp(p,password)!=0) { goto pass; }
	}
	
	void manage()
	{
		char c;
		do
		{
		printf("\033c");
		printf("\n\n\n\n");
		printf("\n                             .....choose the purpose......                ");
		printf("\n             -------------------------------------------------------      ");
		printf("\n                                                                          ");
		printf("\n             ----- -------------------      ----- ------------------      ");
		printf("\n             | 1 |  check booked seats      | 2 |  change show rates      ");
		printf("\n             ----- -------------------      ----- ------------------      ");
		printf("\n                             -----  ------------------                    ");
		printf("\n                             | 3 |   change the movies                    ");
		printf("\n                             -----  ------------------                    ");
		printf("\n\n             -------------------------------------------------------    ");
		printf("\n              Home (0)                             Enter choice ...       ");
		printf("\n             -------------------------------------------------------      ");
		printf("\n\n                                         ");
		c=getch();
		if(c=='0')
		{ home(); }
		if(c=='1')
		{ checkseat(); }
		if(c=='2')
		{ changerate(); }
		if(c=='3')
		{ changemovie(); }
		}while(c!='1'&&c!='2'&&c!='3');
	}
	
	void checkseat()
	{
		char c;
		unsigned long int reject;
		c_again :
		printf("\033c");
		printf("\n\n\n");
		printf("\n    -----------------------------------------------------------------------------------------------------------");
		printf("\n    ...Reg.number...                             .....Data of booked seats......");
		rewind(fr);
		while(fread(&info,sizeof(info),1,fr)==1)
		{
			printf("\n    ----------------    ---------------------------------------------------------------------------------------");
			printf("\n                        Date: %02d/%02d/%04d   Cinema          : %s",info.regday,info.regmonth,info.regyear,info.regcine);
			printf("\n                        Slot: ");
			if(info.regslot==12)
				{ printf("%02dPM-%02dPM",info.regslot,(info.regslot+3)%12); }
			else if(info.regslot>12)
				{ printf("%02dPM-%02dPM",info.regslot%12,(info.regslot+3)%12); }
			else { printf("%02dAM-%02dAM",info.regslot,info.regslot+3); }
			printf("    Customer name   : %s",info.regname);
			printf("    | R-%010lu |    Language: ",info.regnum);
			if(info.reglang==0) { printf("Eng"); }
			else if(info.reglang==1) { printf("Hin"); }
			else { printf("Mar"); }
			printf("      Customer mobile : %s",info.regmobi);
			printf("\n                        Seat-count: %02d     Seat numbers    :",info.regseatcnt);
			for(i=0;i<(info.regseatcnt);i++) { printf(" %02d",info.regseatnum[i]); }
			printf("\n                        Reserved on (%02d/%02d/%04d) at (%02d:%02d:%02d ",info.rday,info.rmonth,info.ryear,info.rhour%12,info.rmin,info.rsec);
			if(info.rhour<12) { printf("AM)"); }
			else { printf("PM)"); }
			printf(" by Paid (%d Rs.)",info.regrate); }
			printf("\n    -----------------------------------------------------------------------------------------------------------");
			printf("\n\n           Reject reserved seat (R/r) ....                                               Home (any) ....");
			printf("\n                                                            ");
			c=getch();
			if(c=='R'||c=='r')
			{
				printf("\n           Enter the Registration number which you want to Reject...");
	  			printf("\n                                                                      R-");
				scanf("%lu",&reject);
				getch();
				if(reject==0) { home(); }
				ft=fopen("i3mnse.dat","wb");
				rewind(fr);
				while(fread(&info,sizeof(info),1,fr)==1)
				{ if(info.regnum!=reject) { fwrite(&info,sizeof(info),1,ft); } }
				fclose(ft);
				fclose(fr);
				remove("i2mnse.dat");
				rename("i3mnse.dat","i2mnse.dat");
				fr=fopen("i2mnse.dat","rb+");
				goto c_again;
			} else { home(); }
	
	}
	
	void changerate()
	{
		adminvar=1;
		language();
		movie();
		char c;
		r_again:
		do { printf("\033c");
		printf("\n\n\n");
		printf("\n          The old rates of the selected movie are as follow ....         ");
		printf("\n        ---------------------------------------------------------        ");
		printf("\n\n        -------------------                    ------------------      ");
		printf("\n        |1|  silver  %d Rs                    |2|   gold  %d Rs ",movierate[l][f][0],movierate[l][f][1]);
		printf("\n        -------------------                    ------------------      ");
		printf("\n\n                           ---------------------                       ");
		printf("\n                           |3|  platinum  %d Rs  ",movierate[l][f][2]);
		printf("\n                           ---------------------                       ");
		printf("\n\n        ---------------------------------------------------------        ");
		printf("\n\n        Movie list (l)                     Enter the choice .... ");
		printf("\n        ---------------------------------------------------------        ");
		printf("\n\n                                      ");
		c=getch();
		if(c=='l') { changerate(); }
		if(c=='0') { home(); } }while(c!='0'&&c!='1'&&c!='2'&&c!='3'&&c!='l');
		
		printf("\033c\n\n\n\n");
		printf("\n       ------------------------------------------------------------  ");
		if(c=='1') { printf("\n                   Enter the new rate of silver seats ... "); }
		if(c=='2') { printf("\n                    Enter the new rate of gold seats ...  "); }
		if(c=='3') { printf("\n                  Enter the new rate of platinum seats ..."); }
		printf("\n       ------------------------------------------------------------  ");
		printf("\n\n                                     ");
		scanf("%d",&movierate[l][f][c-49]);
		rewind(fp);
		vinfo.vregnumber=regnumber;
		strcpy(vinfo.vpassword,password);
		for(i=0;i<3;i++) { for(j=0;j<7;j++) { strcpy(vinfo.vmoviename[i][j],moviename[i][j]);
						   for(k=0;k<3;k++) { vinfo.vmovierate[i][j][k]=movierate[i][j][k]; } } 
											  vinfo.vmn[i]=mn[i]; }
		fwrite(&vinfo,sizeof(vinfo),1,fp);
		rewind(fp);
		goto r_again;
	}
	
	void changemovie()
	{
		adminvar=1;
		language();
		char c='z';
		n_again:
		do {
		if(c=='a'&&mn[l]<7) { mn[l]++; }
		if(c=='r'&&mn[l]>0) { mn[l]--; }
		printf("\033c\n\n\n");
		printf("\n       ------------------------------------------------------------      ");
		printf("\n                    Choose the movie and make change ....                ");
		printf("\n       ------------------------------------------------------------    \n");
		printf("\n       ------------------------------------------------------------      ");
		for(i=0;i<mn[l];i++) {
		printf("\n       |%d|  %s",i+1,moviename[l][i]);
		printf("\n       ------------------------------------------------------------ "); }
		printf("\n\n                              Home (0) ...                               ");
		printf("\n        Add movie (a) ...                    Remove movie (r)...         ");
		printf("\n\n                   Change in another language movie (c) ...             ");
		printf("\n       ------------------------------------------------------------ ");
		printf("\n\n                                     ");
		c=getch();
		if(c=='0') { home(); }
		if(c=='c') { changemovie(); } }while(c<48||(c-48)>mn[l]);
		
		printf("\033c\n\n\n");
		printf("\n    ||| The old name of this movie is |>>> %s",moviename[l][c-49]);
		printf("\n       -------------------------------                                 ");
		printf("\n       -------------------------------                                 ");
		printf("\n    ||| Enter new name of this movie  |>>> ");
		scanf("\n");
		fgets(moviename[l][c-49],50,stdin);
		for(k=0;k<50;k++) { if(moviename[l][c-49][k]=='\n') { moviename[l][c-49][k]='\0';
															 break; } }
		rewind(fp);
		vinfo.vregnumber=regnumber;
		strcpy(vinfo.vpassword,password);
		for(i=0;i<3;i++) { for(j=0;j<7;j++) { strcpy(vinfo.vmoviename[i][j],moviename[i][j]);
						   for(k=0;k<3;k++) { vinfo.vmovierate[i][j][k]=movierate[i][j][k]; } } 
											  vinfo.vmn[i]=mn[i]; }
		fwrite(&vinfo,sizeof(vinfo),1,fp);
		rewind(fp);
		goto n_again;
	}
	
	
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	void welcome()
	{
		char c;
		printf("\033c");
		printf("\n\n\n\n");
		printf("\n     ||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||");
		printf("\n     ||                                                                    ||");
		printf("\n     ||    ||    ||  ||||||  ||         |||||  ||||||   ||    ||  ||||||   ||");
		printf("\n     ||    ||    ||  ||      ||        ||     ||    ||  |||  |||  ||       ||");
		printf("\n     ||    || || ||  ||||||  ||   |||| ||     ||    ||  || || ||  ||||||   ||");
		printf("\n     ||    |||  |||  ||      ||        ||     ||    ||  ||    ||  ||       ||");
		printf("\n     ||    ||    ||  ||||||  ||||||     |||||  ||||||   ||    ||  ||||||   ||");
		printf("\n     ||                                                                    ||");
		printf("\n     ||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||");
		printf("\n\n         To continue press enter key      .........      ");
		c=getch();
		home();
	}
		
	void home()
	{
		char c;
		adminvar=0;
		printf("\033c");
		printf("\n\n\n");
		printf("\n                     ......Book the Cinema tickets with......                ");
		printf("\n     ||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||");
		printf("\n     ||                                                                    ||");
		printf("\n     ||     ||||| |||||| ||   || ||||||       |||||   ||||   ||||  ||  ||  ||");
		printf("\n     ||    ||       ||   |||  || ||           ||  || ||  || ||  || || ||   ||");
		printf("\n     ||    ||       ||   || | || ||||   ||||  |||||  ||  || ||  || ||||    ||");
		printf("\n     ||    ||       ||   ||  ||| ||           ||  || ||  || ||  || || ||   ||");
		printf("\n     ||     ||||| |||||| ||   || ||||||       |||||   ||||   ||||  ||  ||  ||");
		printf("\n     ||                                                                    ||");
		printf("\n     ||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||");
		printf("\n\n           To continue (enter any key)...      ");
		c=getch();
		login();
	}
	
	void thankyou()
	{	
		char c;
		printf("\033c");
		printf("\n\n\n");
		printf("\n     ||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||");
		printf("\n     ||                                                                    ||");
		printf("\n     ||   |||||| ||  ||    |||   ||   || ||  ||   ||    ||  |||||  ||  ||  ||");
		printf("\n     ||     ||   ||  ||   || ||  |||  || || ||     ||  ||  ||   || ||  ||  ||");
		printf("\n     ||     ||   ||||||  ||   || || | || ||||  ||||  ||    ||   || ||  ||  ||");
		printf("\n     ||     ||   ||  ||  ||||||| ||  ||| || ||       ||    ||   || ||  ||  ||");
		printf("\n     ||     ||   ||  ||  ||   || ||   || ||  ||      ||     |||||   ||||   ||");
		printf("\n     ||                                                                    ||");
		printf("\n     ||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||<<<<<<<<||>>>>>>>>||");
		printf("\n\n         Home (0)                                         Exit (enter)     ");
		printf("\n                                         ");
		c=getch();
		if(c=='0')
		{ home(); }
		else
		{  printf("\n\n...");
		   exit(1); }
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
