#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

typedef struct
{
	char formula[200];//产生式
}grammarElement;
grammarElement gramOldSet[200];//原始文法的产生式集
char terSymbol[200];//终结符号
char non_ter[200];//非终结符号
char allSymbol[400];//所有符号
char firstSET[100][100];//各产生式右部的FIERST集
char followSET[100][100];//各产生式左部的FOLLOW集
int M[200][200];//分析表
string a;//输入串
stack<char> s;//分析栈
int n=0,non=0,ter=0,all=0;//n为产生式的个数，non为非终结符的个数，ter为终结符的个数,all为所有符号的个数
int first[200]={0};//记录每一个非终结符FIRST集里终结符的个数
int follow[200]={0};//记录每个非终结符FOLLOW集里终结符的个数

void input(){
	//flag判断非终结符数组里有没有和当前要加入的非终结符重复，flag1判断终结符数组里有没有和当前要加入的终结符重复,flag2判断产生式是否有‘|’
	int flag=0,flag1=0,flag2=0;
	cout<<"请输入产生式的个数：";
	cin>>n;
	cout<<"请输入产生式(用$代表epsilon)："<<endl;
	for (int i=0;i<n;i++){
		for(int j=0;j<200;j++)
			gramOldSet[i].formula[j]=0;
		cin>>gramOldSet[i].formula;
	}
	for(int i=0;i<n;i++){//去除'|'
		for(int j=strlen(gramOldSet[i].formula);j>=0;j--){
			if(gramOldSet[i].formula[j]=='|'){
				flag2=j;
				int temp=strlen(gramOldSet[i].formula);
				gramOldSet[i].formula[j]=0;
			n=n+1;
			gramOldSet[n-1].formula[0]=gramOldSet[i].formula[0];
			gramOldSet[n-1].formula[1]='-';
			gramOldSet[n-1].formula[2]='>';
			temp=temp-j+2;
			for(int m=3;m<temp;m++){
				j=j+1;
				gramOldSet[n-1].formula[m]=gramOldSet[i].formula[j];
				gramOldSet[i].formula[j]=0;
			}
			j=flag2;
		}
	}
	}
	//for(int i=0;i<strlen(gramOldSet[n].formula);i++)
	//cout<<gramOldSet[n].formula[i];
	//if(flag2!=0){
		//cout<<"去除'|'之后的产生式为："<<endl;
		//for(int i=0;i<n;i++){
			//for(int j=0;j<strlen(gramOldSet[i].formula);j++)
				//cout<<gramOldSet[i].formula[j];
			//cout<<endl;
		//}
	//}
	for(int i=0;i<n;i++){//对每一个产生式分析
		for(int j=0;j<strlen(gramOldSet[i].formula);j++){//对具体的产生式符号分析
			if(gramOldSet[i].formula[j]<='Z'&&gramOldSet[i].formula[j]>='A'){//大写英文字母即是反非终结符
				flag=0;
				for(int m=0;m<non;m++){
					if(non_ter[m]==gramOldSet[i].formula[j])
						flag=1;//有重复则flag置为1
				}
				if(flag==0){
					non_ter[non]=gramOldSet[i].formula[j];
					non++;
				}	
			}
			else
			{
				flag1=0;
				//if(gramOldSet[i].formula[j]=='|'){
					//flag2=1;//标记出现了‘|’
					//j=j+0;//因为循环里有j++了，这里不用重复加了
					//n=n+1;
					//gramOldSet[n].formula[0]=gramOldSet[i].formula[0];
					//gramOldSet[n].formula[1]='-';
					//gramOldSet[n].formula[2]='>';
					//for(int m=3;m<strlen(gramOldSet[i].formula);m++)
						//if(gramOldSet[i].formula[j+1]!='|'||strlen(gramOldSet[i].formula)!=j)
							//gramOldSet[n].formula[m]=gramOldSet[i].formula[j++];

				//}
				if(gramOldSet[i].formula[j]=='-'&&gramOldSet[i].formula[j+1]=='>')
					j=j+1;
				else{
					for(int m=0;m<ter;m++){
						if(terSymbol[m]==gramOldSet[i].formula[j])
						flag1=1;
					}
					if(flag1==0){
					terSymbol[ter]=gramOldSet[i].formula[j];
					ter++;
					}	
				}
			}
		}
	}
	if(flag2!=0){
		cout<<"去除'|'之后的产生式为："<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<strlen(gramOldSet[i].formula);j++)
				cout<<gramOldSet[i].formula[j];
			cout<<endl;
		}
	}

	cout<<"非终结符：";
	for(int i=0;i<non;i++){
		allSymbol[all]=non_ter[i];
		all++;
		cout<<non_ter[i];
		cout<<"\t";
	}
	cout<<endl;
	cout<<"终结符：";
	for(int i=0;i<ter;i++){
		allSymbol[all]=terSymbol[i];
		all++;
		cout<<terSymbol[i];
		cout<<"\t";
	}
	cout<<endl;
	cout<<"所有符号：";
	for(int i=0;i<all;i++){
		cout<<allSymbol[i];
		cout<<"\t";
	}
	cout<<endl;
}
bool isnon_ter(char ch){//判断一个字符是否是非终结符
	for(int i=0;i<non;i++){
		if(ch==non_ter[i]){
			return true;
		}
	}
	return false;
}
bool isterSymbol(char ch){//判断一个字符是否是终结符
	for(int a=0;a<ter;a++){
		if(ch==terSymbol[a]){
			return true;
		}
	}
	return false;
}
bool isfirstSET(char ch){//判断一个非终结符是否求过FIRST集
	int i;
	for(i=0;i<non;i++)
		if(ch==non_ter[i]){
			if(isterSymbol(firstSET[i][0])==true)
				return true;
		}
		return false;
}
bool isfirstepsilon(char ch){//判断非终结符可推出空字
	char a[200];
	for(int m=0;m<200;m++)
		a[m]=0;
	for(int j=0;j<n;j++){//找非终结符所在的产生式
			if(ch==gramOldSet[j].formula[0]){
				for(int m=0;m<(strlen(gramOldSet[j].formula));m++)//存入a中
					a[m]=gramOldSet[j].formula[m];
				if(a[3]=='$'){
					return true;
					break;
				}
				else {
					for(int m=3;m<strlen(a);m++)
					if(a[m]=='|'&&a[m+1]=='$'){
						return true;
						break;
					}
				}
			}
	}
	return false;
}
bool isfollowSET(char ch){//判断一个非终结符是否求过FOLLOW集
	int i;
	for(i=0;i<non;i++)
		if(ch==non_ter[i]){
			if(isterSymbol(followSET[i][0])==true)
				return true;
			for(int m=0;m<follow[i];m++){
				if(followSET[i][m]=='#')
					return true;
			}

		}
		return false;
}
int non_position(char ch){//返回非终结符在非终结符字符串中的位置
	for(int j=0;j<non;j++){
		if(ch==non_ter[j]){
				return j;
			}
	}
}
int ter_position(char ch){//返回终结符在终结符字符串中的位置
	for(int j=0;j<ter;j++){
		if(ch==terSymbol[j])
			return j;
	}

}
void printtable(int i){//输出第i条产生式
	if(i==-1)
		cout<<"ERROR!";
	else
		for(int j=0;j<strlen(gramOldSet[i].formula);j++){
		cout<<gramOldSet[i].formula[j];
	}
		cout<<"\t\t";

}
bool isterepsilon(char ch){//判断一个字符是否是空字
	if(ch=='$'){
		return true;
	}
	return false;
}
bool isfirstSETepsilon(int i){//判断第i个非终结符First集中是否有空字 
	for(int m=0;m<first[i];m++){
		if(firstSET[i][m]=='$')
			return true;
	}
	return false;
}
void error(){
	cout<<"输入串错误！"<<endl;
}
void correct(){
	cout<<"分析成功！"<<endl;
}

