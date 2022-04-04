#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); // �迭 ���� �Լ� ���� 
void print_matrix(int** matrix, int row, int col); // �迭 ��� �Լ� ����
int free_matrix(int** matrix, int row, int col); // �迭 �޸� ��ü �Լ� ���� 
int fill_data(int** matrix, int row, int col); // �迭 ������ ä��� �Լ� ����
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // �迭 ���� �Լ� ���� 
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // �迭 ���� �Լ� ����
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // �迭 ��ġ �Լ� ����
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // �迭 ���� �Լ� ���� 

int main()
{
    char command; // ������ ���� ����
    printf("[----- [�����]  [2018038099] -----]\n");

	int row, col; // ������ ���� ���� 
	srand(time(NULL)); // �Ź� �ٸ� ������ ���� �Լ� 

	printf("Input row and col : "); // ��, �� �Է� ��� 
	scanf("%d %d", &row, &col); // ������ ���� �Է� ���� 
    int** matrix_a = create_matrix(row, col); // 2���� �迭 a ���� 
	int** matrix_b = create_matrix(row, col); // 2���� �迭 b ����
    int** matrix_a_t = create_matrix(col, row); // 2���� �迭 a_t ����

	printf("Matrix Created.\n"); // �迭 ���� ��� 

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} // matrix_a �Ǵ� b�� null �̸� -1�� ��ȯ

	do{ // �ݺ���
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // ������ ���� �Է� ���� 

		switch(command) { // ���ǹ� 
		case 'z': case 'Z': // z �Ǵ� Z ������
		    printf("Matrix Initialized\n"); 
			fill_data(matrix_a, row, col); // matrix_a ������ ä�� 
			fill_data(matrix_b, row, col); // matrix_b ������ ä�� 
			break; // ����
        case 'p': case 'P': // P �Ǵ� P������
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col); // print_matrix �Լ� ���� matrix_a �� ��� 
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); // print_matrix �Լ� ���� matrix_b �� ���
			break; // ����
        case 'a': case 'A': // a, A ������
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); // matrix_a,b����
			break; // ����
        case 's': case 'S': // s, S ������
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); // matrix_a,b ���� �Լ� 
			break; // ����
        case 't': case 'T': // t,T ������
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // ��� ��ġ�� ���� �Լ� 
            print_matrix(matrix_a_t, col, row); // ��ġ�� ��� ��� �Լ�
			break; // ����
        case 'm': case 'M': // m �Ǵ� M ������ 
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); // ��� ��ġ ���� �Լ� 
            multiply_matrix(matrix_a, matrix_a_t, row, col); // ��� ���� �Լ� 
			break; // ����
        case 'q': case 'Q': // q �Ǵ� Q ������
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); // matrix_a_t �����޸� ����
            free_matrix(matrix_a, row, col); // matrix_a �����޸� ����
            free_matrix(matrix_b, row, col); // matrix_b �����޸� ���� 
			break; // ����
		default: 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break; // ����
		}

	}while(command != 'q' && command != 'Q'); // q �� Q�� �ԷµǱ� ������ �ݺ�

	return 1; // 1�� ��ȯ 
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) // matrix ���� �Լ� 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // ���� �� �Ǵ� ���� 0 �̰ų� 0���� ���� ��� 
		printf("Check the size of row and col!\n");  // ���� �� ������ üũ ��� 
		return NULL; // NULL�� ��ȯ
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); // 2���� �迭, ���� �޸� �Ҵ�, int Ÿ�� �ּ� �����ϴ� �޸� row��ŭ �� �������� �Ҵ� ����
	for (int r = 0; r < row; r++) { // ���� row�� ���� ��� links�� ���� 0���� row ���� �ݺ�
		matrix[r] = (int*)malloc(sizeof(int) * col); // ���� matrix[r]��° ��ҿ� ���� col�� �Ҵ� �ޱ� ���� �޸� �����Ҵ�  
	}

	/* Check post conditions */
	if (matrix == NULL) { // matrix�� NULL�� ��� 
		printf("Memory Allocation Failed.\n"); // �޸� �Ҵ� ���� ��� 
		return NULL; // NULL�� ��ȯ
	}

	return matrix; // matrix ��ȯ
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) // matrix ��� �Լ� 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // ���� �� �Ǵ� ���� 0 �̰ų� 0���� ���� ���
		printf("Check the size of row and col!\n"); // ���� �� ������ üũ ���
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { // matrix ����� ���� 0 ���� row�� �Է¹��� ��ŭ �ݺ�
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix ����� ���� 0 ���� col�� �Է¹��� ��ŭ �ݺ�
			printf("%3d ", matrix[matrix_row][matrix_col]); // matrix ��� 
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) { // matrix�� NULL�� ��� 
		printf("Memory Allocation Failed.\n"); // �޸� �Ҵ� ���� ��� 
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) // matrix �޸� ���� �Լ� 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // ���� �� �Ǵ� ���� 0 �̰ų� 0���� ���� ���
		printf("Check the size of row and col!\n"); // ���� �� ������ üũ ���
		return -1; // -1 ��ȯ 
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // 0���� row ��ŭ �ݺ� 
		free(matrix[matrix_row]); // matrix[matrix_row] �޸� ����
	}

	free(matrix); // matrix �޸� ����
	return 1; // 1�� ��ȯ
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) // matrix�� ������ ä��� ���� �Լ� 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // ���� �� �Ǵ� ���� 0 �̰ų� 0���� ���� ���
		printf("Check the size of row and col!\n");  // ���� �� ������ üũ ���
		return -1; // -1 ��ȯ 
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) // matrix ���� �Է��� �ޱ� ���� 0 ���� row�� �Է¹��� ��ŭ �ݺ�
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix ���� �Է��� �ޱ� ���� 0 ���� col�� �Է¹��� ��ŭ �ݺ�
			matrix[matrix_row][matrix_col] = rand() % 20; // matrix[matrix_row][matrix_col]�� 0~19���� ������ ����
	/* Check post conditions */
    if (matrix == NULL) { // matrix�� NULL�� ���
		printf("Memory Allocation Failed.\n"); // �޸� �Ҵ� ���� ���
		return -1; // -1 ��ȯ
	}
	return 1; // 1�� ��ȯ
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) // matrix_a,b ���ϴ� �Լ� ���� 
{
    int** matrix_sum = create_matrix(row, col);  // matrix_sum�� create_matrix�� ����
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // ���� �� �Ǵ� ���� 0 �̰ų� 0���� ���� ���
		printf("Check the size of row and col!\n");  // ���� �� ������ üũ ���
		return -1; // -1 ��ȯ 
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // matrix ���ϱ� ���� 0 ���� row�� �Է¹��� ��ŭ �ݺ�
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix ���ϱ� ���� 0 ���� col�� �Է¹��� ��ŭ �ݺ�
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col]; // matrix_sum�� matrix_a,b ���� �� ���� 
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { // matrix_a �Ǵ� b �Ǵ� sum�� NULL�� ���
		printf("Memory Allocation Failed.\n"); // �޸� �Ҵ� ���� ���
		return -1; // -1 ��ȯ
	}

	print_matrix(matrix_sum, row, col); // matrix_sum�� row,col print_matrix�� ����
	free_matrix(matrix_sum, row, col); // matrix_sum�� row,col free_matrix�� ����
	return 1; // 1�� ��ȯ
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) // matrix_a,b ���� �Լ� ���� 
{
    int** matrix_sub = create_matrix(row, col); // matrix_sub�� create_matrix�� ����
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // ���� �� �Ǵ� ���� 0 �̰ų� 0���� ���� ���
		printf("Check the size of row and col!\n"); // ���� �� ������ üũ ���
		return -1; // -1 ��ȯ 
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // matrix ���� ���� 0 ���� row�� �Է¹��� ��ŭ �ݺ�
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix ���� ���� 0 ���� col�� �Է¹��� ��ŭ �ݺ�
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col]; // matrix_sub�� matrix_a,b �� �� ���� 
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { // matrix_a �Ǵ� b �Ǵ� sub�� NULL�� ���
		printf("Memory Allocation Failed.\n"); // �޸� �Ҵ� ���� ���
		return -1; // -1 ��ȯ 
	}
	print_matrix(matrix_sub, row, col); // matrix_sub�� row,col print_matrix�� ����
	free_matrix(matrix_sub, row, col); // matrix_sub�� row,col free_matrix�� ����

	return 1; // 1�� ��ȯ
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) // matrix��ġ �Լ� ����
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // ���� �� �Ǵ� ���� 0 �̰ų� 0���� ���� ���
		printf("Check the size of row and col!\n"); // ���� �� ������ üũ ���
		return -1; // -1 ��ȯ 
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { // matrix ��ġ �ϱ� ���� 0 ���� row�� �Է¹��� ��ŭ �ݺ�
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // matrix ��ġ �ϱ� ���� 0 ���� col�� �Է¹��� ��ŭ �ݺ�
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row]; // matrix_t[matrix_row][matrix_col]�� matrix[matrix_col][matrix_row] �� ����(��ġ�� ���� matrix��� row�� col�� col,row�� �ٲ�)
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) { // matrix �Ǵ� matrix_t�� NULL�� ���
		printf("Memory Allocation Failed.\n"); // �޸� �Ҵ� ���� ���
		return -1; // -1 ��ȯ 
	}

	return 1; // 1�� ��ȯ
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // matrix_a,t ���ϴ� �Լ� ���� 
{
    int** matrix_axt = create_matrix(row, row);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { // ���� �� �Ǵ� ���� 0 �̰ų� 0���� ���� ���
		printf("Check the size of row and col!\n");  // ���� �� ������ üũ ���
		return -1; // -1 ��ȯ
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) { // ���ϱ� ���� matrix_a_row �Է¹��� row ��ŭ �ݺ�
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) { // ������ ���� matrix_t_row �Է¹��� row ��ŭ �ݺ�
			int temp = 0; // ������ ���� ���� 
			for (int matrix_col = 0; matrix_col < col; matrix_col++) // ������ ����  matrix_col �� �Է¹��� col��ŭ �ݺ�
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; // temp�� matrix_a, matrix_t ���� �� ���� 
			matrix_axt[matrix_a_row][matrix_t_row] = temp; // temp �� matrix_axt �� �ѱ� 
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) { // matrix_t �Ǵ� matrix_axt�� NULL�� ���
		printf("Memory Allocation Failed.\n"); // �޸� �Ҵ� ���� ���
		return -1; // -1 ��ȯ
	}
	print_matrix(matrix_axt, row, row); // matrix_axt�� row,col print_matrix�� ����
	free_matrix(matrix_axt, row, col); // matrix_axt�� row,col free_matrix�� ����
	return 1; // 1�� ��ȯ
}

