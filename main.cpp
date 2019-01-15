#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<Windows.h>
#pragma warning(disable: 4996)

#define name_index 2
#define word_index 1
#define case_array_index 4
using namespace std;
class Node
{
	public:
	Node* next;
	string data;
	
};
class myq
{
	public:
	Node* head;
	myq()
	{
		head = NULL;
	}
	int insert(string newdata)
	{
		
		
		if(head ==NULL)
		{
			Node * newnode = new Node();
			newnode->next = NULL;
			newnode->data = newdata;
			head = newnode;
			return 1;
		}
		else
		{
		   Node *temp = head;
		   if(temp->data==newdata)
		   {
		   	  return -1;
		   }
		   while(temp->next !=NULL)
		   {
		   		temp = temp->next;
		   		if(temp->data==newdata)
				   {
				   	  return -1;
				   }
		   }
		   Node * newnode = new Node();
		   temp->next = newnode;
		   newnode->data = newdata;
		   newnode->next = NULL;
		   return 1;	
		}
		
		
	}
	
};


char easytolower(char in) {
  if(in <= 'Z' && in >= 'A')
    return in - ('Z' - 'z');
  return in;
}

int main()
{
	ifstream database("input_db.txt");
	string buffer;
	myq checkdup;
	//------------- ������ �Է� �ޱ� ---------------//
	getline(database, buffer);
	std::transform(buffer.begin(), buffer.end(), buffer.begin(), easytolower);
	cout<<buffer<<endl;
	

////////////////////////////////////////////////////////////////////////////////////////////////////

	string dbname[40000]={};
	string dbword[40000]={};
	int dbindex=0;
	
	int adjust_nodb=0;
	int adjust_nodb_nodup=0;
	int adjust_1db=0;
	int adjust_1db_nodup=0;
	int adjust_2db=0;
	int adjust_2db_nodup=0;
	while(!database.eof())
	{
		getline(database, buffer);
		std::transform(buffer.begin(), buffer.end(), buffer.begin(), easytolower);
		//cout<<buffer<<endl;
		int p,p2;
		p=buffer.find(",");	
		int count=0;
		string tempword;
		string tempname;
		while(1)
		{
			p2=buffer.find(",",p+1);
			count++;
			if(count ==word_index)
			{
				tempword=buffer.substr(p+1,p2-p-1);
			//	cout<<tempword<<"//";
			}
			if(count ==name_index)
			{
				
					tempname=buffer.substr(p+1,p2-p-1);
			
					//cout<<tempname<<"//"<<tempword<<endl;
					
					if(tempname[0]=='\"')
					{
						tempname = tempname.substr(1,tempname.length());
					}
					if(tempname[tempname.length()-1]=='\"')
					{
						tempname = tempname.substr(0,tempname.length()-1);
					}
					if(tempword[0]=='\"')
					{
						tempword = tempword.substr(1,tempword.length());
					}
					if(tempword[tempword.length()-1]=='\"')
					{
						tempword = tempword.substr(0,tempword.length()-1);
					}	
									
					dbname[dbindex]=tempname;
					dbword[dbindex]=tempword;
					dbindex++;
				
			}	
			if(p2<0) break;
			p=p2;
		}
	}
	/*
	for(int i = 0 ; i<dbindex;i++)
	{
		cout<<dbname[i]<<"++"<<dbword[i]<<endl;
	}
	*/
	
	database.close();


	ifstream case1("input_case.txt");
	ofstream jsonout("output.txt"); 
	getline(case1, buffer);
	std::transform(buffer.begin(), buffer.end(), buffer.begin(), easytolower);
//	cout<<buffer<<endl;
	while(!case1.eof())
	{
		getline(case1, buffer);
		std::transform(buffer.begin(), buffer.end(), buffer.begin(), easytolower);
		//cout<<buffer<<endl;
		int p,p2;
		p=buffer.find(",");	
		int count=0;
			while(1)
			{
				p2=buffer.find(",",p+1);
				count++;
				string temp_case_array;
				if(count ==case_array_index)
				{
					temp_case_array=buffer.substr(p+1,p2-p-1);
					if(temp_case_array[0]=='\"')
					{
						temp_case_array = temp_case_array.substr(1,temp_case_array.length());
					}
					if(temp_case_array[temp_case_array.length()-1]=='\"')
					{
						temp_case_array = temp_case_array.substr(0,temp_case_array.length()-1);
					}
					
				//	cout<<"����"<<temp_case_array<<endl;
					string tca_array[1000]={};
					int tca_array_index=0;
					int pp=-1;
					int start=0;
					while(1)
					{
						
						pp=temp_case_array.find('/',start);
						if(pp>0)
						{
							tca_array[tca_array_index]=temp_case_array.substr(start,pp-start);
							
						//	cout<<"+"<<tca_array[tca_array_index]<<"+"<<endl;
							
							
							tca_array_index++;
							start =pp+1;
						}
						else
						{
							tca_array[tca_array_index]=temp_case_array.substr(start,temp_case_array.length()-start);
						//	cout<<"+"<<tca_array[tca_array_index]<<"+"<<endl;
							tca_array_index++;
							break;
						}

					
						
					}
					for(int j = 0 ;j<tca_array_index;j++)
					{
						//cout<<"="<<tca_array[j]<<"="<<endl;
						//ģ���� #�� �ִٸ� ��ü �ؾ���
						pp=-10;
						pp=tca_array[j].find("#");
						
						if(pp>=0)
						{
							//cout<<"="<<tca_array[j]<<"="<<endl;
							//////////���⼱ ���������� ��ü�ɿ�����
							//dbname�ϰ�  #asfasf# ������ ���� ��ġ�ϸ� dbword�� �ٲ������ �ٵ� dbword�� ������ŭ �� ���ؼ� 
							int sharpcount=0;
							for(int k=0 ; k <tca_array[j].length();k++)
							{
								if(tca_array[j][k]=='#')sharpcount++;					
							} 
							
							if(sharpcount==2)
							{
////////////////////////////////////////////////////////////////////////////////////DB 1��¥��/////////////////////////////////////////////////////////////////// 
								int sharp_index1 = tca_array[j].find("#");
								int sharp_index2 = tca_array[j].find("#",sharp_index1+1);
								//cout<<"����"<<tca_array[j]<<"//"<<"sharp_index1:"<<sharp_index1<<"sharp_index2:"<<sharp_index2<<endl;
								string finddbname = tca_array[j].substr((sharp_index1+1),(sharp_index2-1)-(sharp_index1));
								//cout<<"ã����:"<<finddbname<<endl;
								//ã�� db����ã��
								int exist_dbcount=0;
								/*
									for(int i = 0 ; i<dbindex;i++)
									{
										cout<<dbname[i]<<"++"<<dbword[i]<<endl;
									}
								*/
								for(int e= 0 ; e<dbindex;e++)
								{
									if(dbname[e]==finddbname)
									{
										exist_dbcount++;
									}
								} 
								
								//cout<<exist_dbcount<<endl;
								
								if(exist_dbcount!=0)
								{
									//cout<<"����"<<tca_array[j]<<endl;
									
									int tempdbindex=1;
									for(int i = 0 ; i<exist_dbcount;i++)
									{
										string copystring = tca_array[j];
										int searchcount=0;
										for(int u = 0 ; u<dbindex; u++)
										{
											if(dbname[u]==finddbname)
											{
												searchcount++;
												if(searchcount==tempdbindex)
												{
													tempdbindex++;
													/*
													if(dbname[u]=="number")
													{
														cout<<"������:"<<copystring<<"[[]]"<<sharp_index1<<"//"<<sharp_index2<<endl;
													 }
													 */ 
													copystring.replace(sharp_index1,sharp_index2-sharp_index1+1,"");
													copystring.insert(sharp_index1,dbword[u]);
													/*
													if(dbname[u]=="number")
													{
														cout<<"Ȯ�ο�:"<<copystring<<endl;
													 }
													 */ 
													break;
												}
												else
												{
													
												}
												

											}
										}
										adjust_1db++;
										
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@�ߺ�ť�� �� �־��ּ� 
										if(checkdup.insert(copystring)==1)//!@#
										{//
											adjust_1db_nodup++;
											cout<<"[�ߺ��ƴ�]db1_���:"<<copystring<<endl;
												jsonout<<"{"<<endl;
										jsonout<<"\"name\": {"<<endl;
										jsonout<<"\"value\": \""<<copystring<<"\""<<endl;
										jsonout<<"}"<<endl;	        
										jsonout<<"},"<<endl;
										}
										else
										{
									//		cout<<"[�ߺ��Ӥ�]db��_���:"<<copystring<<endl;
										}
										//cout<<"db��_���:"<<copystring<<endl;
										/*
									
										*/
										//tca_array[j]�� sharp_index1 sharp_index2 ���� �о������
										//sharp_index1 �κп� inser�ؼ� finddbname�� ��ġ�ؼ� dbname[i]���� ��ġ�ؼ� dbword[i]�� ���Ʋ��ָ� 
									
									}
									
									
								}
								
								
							}
							/////////////////////////////DB1��¥����
							////////////////////////DB2��¥��///////////////////////////////////////////////////////////////////////// 
							else if(sharpcount==4)
							{
							//	cout<<"����"<<tca_array[j]<<endl;
								
								int sharp_index1 = tca_array[j].find("#");
								int sharp_index2 = tca_array[j].find("#",sharp_index1+1);
								int sharp_index3 = tca_array[j].find("#",sharp_index2+1);
								int sharp_index4 = tca_array[j].find("#",sharp_index3+1);
								string finddbname1 = tca_array[j].substr((sharp_index1+1),(sharp_index2-1)-(sharp_index1));
								string finddbname2 = tca_array[j].substr((sharp_index3+1),(sharp_index4-1)-(sharp_index3));
								//cout<<finddbname1<<" "<<finddbname2<<endl;
								
									int exist_dbcount1=0;
									int exist_dbcount2=0;
							
								for(int e= 0 ; e<dbindex;e++)////////////////////���⼭  if elseif �� �ҽ�  �ΰ� db�� ������� db������ �������� ġ���� 
								{
									if(dbname[e]==finddbname1)
									{
										exist_dbcount1++;
									}
									if(dbname[e]==finddbname2)
									{
										exist_dbcount2++;
									}
								} 
								
								if(exist_dbcount1!=0 && exist_dbcount2!=0)
								{
									cout<<"exist_dbcount1:"<<exist_dbcount1<<"exist_dbcount2:"<<exist_dbcount2<<"�ΰ���:"<<exist_dbcount1*exist_dbcount2<<endl;
									//��ŭ�ؾ� ��
									//tca_array[j]�� �ִ��༮����  ù �ѳ��� �񸣰� ���� db���Ѹ�ŭ �ݺ��� �������� 
									//���⼭ �밡�� �ʿ� 
									int tempdbindex=1;
									for(int t1 = 0 ; t1<exist_dbcount1;t1++)
									{
									    string copystring = tca_array[j];
										int searchcount=0;
										//���⼭ �ش粬 ���Ʋ��ְ� 1DB��  2DB�� �� ���Ʋ����� 
										for(int u = 0 ; u<dbindex; u++)
										{
											if(dbname[u]==finddbname1)
											{
												searchcount++; 
												if(searchcount==tempdbindex)
												{
													tempdbindex++;
													copystring.replace(sharp_index1,sharp_index2-sharp_index1+1,"");
													copystring.insert(sharp_index1,dbword[u]);
													break;	
												}
											}
										}
										//cout<<"db2���Ѱ��� ��������:"<<copystring<<endl;
										////////////////////////////////
										int tempdbindex2=1;
										for(int t2=0 ; t2<exist_dbcount2;t2++)
										{
											string copystring2 = copystring;
											int searchcount2=0;
											for(int u = 0 ; u<dbindex; u++)
											{
												if(dbname[u]==finddbname2)
												{
													searchcount2++; 
													if(searchcount2==tempdbindex2)
													{
														tempdbindex2++;
														sharp_index3 = copystring2.find("#");
														sharp_index4 = copystring2.find("#",sharp_index3+1);
														copystring2.replace(sharp_index3,sharp_index4-sharp_index3+1,"");
														copystring2.insert(sharp_index3,dbword[u]);
														
														break;	
													}
												}
												
											}
											//cout<<"db2�����ѻ���:"<<copystring2<<endl;
											
											adjust_2db++;

											if(checkdup.insert(copystring2)==1)//!@#
											{//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
												cout<<"[�ߺ��ƴ�]db2_���:"<<copystring2<<endl;
												jsonout<<"{"<<endl;
												jsonout<<"\"name\": {"<<endl;
												jsonout<<"\"value\": \""<<copystring2<<"\""<<endl;
												jsonout<<"}"<<endl;	        
												jsonout<<"},"<<endl; 
												adjust_2db_nodup++;
											}
											else
											{
												//�ߺ� 
											}
											////////���⼭�ؾ� 
		
										}
										///////////////////////
										
									}
									
									
								}
								else
								{
								//	cout<<finddbname1<<endl;
									//cout<<finddbname2<<endl;
									//cout<<"tca_array[j]�� �Ұ�����:"<<tca_array[j]<<endl;
									//���պҰ� DB�� ���³༮ ���� 
								}
								
								
								
							}
							////////////////////////DB2��¥����/////////////////////////////////////////////////////////////////////////
							
						}
						else/////////////////db���� 
						{
							//@@@@@@@@@@@@@@@@@@@@@@@@@@�ߺ�ť �־ �����Ұ� 
							//!@#
							adjust_nodb++;
							if(checkdup.insert(tca_array[j])==1)
							{
								adjust_nodb_nodup++;
								cout<<"[�ߺ��ƴ�]db��_���:"<<tca_array[j]<<endl;
									jsonout<<"{"<<endl;
										jsonout<<"\"name\": {"<<endl;
										jsonout<<"\"value\": \""<<tca_array[j]<<"\""<<endl;
										jsonout<<"}"<<endl;	        
										jsonout<<"},"<<endl;
							}
							else
							{
							//	cout<<"[�ߺ��Ӥ�]db��_���:"<<tca_array[j]<<endl;
							}
							/*
						
										*/
						}
						
						 
						
						
						
					}
					
					
				}
				if(p2<0) break;
				p=p2;
			}
	}
	//case��ü �y������
	/*
	 int adjust_nodb=0;
	int adjust_nodb_nodup=0;
	int adjust_1db=0;
	int adjust_1db_nodup=0;
	int adjust_2db=0;
	int adjust_2db_nodup=0;
	*/
	jsonout<<"DB������ �����(��ü):"<<adjust_nodb<<endl;
	jsonout<<"DB������ �����(�ߺ�����):"<<adjust_nodb_nodup<<endl;
	jsonout<<"DB��� 1�� ����� (��ü):"<<adjust_1db<<endl;
	jsonout<<"DB��� 1�� �����(�ߺ�����):"<<adjust_1db_nodup<<endl;
	jsonout<<"DB��� 2�� ����� (��ü):"<<adjust_2db<<endl;
	jsonout<<"DB��� 2�� �����(�ߺ�����):"<<adjust_2db_nodup<<endl;
	jsonout<<"�ߺ����� �� ����:"<<adjust_2db_nodup+adjust_1db_nodup+adjust_nodb_nodup<<endl;
	jsonout.close();
	case1.close();

}
