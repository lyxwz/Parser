#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

typedef struct
{
	char formula[200];//����ʽ
}grammarElement;
grammarElement gramOldSet[200];//ԭʼ�ķ��Ĳ���ʽ��
char terSymbol[200];//�ս����
char non_ter[200];//���ս����
char allSymbol[400];//���з���
char firstSET[100][100];//������ʽ�Ҳ���FIERST��
char followSET[100][100];//������ʽ�󲿵�FOLLOW��
int M[200][200];//������
string a;//���봮
stack<char> s;//����ջ
int n=0,non=0,ter=0,all=0;//nΪ����ʽ�ĸ�����nonΪ���ս���ĸ�����terΪ�ս���ĸ���,allΪ���з��ŵĸ���
int first[200]={0};//��¼ÿһ�����ս��FIRST�����ս���ĸ���
int follow[200]={0};//��¼ÿ�����ս��FOLLOW�����ս���ĸ���

void input(){
	//flag�жϷ��ս����������û�к͵�ǰҪ����ķ��ս���ظ���flag1�ж��ս����������û�к͵�ǰҪ������ս���ظ�,flag2�жϲ���ʽ�Ƿ��С�|��
	int flag=0,flag1=0,flag2=0;
	cout<<"���������ʽ�ĸ�����";
	cin>>n;
	cout<<"���������ʽ(��$����epsilon)��"<<endl;
	for (int i=0;i<n;i++){
		for(int j=0;j<200;j++)
			gramOldSet[i].formula[j]=0;
		cin>>gramOldSet[i].formula;
	}
	for(int i=0;i<n;i++){//ȥ��'|'
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
		//cout<<"ȥ��'|'֮��Ĳ���ʽΪ��"<<endl;
		//for(int i=0;i<n;i++){
			//for(int j=0;j<strlen(gramOldSet[i].formula);j++)
				//cout<<gramOldSet[i].formula[j];
			//cout<<endl;
		//}
	//}
	for(int i=0;i<n;i++){//��ÿһ������ʽ����
		for(int j=0;j<strlen(gramOldSet[i].formula);j++){//�Ծ���Ĳ���ʽ���ŷ���
			if(gramOldSet[i].formula[j]<='Z'&&gramOldSet[i].formula[j]>='A'){//��дӢ����ĸ���Ƿ����ս��
				flag=0;
				for(int m=0;m<non;m++){
					if(non_ter[m]==gramOldSet[i].formula[j])
						flag=1;//���ظ���flag��Ϊ1
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
					//flag2=1;//��ǳ����ˡ�|��
					//j=j+0;//��Ϊѭ������j++�ˣ����ﲻ���ظ�����
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
		cout<<"ȥ��'|'֮��Ĳ���ʽΪ��"<<endl;
		for(int i=0;i<n;i++){
			for(int j=0;j<strlen(gramOldSet[i].formula);j++)
				cout<<gramOldSet[i].formula[j];
			cout<<endl;
		}
	}

	cout<<"���ս����";
	for(int i=0;i<non;i++){
		allSymbol[all]=non_ter[i];
		all++;
		cout<<non_ter[i];
		cout<<"\t";
	}
	cout<<endl;
	cout<<"�ս����";
	for(int i=0;i<ter;i++){
		allSymbol[all]=terSymbol[i];
		all++;
		cout<<terSymbol[i];
		cout<<"\t";
	}
	cout<<endl;
	cout<<"���з��ţ�";
	for(int i=0;i<all;i++){
		cout<<allSymbol[i];
		cout<<"\t";
	}
	cout<<endl;
}
bool isnon_ter(char ch){//�ж�һ���ַ��Ƿ��Ƿ��ս��
	for(int i=0;i<non;i++){
		if(ch==non_ter[i]){
			return true;
		}
	}
	return false;
}
bool isterSymbol(char ch){//�ж�һ���ַ��Ƿ����ս��
	for(int a=0;a<ter;a++){
		if(ch==terSymbol[a]){
			return true;
		}
	}
	return false;
}
bool isfirstSET(char ch){//�ж�һ�����ս���Ƿ����FIRST��
	int i;
	for(i=0;i<non;i++)
		if(ch==non_ter[i]){
			if(isterSymbol(firstSET[i][0])==true)
				return true;
		}
		return false;
}
bool isfirstepsilon(char ch){//�жϷ��ս�����Ƴ�����
	char a[200];
	for(int m=0;m<200;m++)
		a[m]=0;
	for(int j=0;j<n;j++){//�ҷ��ս�����ڵĲ���ʽ
			if(ch==gramOldSet[j].formula[0]){
				for(int m=0;m<(strlen(gramOldSet[j].formula));m++)//����a��
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
bool isfollowSET(char ch){//�ж�һ�����ս���Ƿ����FOLLOW��
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
int non_position(char ch){//���ط��ս���ڷ��ս���ַ����е�λ��
	for(int j=0;j<non;j++){
		if(ch==non_ter[j]){
				return j;
			}
	}
}
int ter_position(char ch){//�����ս�����ս���ַ����е�λ��
	for(int j=0;j<ter;j++){
		if(ch==terSymbol[j])
			return j;
	}

}
void printtable(int i){//�����i������ʽ
	if(i==-1)
		cout<<"ERROR!";
	else
		for(int j=0;j<strlen(gramOldSet[i].formula);j++){
		cout<<gramOldSet[i].formula[j];
	}
		cout<<"\t\t";

}
bool isterepsilon(char ch){//�ж�һ���ַ��Ƿ��ǿ���
	if(ch=='$'){
		return true;
	}
	return false;
}
bool isfirstSETepsilon(int i){//�жϵ�i�����ս��First�����Ƿ��п��� 
	for(int m=0;m<first[i];m++){
		if(firstSET[i][m]=='$')
			return true;
	}
	return false;
}
void error(){
	cout<<"���봮����"<<endl;
}
void correct(){
	cout<<"�����ɹ���"<<endl;
}

void firstset(int i){//���õ�i�����ս����first�� 
	char a[200];//ÿ���ҵ����ս�����ڵĲ���ʽ�ͰѸ�������ʽ��������a�з���
	int flag=0;
	for(int m=0;m<200;m++)
		a[m]=0;
	for(int j=0;j<n;j++){//�ҷ��ս�����ڵĲ���ʽ
		if(non_ter[i]==gramOldSet[j].formula[0]){
			for(int m=0;m<(strlen(gramOldSet[j].formula));m++)//����a��
				a[m]=gramOldSet[j].formula[m];
			//cout<<strlen(a);
			/*�жϲ���ʽ�Ҳ���һ���ַ���epsilon�������ս������X->a����X->$*/
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
				continue;//������һ�����ս����ʼ�Ĳ���ʽ 
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
				continue;//������һ�����ս����ʼ�Ĳ���ʽ 
			}
			else if(isnon_ter(a[3])==true){//�жϲ���ʽ�Ҳ���һ���ַ��Ƿ��Ƿ��ս��
				if(non_ter[i]==a[3])//�÷��ս�����ڵ�ǰ�ַ�
					continue;
				else if(isfirstSET(a[3])==false){//�÷��ս�������ڵ�ǰ�ַ���û�����first��
					for(int m=0;m<non;m++)
						if(a[3]==non_ter[m])
							flag=m;//�ж��ǵڼ������ս��
					firstset(flag);//�ݹ��������first��
					for(int m=0;m<first[flag];m++){//����
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
				else if(isfirstSET(a[3])==true){//�÷��ս�������ڵ�ǰ�ַ������first��
						flag=non_position(a[3]);
						for(int m=0;m<first[flag];m++){//����
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
				if(strlen(a)>4){//�Ҳ��׷����Ƴ����ҷ����һ���ַ�
					if(isnon_ter(a[4])==true&&isfirstSET(a[4])==true){
						flag=non_position(a[4]);
						for(int m=0;m<first[flag];m++){//����
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
							flag=m;//�ж��ǵڼ������ս��
					firstset(flag);//�ݹ��������first��
					for(int m=0;m<first[flag];m++){//����
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
	int flag=0;//��ǲ���ʽ�󲿷��ս���ڷ��ս���ַ����е�λ��
	int flag1=0;//��Ƿ��ս���ڲ���ʽ�е�λ��
	if(i==0){
		followSET[i][follow[i]]='#';
		follow[i]++;
	}
	for(int m=0;m<200;m++)
			a[m]=0;
	for(int j=0;j<n;j++){//���Ҳ����е�ǰ���ս�����ڵĲ���ʽ
		for(int z=3;z<(strlen(gramOldSet[j].formula));z++){
			if(non_ter[i]==gramOldSet[j].formula[z]){
				flag1=z;
				for(int m=0;m<(strlen(gramOldSet[j].formula));m++)//����a��
					a[m]=gramOldSet[j].formula[m];
				if(flag1==strlen(a)-1){//�����ǰ���ս���ڸò���ʽ���
					if(isfollowSET(a[0])==true){//�Ҹò���ʽ�󲿷��ս�����FOLLOW��
						for(int m=0;m<non;m++){//��ò���ʽ�󲿷��ս���ڷ��ս���ַ����е�λ��
							if(a[0]==non_ter[m])
								flag=m;
						}
						for(int m=0;m<follow[flag];m++){//����
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
						for(int m=0;m<non;m++){//��ò���ʽ�󲿷��ս���ڷ��ս���ַ����е�λ��
							if(a[0]==non_ter[m])
								flag=m;
						}
						followset(flag);
					}
				}
				else if(flag1+1==strlen(a)-1){// ������ս���ڲ���ʽ�ĵ����ڶ���λ�� 
					if(isnon_ter(a[flag1+1])==true){//���������һ��Ϊ���ս�� 
						if(isfirstepsilon(a[flag1+1])==true){//������Ƴ��� 
							if(isfollowSET(a[flag1+1])==true){
								flag=non_position(a[0]);
								for(int m=0;m<follow[flag];m++){//����
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
					for(int m=0;m<non;m++){//��a[flag1+1]�ڷ��ս���ַ����е�λ��
							if(a[flag1+1]==non_ter[m])
								flag=m;
						}
					//firstset(flag);
					for(int m=0;m<first[flag];m++){//����
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
					else if(isterSymbol(a[flag1+1])==true){//������һ���ַ�Ϊ�ս�� 
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
	int flag=0,flag1=0,flag2=0;//flag��¼���ս���ڷ��ս���ַ����е�λ�ã�flag2��¼��ǰ���ս�����ڵĲ���ʽ���
	for(int i=0;i<200;i++){
		a[i]=0;
	}//��ʼ��a;
	for(int i=0;i<n;i++){//����ÿһ������ʽ
		flag=non_position(ch0);
		if(ch0==gramOldSet[i].formula[0]){
			flag2=i;
			for(int m=0;m<(strlen(gramOldSet[i].formula));m++)//����a��  
					a[m]=gramOldSet[i].formula[m];
			if(isterSymbol(a[3])==true&&a[3]!='$'){//�������ʽ��FIRST�����ս���Ҳ���epsilon
				M[flag][ter_position(a[3])]=flag2;
			}
			if(a[3]=='$'){//�������ʽ��FIRST�����ս������epsilon
				for(int k=0;k<follow[flag];k++){//����FOLLOW��
						M[flag][ter_position(followSET[flag][k])]=flag2;//�Ը�FOLLOW���е�ÿһ���ս��λ�����ϸò���ʽ
					}
			}
			if(isnon_ter(a[3])==true&&isfirstSETepsilon(non_position(a[3]))==false){//����ʽ���׷��Ƿ��ս���Ҹ÷��ս����FIRST����û��epsilon
				for(int m=0;m<first[non_position(a[3])];m++){
					M[flag][ter_position(firstSET[non_position(a[3])][m])]=flag2;
				}
			}
			if(isnon_ter(a[3])==true&&isfirstSETepsilon(non_position(a[3]))==true){//����ʽ���׷��Ƿ��ս���Ҹ÷��ս����FIRST������epsilon
				for(int m=0;m<first[non_position(a[3])];m++){
					if(firstSET[non_position(a[3])][m]!='$')//û������epsilonʱ�������
						M[flag][ter_position(firstSET[non_position(a[3])][m])]=flag2;
					else //����epsilon��鿴FOLLOW��
						for(int k=0;k<follow[flag];k++){//����FOLLOW��
						M[flag][ter_position(followSET[flag][k])]=flag2;//�Ը�FOLLOW���е�ÿһ���ս��λ�����ϸò���ʽ
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
	cout<<"�������������Ĵ�����#��������";
	cin>>a;
	alength=a.length()-1;
	s.push('#');
	s.push(gramOldSet[0].formula[0]);
	//cout<<"����ջ"<<"\t"<<"�ַ���"<<"\t"<<"���ò���ʽ"<<endl;
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
			cout<<"ƥ��("<<x<<','<<b<<')'<<"\t";
			cout<<"���ò���ʽΪ��";
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
		cout<<"��FIRST��Ϊ��";
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
		cout<<"��FOLLOW��Ϊ��";
		for(int m=0;m<follow[i];m++){
			cout<<followSET[i][m];
			cout<<"\t";
		}
		cout<<endl;
	}
	for(int i=0;i<non;i++){
		alalysetable(non_ter[i]);
	}
	cout<<"Ԥ����������£�"<<endl;
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
