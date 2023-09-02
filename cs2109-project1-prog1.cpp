#include<iostream>
#include<vector>
#include<unordered_map>
#include<climits>
using namespace std;
using vi=vector<int>;
using vvi=vector<vector<int>>;
#define fi first
#define se second

//max value function
int maxVal(vi v){
	int ans=INT_MIN;
	for(auto it:v){ans=max(it,ans);}
	return ans;
}
//min value function
int minVal(vi v){
	int ans=INT_MAX;
	for(auto it:v){ans=min(it,ans);}
	return ans;
}
//find factorial function
int fact(int n){
	int ans=1;
	for(int i=2;i<=n;++i){ans*=i;}
	return ans;
}
//hash function to map vector to int
struct vectorHasher{
	int operator()(const vi &v) const{
		int h=(int)v.size();
		for(auto &i:v){h^=i+0x9e3779b9+(h<<6) +(h>>2);}
		return h;
	}
};
bool isSame(int a,int b){
	return a==b?true:false;
}
//insert function
vi insertFunction(vi v,int a,int b){
	if(isSame(a,b)){v[a]+=1;}
	else if(a<b){v[a]-=1;v[b]+=2;}
	return v;}
//find the max function
int maxSize(unordered_map<vi,int,vectorHasher> dict,int L,vvi &LHS){
	int heapableSize=INT_MIN;
	for(auto it:dict){heapableSize=max(heapableSize,LHS[L][it.se]);}
	return heapableSize;
}
bool findShape(unordered_map<vi,int,vectorHasher> dict,vi SHAPE){
	return dict.find(SHAPE)==dict.end();
}
void updateDictionary(vector<pair<vi,int>> TEMP,unordered_map<vi,int,vectorHasher>& dict){
	//update the dictionary
	for(auto it:TEMP){dict[it.fi]=it.se;}
}
//final function
int longestHeapableSubsequence(vector<int> v,int alpha){
	//take an array of size n x factorial k as described in the paper
	vvi LHS((int)v.size()+1,vi(fact(alpha+1)+1,0));
	//a hashmap from vector int to int	
	unordered_map<vi,int,vectorHasher> dict;
	vi iniShape(alpha+1,0);iniShape[0]=1;
	dict[iniShape]=0;int freeCol=1; // indicate the free current column
	for(int i=1;i<=(int)v.size();++i){
		for(auto it:dict)LHS[i][it.se]=LHS[i-1][it.se];// for clearing the array
		vector<pair<vi,int>> TEMP; //temporary vector
		for(auto it:dict){
			//int b=0;
			for(int index=0;index<=v[i-1];++index){
				if(it.fi[index]>0){
					vi SHAPE=insertFunction(it.fi,index,v[i-1]);
					//if that vector is not found
					if(findShape(dict,SHAPE)){
						TEMP.push_back(make_pair(SHAPE,freeCol));
						LHS[i][freeCol]=LHS[i-1][it.se]+1;
						freeCol+=1;
					}else if(LHS[i][dict[SHAPE]]<LHS[i-1][it.se]+1){
						//if got
						LHS[i][dict[SHAPE]]=LHS[i-1][it.se]+1;
					}
				}
				//++b;
			}
		}
		//update the dictionary
		//pass temp vector and dict dictionary as reference
		updateDictionary(TEMP,dict);
		//++i;
	}
	//return the max size
	return maxSize(dict,(int)v.size(),LHS);
}	
int main()
{
	//take input
	int n;scanf("%d",&n);
	vi v(n);for(auto &it:v)cin>>it;
	//find max value
	int alpha=maxVal(v);
	//checking the edge cases
	if(minVal(v)<=0){
		printf("Min Value is less than zero\n");
		return 0;
	}else if(alpha>=11){
		printf("Alpha should be small\n");
		return 0;
	}else{
		printf("%d\n",longestHeapableSubsequence(v,alpha));
	}
}