void firstset(int i){//设置第i个非终结符的first集 
	char a[200];//每次找到非终结符所在的产生式就把该条产生式存入数组a中分析
	int flag=0;
	for(int m=0;m<200;m++)
		a[m]=0;
	for(int j=0;j<n;j++){//找非终结符所在的产生式
		if(non_ter[i]==gramOldSet[j].formula[0]){
			for(int m=0;m<(strlen(gramOldSet[j].formula));m++)//存入a中
				a[m]=gramOldSet[j].formula[m];
			//cout<<strlen(a);
			/*判断产生式右部第一个字符是epsilon或者是终结符，即X->a或者X->$*/
			if(a[3]=='$'){
				for(int m=0;m<first[i]+1;m++){
					if('$'==firstSET[i][m])
						break;
					else {
						if(m==first[i]){
						firstSET[i][first[i]]='$';
						first[i]++;
						break;
						}
					}
				}
				continue;//分析下一条非终结符开始的产生式 
			}
			else if(isterSymbol(a[3])==true){
				for(int m=0;m<first[i]+1;m++){
					if(a[3]==firstSET[i][m])
						break;
					else{
						if(m==first[i]){
						firstSET[i][first[i]]=a[3];
						first[i]++;
						break;
						}
					}
				}
				continue;//分析下一条非终结符开始的产生式 
			}
			else if(isnon_ter(a[3])==true){//判断产生式右部第一个字符是否是非终结符
				if(non_ter[i]==a[3])//该非终结符等于当前字符
					continue;
				else if(isfirstSET(a[3])==false){//该非终结符不等于当前字符且没有求过first集
					for(int m=0;m<non;m++)
						if(a[3]==non_ter[m])
							flag=m;//判断是第几个非终结符
					firstset(flag);//递归调用求其first集
					for(int m=0;m<first[flag];m++){//并入
						for(int f=0;f<first[i]+1;f++){
							if(firstSET[i][f]==firstSET[flag][m])
							break;
							else{
								if(f==first[i]){
									firstSET[i][first[i]]=firstSET[flag][m];
									first[i]++;
									break;
								}
							}
						}
					}
				}
				else if(isfirstSET(a[3])==true){//该非终结符不等于当前字符且求过first集
						flag=non_position(a[3]);
						for(int m=0;m<first[flag];m++){//并入
						for(int f=0;f<first[i]+1;f++){
							if(firstSET[i][f]==firstSET[flag][m])
							break;
							else{
								if(f==first[i]){
									firstSET[i][first[i]]=firstSET[flag][m];
									first[i]++;
									break;
								}
							}
						}
					}
				}

			}
			if(isfirstepsilon(a[3])==true){
				if(strlen(a)>4){//右部首符可推出空且非最后一个字符
					if(isnon_ter(a[4])==true&&isfirstSET(a[4])==true){
						flag=non_position(a[4]);
						for(int m=0;m<first[flag];m++){//并入
							for(int f=0;f<first[i]+1;f++){
								if(firstSET[i][f]==firstSET[flag][m])
									break;
								else{
									if(f==first[i]){
									firstSET[i][first[i]]=firstSET[flag][m];
									first[i]++;
									break;
									}
								}
							}
						}
					}
					else if(isterSymbol(a[4])==true){
						for(int m=0;m<first[i]+1;m++){
							if(a[4]==firstSET[i][m])
								break;
							else{
								if(m==first[i]){
								firstSET[i][first[i]]=a[4];
								first[i]++;
								break;
								}
							}
						}
					}
					continue;
				}
				else if(isfirstSET(a[4])==false){
					for(int m=0;m<non;m++)
						if(a[4]==non_ter[m])
							flag=m;//判断是第几个非终结符
					firstset(flag);//递归调用求其first集
					for(int m=0;m<first[flag];m++){//并入
						for(int f=0;f<first[i]+1;f++){
							if(firstSET[i][f]==firstSET[flag][m])
							break;
							else{
								if(f==first[i]){
									firstSET[i][first[i]]=firstSET[flag][m];
									first[i]++;
									break;
								}
							}
						}
					}
				}
			}
			if(isfirstepsilon(a[3])==true&&strlen(a)==4){
				for(int m=0;m<first[i]+1;m++){
					if('$'==firstSET[i][m])
						break;
				else {
					if(m==first[i]){
					firstSET[i][first[i]]='$';
					first[i]++;
					break;
					}
				}
				}
				continue;
			}
			else
				continue;
		}
	}
}

