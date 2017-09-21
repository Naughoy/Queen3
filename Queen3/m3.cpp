//CSP冲突算法

#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;
#define MAX 1000          //最多皇后数

int row[MAX];             //row[i]表示当前摆放情况下第i行的皇后数
int col[MAX];
int N;

int pdiag[2 * MAX];//主对角线，左上到右下（表示和主对角线平行的2N-1条对角线）
//pdiag[i]表示当前编号为i的对角线上的皇后数

int cdiag[2 * MAX];//副对角线
//cdiag[i]表示编号为i的对角线上的皇后数

int R[MAX];              //R[row] = col(row,col)“第row行第col列”有1个皇后

void randomize(int a[], int begin, int end){
	for (int i = begin; i <= end - 2; i++){
		int x = rand() % (end - i) + i;      //产生的随机数取值[i, end) 
		int t = a[i];                     //第i行的皇后与第x行的皇后所在列互换，进一步减少冲突
		a[i] = a[x];
		a[x] = t;
	}
}
int getP(int row, int col) {                //返回其对应的左上到右下的对角线编号
	return row - col + N - 1;
}
int getC(int row, int col) {                //返回其对应的右上到左下的对角线编号
	return row + col;
}

//初始化皇后的摆放，同时初始化row,col,pdiag,cdiag数组
void init(){
	for (int i = 0; i < N; i++){
		R[i] = i;
	}
	randomize(R, 0, N);                   //初始化时没有任意皇后同列或同行，都在对角线上
	for (int i = 0; i < N; i++){
		row[i] = 1;                       //对于每行恰好一个皇后
		col[i] = 0;
	}
	for (int i = 0; i < 2 * N - 1; i++){
		pdiag[i] = 0;                     //此时没有任何一条对角线上多余2个皇后
		cdiag[i] = 0;
	}
	for (int i = 0; i < N; i++){
		col[R[i]]++;                       //每列有一个皇后
		pdiag[getP(i, R[i])]++;            //计算对角线上的皇后个数
		cdiag[getC(i, R[i])]++;
	}
}
bool qualify(){
	for (int i = 0; i < N; i++){
		//R[i]列的皇后数不等于1       对角线上的皇后个数不等于1
		if (col[R[i]] != 1 || pdiag[getP(i, R[i])] != 1 || cdiag[getC(i, R[i])] != 1){
			return false;
		}
	}
	return true;
}


//调整当前行的皇后位置
bool adjust_row(int row) {
	int cur_col = R[row];             //当前行的皇后所在位置的列
	int optimal_col = cur_col;        //最佳列号，设置为当前列，然后更新

	//定义最小冲突，对角线冲突数为当前对角线皇后数减一
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

	return false;//如果该行的皇后都没变列的话，肯定不满足终止条件
}

//输出n皇后
void print(){
	cout << "结果如下：" << endl;
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
	cout << "输入n皇后个数" << endl;
	cin >> N;
	start = clock();
	init();
	if (qualify()){
		print();
		cout << "厉害了我的哥，第一次随机就成功" << endl;
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
	cout << N << "皇后求解时间为： " << finish - start << endl;
	return 0;
}

