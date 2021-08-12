#include <iostream>
#include <stdlib.h>
#define MAX_N 50000
using namespace std;

int n;
int arr[2*MAX_N+1];
int sc_1, sc_2;
int main()
{
	cin >> n;
	int i;

	int num_1_1=0, num_1_0=0;
	for (i=1; i<=n; i++){
		cin >> arr[i];
		if (arr[i] == 1) num_1_1++;
		else sc_1+=num_1_1;
	}
	num_1_0 = n-num_1_1;

	int num_2_1=0, num_2_0;
	for (i=n+1;i<=2*n;i++){
		cin >> arr[i];
		if (arr[i]==1) num_2_1++;
		else sc_2+=num_2_1;
	}
	num_2_0 = n-num_2_1;
	int result=abs(sc_1-sc_2);

	if (sc_1 > sc_2){
		int go_1=n, go_2=n+1, go_re=0;
		while(sc_1 > sc_2){
			if (result > go_re+abs(sc_2 - sc_1)){
				result = go_re+abs(sc_2 - sc_1);
			}
			while(arr[go_1]==0){
				go_1--;
				if (go_1 == 0) goto print_result;
			}
			while(arr[go_2]==1){
				go_2++;
				if (go_2 == 2*n+1) goto print_result;
			}
			go_re += go_2-go_1;
			sc_1 -= n-go_1;
			sc_2 += --num_2_0;
			swap(arr[go_1--], arr[go_2++]);
		}
	}
	else{
		int go_1=n, go_2=n+1, go_re=0,sugosu_0=0, sugosu_1=0;
		while (sc_2 > sc_1){
			if (result > go_re + abs(sc_2 - sc_1)){
				result = go_re + abs(sc_2 - sc_1);
			}
			while(arr[go_1] == 1){
				go_1--; sugosu_1++;
				if (go_1 == 0) goto print_result;
			}
			while(arr[go_2] == 0){
				go_2++, sugosu_0++;
				if (go_2 == 2*n+1) goto print_result;
			}
			go_re += go_2-go_1;
			sc_1 -= num_1_1 - sugosu_1;
			sc_2 -= num_2_0 - sugosu_0;
			swap(arr[go_1--], arr[go_2++]);

		}
	}
print_result:
	cout << result << endl;
	return 0;
}