void followset(int i){
	char a[200];
	int flag=0;//标记产生式左部非终结符在非终结符字符串中的位置
	int flag1=0;//标记非终结符在产生式中的位置
	if(i==0){
		followSET[i][follow[i]]='#';
		follow[i]++;
	}
	for(int m=0;m<200;m++)
			a[m]=0;
	for(int j=0;j<n;j++){//找右部含有当前非终结符所在的产生式
		for(int z=3;z<(strlen(gramOldSet[j].formula));z++){
			if(non_ter[i]==gramOldSet[j].formula[z]){
				flag1=z;
				for(int m=0;m<(strlen(gramOldSet[j].formula));m++)//存入a中
					a[m]=gramOldSet[j].formula[m];
				if(flag1==strlen(a)-1){//如果当前非终结符在该产生式最后
					if(isfollowSET(a[0])==true){//且该产生式左部非终结符求过FOLLOW集
						for(int m=0;m<non;m++){//求该产生式左部非终结符在非终结符字符串中的位置
							if(a[0]==non_ter[m])
								flag=m;
						}
						for(int m=0;m<follow[flag];m++){//并入
							for(int f=0;f<follow[i]+1;f++){
								if(followSET[i][f]==followSET[flag][m])
								break;
								else{
									if(f==follow[i]){
										followSET[i][follow[i]]=followSET[flag][m];
										follow[i]++;
										break;
									}
								}
							}
						}
						continue;
					}
					else{
						for(int m=0;m<non;m++){//求该产生式左部非终结符在非终结符字符串中的位置
							if(a[0]==non_ter[m])
								flag=m;
						}
						followset(flag);
					}
				}
				else if(flag1+1==strlen(a)-1){// 如果非终结符在产生式的倒数第二个位置 
					if(isnon_ter(a[flag1+1])==true){//如果倒数第一个为非终结符 
						if(isfirstepsilon(a[flag1+1])==true){//如果能推出空 
							if(isfollowSET(a[flag1+1])==true){
								flag=non_position(a[0]);
								for(int m=0;m<follow[flag];m++){//并入
									for(int f=0;f<follow[i]+1;f++){
										if(followSET[i][f]==followSET[flag][m])
											break;
										else{
											if(f==follow[i]){
												followSET[i][follow[i]]=followSET[flag][m];
												follow[i]++;
												break;
											}
										}
									}
								}
								//continue;
							}//
						//}
					//else {
					for(int m=0;m<non;m++){//求a[flag1+1]在非终结符字符串中的位置
							if(a[flag1+1]==non_ter[m])
								flag=m;
						}
					//firstset(flag);
					for(int m=0;m<first[flag];m++){//并入
						for(int f=0;f<follow[i]+1;f++){
							if(followSET[i][f]==firstSET[flag][m]||firstSET[flag][m]=='$')
								break;
							else{
								if(f==follow[i]){
									followSET[i][follow[i]]=firstSET[flag][m];
									follow[i]++;
									break;
								}
							}
						}
					}
					continue;
				//}
					}
					}
					else if(isterSymbol(a[flag1+1])==true){//如果最后一个字符为终结符 
						followSET[i][follow[i]]=a[flag1+1];
						follow[i]++;
					}

				}



			}

		}

}
}

