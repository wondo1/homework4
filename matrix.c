#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); // 배열 생성 함수 정의 
void print_matrix(int** matrix, int row, int col); // 배열 출력 함수 정의
int free_matrix(int** matrix, int row, int col); // 배열 메모리 해체 함수 정의 
int fill_data(int** matrix, int row, int col); // 배열 데이터 채우는 함수 정의
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // 배열 덧셈 함수 정의 
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // 배열 뺄셈 함수 정의
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // 배열 전치 함수 정의
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // 배열 곱셈 함수 정의 

int main()
{
    char command; // 문자형 변수 선언
    printf("[----- [장원도]  [2018038099] -----]\n");

	int row, col; // 정수형 변수 선언 
	srand(time(NULL)); // 매번 다른 랜덤값 생성 함수 

	printf("Input row and col : "); // 열, 행 입력 출력 
	scanf("%d %d", &row, &col); // 정수형 변수 입력 받음 
    int** matrix_a = create_matrix(row, col); // 2차원 배열 a 생성 
	int** matrix_b = create_matrix(row, col); // 2차원 배열 b 생성
    int** matrix_a_t = create_matrix(col, row); // 2차원 배열 a_t 생성

	printf("Matrix Created.\n"); // 배열 생성 출력 

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} // matrix_a 또는 b가 null 이면 -1값 반환

	do{ // 반복문
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 문자형 변수 입력 받음 

		switch(command) { // 조건문 
		case 'z': case 'Z': // z 또는 Z 누르면
		    printf("Matrix Initialized\n"); 
			fill_data(matrix_a, row, col); // matrix_a 데이터 채움 
			fill_data(matrix_b, row, col); // matrix_b 데이터 채움 
			break; // 멈춤
        case 'p': case 'P': // P 또는 P누르면
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col); // print_matrix 함수 실행 matrix_a 값 출력 
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); // print_matrix 함수 실행 matrix_b 값 출력
			break; // 멈춤
        case 'a': case 'A': // a, A 누르면
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); // matrix_a,b더함
			break; // 멈춤
        case 's': case 'S': // s, S 누르면
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); // matrix_a,b 빼기 함수 
			break; // 멈춤
        case 't': case 'T': // t,T 누르면
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 행렬 전치를 위한 함수 
            print_matrix(matrix_a_t, col, row); // 전치된 행렬 출력 함수
			break; // 멈춤
        case 'm': case 'M': // m 또는 M 누르면 
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); // 행렬 전치 위한 함수 
            multiply_matrix(matrix_a, matrix_a_t, row, col); // 행렬 곱셈 함수 
			break; // 멈춤
        case 'q': case 'Q': // q 또는 Q 누르면
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); // matrix_a_t 동적메모리 해제
            free_matrix(matrix_a, row, col); // matrix_a 동적메모리 해제
            free_matrix(matrix_b, row, col); // matrix_b 동적메모리 해제 
			break; // 멈춤
		default: 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break; // 멈춤
		}

	}while(command != 'q' && command != 'Q'); // q 나 Q가 입력되기 전까지 반복

	return 1; // 1값 반환 
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) // matrix 생성 함수 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 행 또는 열이 0 이거나 0보다 작을 경우 
		printf("Check the size of row and col!\n");  // 열과 행 사이즈 체크 출력 
		return NULL; // NULL값 반환
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); // 2차원 배열, 동적 메모리 할당, int 타입 주소 포함하는 메모리 row만큼 힙 영역에서 할당 받음
	for (int r = 0; r < row; r++) { // 각각 row에 대한 요소 links를 위해 0부터 row 까지 반복
		matrix[r] = (int*)malloc(sizeof(int) * col); // 각각 matrix[r]번째 요소에 대한 col를 할당 받기 위한 메모리 동적할당  
	}

	/* Check post conditions */
	if (matrix == NULL) { // matrix가 NULL일 경우 
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 출력 
		return NULL; // NULL값 반환
	}

	return matrix; // matrix 반환
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) // matrix 출력 함수 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 행 또는 열이 0 이거나 0보다 작을 경우
		printf("Check the size of row and col!\n"); // 열과 행 사이즈 체크 출력
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { // matrix 출력을 위해 0 부터 row를 입력받은 만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix 출력을 위해 0 부터 col를 입력받은 만큼 반복
			printf("%3d ", matrix[matrix_row][matrix_col]); // matrix 출력 
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) { // matrix가 NULL일 경우 
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 출력 
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) // matrix 메모리 해제 함수 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 행 또는 열이 0 이거나 0보다 작을 경우
		printf("Check the size of row and col!\n"); // 열과 행 사이즈 체크 출력
		return -1; // -1 반환 
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 0부터 row 반큼 반복 
		free(matrix[matrix_row]); // matrix[matrix_row] 메모리 해제
	}

	free(matrix); // matrix 메모리 해제
	return 1; // 1값 반환
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) // matrix에 랜덤값 채우기 위한 함수 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 행 또는 열이 0 이거나 0보다 작을 경우
		printf("Check the size of row and col!\n");  // 열과 행 사이즈 체크 출력
		return -1; // -1 반환 
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) // matrix 난수 입력을 받기 위해 0 부터 row를 입력받은 만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix 난수 입력을 받기 위해 0 부터 col를 입력받은 만큼 반복
			matrix[matrix_row][matrix_col] = rand() % 20; // matrix[matrix_row][matrix_col]에 0~19까지 랜덤값 생성
	/* Check post conditions */
    if (matrix == NULL) { // matrix가 NULL일 경우
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 출력
		return -1; // -1 반환
	}
	return 1; // 1값 반환
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) // matrix_a,b 더하는 함수 정의 
{
    int** matrix_sum = create_matrix(row, col);  // matrix_sum에 create_matrix값 넣음
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 행 또는 열이 0 이거나 0보다 작을 경우
		printf("Check the size of row and col!\n");  // 열과 행 사이즈 체크 출력
		return -1; // -1 반환 
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // matrix 더하기 위해 0 부터 row를 입력받은 만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix 더하기 위해 0 부터 col를 입력받은 만큼 반복
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col]; // matrix_sum에 matrix_a,b 더한 값 넣음 
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { // matrix_a 또는 b 또는 sum이 NULL일 경우
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 출력
		return -1; // -1 반환
	}

	print_matrix(matrix_sum, row, col); // matrix_sum값 row,col print_matrix에 전달
	free_matrix(matrix_sum, row, col); // matrix_sum값 row,col free_matrix에 전달
	return 1; // 1값 반환
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) // matrix_a,b 빼는 함수 정의 
{
    int** matrix_sub = create_matrix(row, col); // matrix_sub에 create_matrix값 넣음
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 행 또는 열이 0 이거나 0보다 작을 경우
		printf("Check the size of row and col!\n"); // 열과 행 사이즈 체크 출력
		return -1; // -1 반환 
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // matrix 빼기 위해 0 부터 row를 입력받은 만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix 빼기 위해 0 부터 col를 입력받은 만큼 반복
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col]; // matrix_sub에 matrix_a,b 뺀 값 넣음 
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { // matrix_a 또는 b 또는 sub이 NULL일 경우
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 출력
		return -1; // -1 반환 
	}
	print_matrix(matrix_sub, row, col); // matrix_sub값 row,col print_matrix에 전달
	free_matrix(matrix_sub, row, col); // matrix_sub값 row,col free_matrix에 전달

	return 1; // 1값 반환
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) // matrix전치 함수 정의
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 행 또는 열이 0 이거나 0보다 작을 경우
		printf("Check the size of row and col!\n"); // 열과 행 사이즈 체크 출력
		return -1; // -1 반환 
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // matrix 전치 하기 위해 0 부터 row를 입력받은 만큼 반복
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix 전치 하기 위해 0 부터 col를 입력받은 만큼 반복
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row]; // matrix_t[matrix_row][matrix_col]에 matrix[matrix_col][matrix_row] 값 넣음(전치를 위해 matrix행렬 row와 col이 col,row로 바뀜)
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) { // matrix 또는 matrix_t가 NULL일 경우
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 출력
		return -1; // -1 반환 
	}

	return 1; // 1값 반환
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // matrix_a,t 곱하는 함수 정의 
{
    int** matrix_axt = create_matrix(row, row);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // 만약 행 또는 열이 0 이거나 0보다 작을 경우
		printf("Check the size of row and col!\n");  // 열과 행 사이즈 체크 출력
		return -1; // -1 반환
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) { // 곱하기 위해 matrix_a_row 입력받은 row 만큼 반복
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) { // 곱셈을 위해 matrix_t_row 입력받은 row 만큼 반복
			int temp = 0; // 정수형 변수 생성 
			for (int matrix_col = 0; matrix_col < col; matrix_col++) // 곱셈을 위해  matrix_col 값 입력받은 col만큼 반복
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; // temp에 matrix_a, matrix_t 곱한 값 더함 
			matrix_axt[matrix_a_row][matrix_t_row] = temp; // temp 값 matrix_axt 에 넘김 
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) { // matrix_t 또는 matrix_axt가 NULL일 경우
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 출력
		return -1; // -1 반환
	}
	print_matrix(matrix_axt, row, row); // matrix_axt값 row,col print_matrix에 전달
	free_matrix(matrix_axt, row, col); // matrix_axt값 row,col free_matrix에 전달
	return 1; // 1값 반환
}

