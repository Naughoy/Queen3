//CSP��ͻ�㷨

#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define MAX 1000          //���ʺ���

int row[MAX];             //row[i]��ʾ��ǰ�ڷ�����µ�i�еĻʺ���
int col[MAX];
int N;

int pdiag[2 * MAX];//���Խ��ߣ����ϵ����£���ʾ�����Խ���ƽ�е�2N-1���Խ��ߣ�
//pdiag[i]��ʾ��ǰ���Ϊi�ĶԽ����ϵĻʺ���

int cdiag[2 * MAX];//���Խ���
//cdiag[i]��ʾ���Ϊi�ĶԽ����ϵĻʺ���

int R[MAX];              //R[row] = col(row,col)����row�е�col�С���1���ʺ�

void randomize(int a[], int begin, int end){
	for (int i = begin; i <= end - 2; i++){
		int x = rand() % (end - i) + i;      //�����������ȡֵ[i, end) 
		int t = a[i];                     //��i�еĻʺ����x�еĻʺ������л�������һ�����ٳ�ͻ
		a[i] = a[x];
		a[x] = t;
	}
}
int getP(int row, int col) {                //�������Ӧ�����ϵ����µĶԽ��߱��
	return row - col + N - 1;
}
int getC(int row, int col) {                //�������Ӧ�����ϵ����µĶԽ��߱��
	return row + col;
}

//��ʼ���ʺ�İڷţ�ͬʱ��ʼ��row,col,pdiag,cdiag����
void init(){
	for (int i = 0; i < N; i++){
		R[i] = i;
	}
	randomize(R, 0, N);                   //��ʼ��ʱû������ʺ�ͬ�л�ͬ�У����ڶԽ�����
	for (int i = 0; i < N; i++){
		row[i] = 1;                       //����ÿ��ǡ��һ���ʺ�
		col[i] = 0;
	}
	for (int i = 0; i < 2 * N - 1; i++){
		pdiag[i] = 0;                     //��ʱû���κ�һ���Խ����϶���2���ʺ�
		cdiag[i] = 0;
	}
	for (int i = 0; i < N; i++){
		col[R[i]]++;                       //ÿ����һ���ʺ�
		pdiag[getP(i, R[i])]++;            //����Խ����ϵĻʺ����
		cdiag[getC(i, R[i])]++;
	}
}
bool qualify(){
	for (int i = 0; i < N; i++){
		//R[i]�еĻʺ���������1       �Խ����ϵĻʺ����������1
		if (col[R[i]] != 1 || pdiag[getP(i, R[i])] != 1 || cdiag[getC(i, R[i])] != 1){
			return false;
		}
	}
	return true;
}


//������ǰ�еĻʺ�λ��
bool adjust_row(int row) {
	int cur_col = R[row];             //��ǰ�еĻʺ�����λ�õ���
	int optimal_col = cur_col;        //����кţ�����Ϊ��ǰ�У�Ȼ�����

	//������С��ͻ���Խ��߳�ͻ��Ϊ��ǰ�Խ��߻ʺ�����һ
	int min_conflict = col[optimal_col] + pdiag[getP(row, optimal_col)] - 1 + cdiag[getC(row, optimal_col)] - 1;
	for (int i = 0; i < N; i++){
		if (i == cur_col){
			continue;
		}
		int conflict = col[i] + pdiag[getP(row, i)] + cdiag[getC(row, i)];     //
		if (conflict < min_conflict) {
			min_conflict = conflict;
			optimal_col = i;
		}
	}
	if (optimal_col != cur_col) {
		col[cur_col]--;
		pdiag[getP(row, cur_col)]--;
		cdiag[getC(row, cur_col)]--;

		col[optimal_col]++;
		pdiag[getP(row, optimal_col)]++;
		cdiag[getC(row, optimal_col)]++;
		R[row] = optimal_col;

		if (col[optimal_col] == 1 && pdiag[getP(row, optimal_col)] == 1 && cdiag[getC(row, optimal_col)] == 1){
			return qualify();
		}
	}

	return false;//������еĻʺ�û���еĻ����϶���������ֹ����
}

//���n�ʺ�
void print(){
	cout << "������£�" << endl;
	for (int i = 0; i < N; i++){
		cout << R[i] << ",";
	}
	cout << endl;
	for (int j = 0; j < N; j++) {
		if (j <= 9)
			cout << "0" << j;
		else
			cout << j;
		for (int k = 0; k < N; k++) {
			if (R[j] == k)
				cout << "  Q";
			else
				cout << "  *";
		}
		cout << endl;
	}
}


int main(){
	clock_t start, finish;
	cout << "����n�ʺ����" << endl;
	cin >> N;
	start = clock();
	init();
	if (qualify()){
		print();
		cout << "�������ҵĸ磬��һ������ͳɹ�" << endl;
		return 0;
	}
	bool Ju = false;
	while (!Ju) {
		for (int i = 0; i < N; i++) {
			if (adjust_row(i)) {
				Ju = true;
				break;
			}
		}
	}
	finish = clock();
	cout << endl << endl;
	print();
	cout << endl << endl;
	cout << N << "�ʺ����ʱ��Ϊ�� " << finish - start << endl;
	return 0;
}