void alalysetable(char ch0){
	char a[200];
	int flag=0,flag1=0,flag2=0;//flag记录非终结符在非终结符字符串中的位置，flag2记录当前非终结符所在的产生式序号
	for(int i=0;i<200;i++){
		a[i]=0;
	}//初始化a;
	for(int i=0;i<n;i++){//遍历每一条产生式
		flag=non_position(ch0);
		if(ch0==gramOldSet[i].formula[0]){
			flag2=i;
			for(int m=0;m<(strlen(gramOldSet[i].formula));m++)//存入a中  
					a[m]=gramOldSet[i].formula[m];
			if(isterSymbol(a[3])==true&&a[3]!='$'){//如果产生式的FIRST集是终结符且不是epsilon
				M[flag][ter_position(a[3])]=flag2;
			}
			if(a[3]=='$'){//如果产生式的FIRST集是终结符且是epsilon
				for(int k=0;k<follow[flag];k++){//遍历FOLLOW集
						M[flag][ter_position(followSET[flag][k])]=flag2;//对该FOLLOW集中的每一个终结符位置填上该产生式
					}
			}
			if(isnon_ter(a[3])==true&&isfirstSETepsilon(non_position(a[3]))==false){//产生式的首符是非终结符且该非终结符的FIRST集里没有epsilon
				for(int m=0;m<first[non_position(a[3])];m++){
					M[flag][ter_position(firstSET[non_position(a[3])][m])]=flag2;
				}
			}
			if(isnon_ter(a[3])==true&&isfirstSETepsilon(non_position(a[3]))==true){//产生式的首符是非终结符且该非终结符的FIRST集里有epsilon
				for(int m=0;m<first[non_position(a[3])];m++){
					if(firstSET[non_position(a[3])][m]!='$')//没有遇到epsilon时正常添加
						M[flag][ter_position(firstSET[non_position(a[3])][m])]=flag2;
					else //遇到epsilon则查看FOLLOW集
						for(int k=0;k<follow[flag];k++){//遍历FOLLOW集
						M[flag][ter_position(followSET[flag][k])]=flag2;//对该FOLLOW集中的每一个终结符位置填上该产生式
					}
				}
			}		
	}
	}
}
void control(){
	bool flag=true,flag1=true;
	int flag2=0,flag3=0;
	char x,b;
	//char p[100]={0};
	int i=0,j=0,length=0,alength=0;
	cout<<"请输入欲分析的串（以#结束）：";
	cin>>a;
	alength=a.length()-1;
	s.push('#');
	s.push(gramOldSet[0].formula[0]);
	//cout<<"符号栈"<<"\t"<<"字符串"<<"\t"<<"所用产生式"<<endl;
	//cout<<'#'<<gramOldSet[0].formula[0]<<"\t";
	/*for(int m=0;m<alength;m++)
		cout<<a[m];
	cout<<"\t";*/
	b=a[i];
	while(flag){
		flag1=true;
		x=s.top();
		s.pop();
		if(isterSymbol(x)==true){
			if(x==b){
				b=a[++i];
				length=length-1;
				/*for(int m=0;m<length;m++){
					cout<<a[m];
				}
				cout<<"\t";*/
			}
			else {error();break;}
		}
		else if(x=='#'){
			if(x==b)
				flag=false;
			else {error();break;}
		}
		else if(M[non_position(x)][ter_position(b)]!=-1){
			j=M[non_position(x)][ter_position(b)];
			if(gramOldSet[j].formula[3]=='$')
				continue;
			length=strlen(gramOldSet[j].formula);
			cout<<"匹配("<<x<<','<<b<<')'<<"\t";
			cout<<"所用产生式为：";
			for(int m=0;m<length;m++)
				cout<<gramOldSet[j].formula[m];
			cout<<endl;
			for(int m=length-1;m>2;m--){
				s.push(gramOldSet[j].formula[m]);
				/*cout<<gramOldSet[j].formula[m];*/
			}
			/*cout<<"\t";*/
			flag1=false;
			flag2=1;
			flag3=j;
		}
		else {error();break;}
		/*if(flag1==true){
			cout<<endl;
		}
		if(flag2==1){
			for(int m=0;m<length;m++)
				cout<<gramOldSet[j].formula[m];
			cout<<endl;

		}*/
	}
	if(flag==false)
		correct();
}


int main(){
	int flags=-1;
	input();
	for(int i=0;i<200;i++)
		for(int j=0;j<200;j++)
			M[i][j]=-1;
	for(int i=0;i<non;i++){
		if(isfirstSET(non_ter[i])==false)
			firstset(i);
		cout<<non_ter[i];
		cout<<"的FIRST集为：";
		for(int m=0;m<first[i];m++){
			cout<<firstSET[i][m];
			cout<<"\t";
		}
		cout<<endl;
	}
	for(int i=non-1;i>=0;i--){
		if(isfollowSET(non_ter[i])==false)
			followset(i);
		cout<<non_ter[i];
		cout<<"的FOLLOW集为：";
		for(int m=0;m<follow[i];m++){
			cout<<followSET[i][m];
			cout<<"\t";
		}
		cout<<endl;
	}
	for(int i=0;i<non;i++){
		alalysetable(non_ter[i]);
	}
	cout<<"预测分析表如下："<<endl;
	for(int i=0;i<ter;i++){
		if(isterepsilon(terSymbol[i])==true)
			flags=i;
		else
			cout<<"\t"<<terSymbol[i]<<"\t";
	}
	cout<<endl;
	for(int i=0;i<non;i++){
		for(int j=0;j<ter;j++){
			if(j==0)
				cout<<non_ter[i]<<"\t";
			if(flags==j)
			continue;
			printtable(M[i][j]);
		}
		cout<<endl;
	}
	control();
	

	return 0;
}

//S->a|b|(T)
//T->SB
//B->,SB|$   
//(a,b)# 
