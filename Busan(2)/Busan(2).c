// 2-4���� ���� �� �ϱ�� �ߴµ� ���ٳ� �κе��� �����ϴ�.. �߰��� ������ �ѹ� ���ư��� ���ϰ� ������� �˼��մϴ�.
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Len_Min 15
#define Len_Max 50
#define PROB_Min 10
#define PROB_Max 90
#define Stm_Min 0 // ������ ü��
#define Stm_Max 5
#define AGGRO_MIN 0 // �ù�, ������ ��׷�
#define AGGRO_MAX 5

// ������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0
// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2
// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int length, prob, madongsukStamina;

void intro() { // ��Ʈ�� �Լ�
    printf("################\n");
    printf("# Escape Train #\n");
    printf("################\n");
    printf("\n");
}

void trainInfo() {
    // length == ��������, prob == probability
    printf("���� �� ���ڸ� �Է� ���ּ���.\n");
    printf("train length (%d ~ %d)>>", Len_Min, Len_Max);
    scanf_s("%d", &length);
    while (length < Len_Min || length > Len_Max) {
        printf("train length (%d ~ %d)>>", Len_Min, Len_Max);
        scanf_s("%d", &length);
    }
    printf("percentile probability 'p' (%d ~ %d)>>", PROB_Min, PROB_Max);
    scanf_s("%d", &prob);
    while (prob < PROB_Min || prob > PROB_Max) {
        printf("percentile probability 'p' (%d ~ %d)>>", PROB_Min, PROB_Max);
        scanf_s("%d", &prob);
    }
    printf("Madongsuk Stamina (%d ~ %d)>>", Stm_Min, Stm_Max);
    scanf_s("%d", &madongsukStamina);
    while (madongsukStamina < Stm_Min || madongsukStamina > Stm_Max) {
        printf("Madongsuk Stamina (%d ~ %d)>>", Stm_Min, Stm_Max);
        scanf_s("%d", &madongsukStamina);
    }
    printf("\n");

    printf("\n");
    // ���� ���� �ùٸ� Ȯ�� �Ϸ�

    printf("�Է��� ���� ���� : %d\n", length);
    printf("�Է��� Ȯ�� : %d\n", prob);
    printf("�Է��� Ȯ������ ���� �ù��� �������� 1ĭ �̵��ϴ� Ȯ���� %d%%\n", 100 - prob);
    printf("���� �������� 1ĭ �̵��ϴ� Ȯ���� %d%%�Դϴ�\n", prob);
    // �Է��� ���� ���� ��� �Ϸ�
}

void firstTrainDraw(int C, int Z, int M) {
    // ���� ���κ� ��� ����
    for (int i = 0; i < length; i++) {
        printf("#");
    }
    printf("\n");

    // ���� �߰� �κ�
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            printf("#");
        }
        else if (i == M) {
            printf("M");
        }
        else if (i == Z) {
            printf("Z");
        }
        else if (i == C) {
            printf("C");
        }
        else if (i != length - 1) {
            printf(" ");
        }
        else {
            printf("#\n");
        }
    }

    // ���� �Ʒ��κ�
    for (int i = 0; i < length; i++) {
        printf("#");
    }
    printf("\n");
    printf("�Է��� ���� ���� ù ������ �����Դϴ�.\n");
    printf("������ �����ϰڽ��ϴ�.\n");
    Sleep(1000);
    // ���� �ʱ� ���� �ϼ�
}

void check(int C, int Z) {
    if (C == 1) {
        printf("\n");
        printf("�����մϴ�!\n�ù��� 1��° ĭ���� Ż�⿡ �����߽��ϴ�! ������ �����մϴ�.\n");
        printf("###############\n");
        printf("#   Success   #\n");
        printf("###############\n");
        Sleep(1000);
        exit(0);
    }
    else if (C == Z - 1) {
        printf("\n");
        printf("�ù��� ���񿡰� ���������ϴ�..\nŻ�⿡ �����Ͽ����ϴ�. ������ �����մϴ�\n");
        printf("###############\n");
        printf("#     Fail    #\n");
        printf("###############\n");
        Sleep(1000);
        exit(0);
    }
}
int main(void) {
    srand((unsigned int)time(NULL));
    // ��Ʈ�� ����
    intro();
    // ��Ʈ�� ��

    trainInfo();
    int madongsukStamin_before = madongsukStamina;
    int C = length - 6;
    int Z = length - 3;
    int M = length - 2;
    firstTrainDraw(C, Z, M);

    int location_C, location_Z, location_M; // �ù�, ����, ������ ��ġ ���� ����
    location_C = length - 6;
    location_Z = length - 3;
    location_M = length - 2;

    int judge_C, judge_Z; // �ù�, ���� ������ �Ǵ�
    int C_aggro = 1;
    int C_aggro_before = 1;
    int dongsukAction = 0;
    int M_aggro = 1;
    int M_aggro_before = 1;
    int pullSuccess = 0; // ����� �Ǵ�
    while (1) {
        int random_C = rand() % 100 + 1; // �ùο� ���� ����

        if (random_C >= prob) {
            C--;
            judge_C = 1; // 1�̸� move
        }
        else {
            judge_C = 0; // 0�̸� stay
        }

        int random_Z = rand() % 100 + 1; // ���� ���� ����
        if (random_Z >= prob) {
            judge_Z = 0;
        }
        else {
            Z--;
            judge_Z = 1;
        }

        int random_M = rand() % 100 + 1; // �������� ���� ����, �ٵ�� �� ��� (100-p)%�� �ٵ�� ����

        printf("\n\n");
        for (int i = 0; i < length; i++) { // ���� ���� ���
            printf("#");
        }

        printf("\n");

        // ���� �߰� �κ�
        for (int i = 0; i < length; i++) {
            if (i == 0) {
                printf("#");
            }
            else if (i == M) {
                printf("M");
            }
            else if (i == Z) {
                printf("Z");
            }
            else if (i == C) {
                printf("C");
            }
            else if (i != length - 1) {
                printf(" ");
            }
            else {
                printf("#\n");
            }
        }

        // ���� �Ʒ��κ�
        for (int i = 0; i < length; i++) {
            printf("#");
        } // ���� ��� �Ϸ�

        // �ù�, ���� ���� ��� ����
        printf("\n");
        if (judge_C == 0) {
            if (C_aggro <= AGGRO_MIN) {
                C_aggro = AGGRO_MIN;
                C_aggro_before = AGGRO_MIN;
            }
            else {
                C_aggro--;
            }
            printf("�ù� : stay %d (aggro : %d -> %d)\n", location_C, C_aggro_before, C_aggro); // ��׷� ���� �ؾ� ��
            if (C_aggro <= AGGRO_MIN) {
                C_aggro = AGGRO_MIN;
                C_aggro_before = AGGRO_MIN;
            }
            else {
                C_aggro_before--;
            }
        }
        else {
            if (C_aggro >= AGGRO_MAX) { // MAX�� �ʰ����� �ʰ� �ϴ� ���ǹ�
                C_aggro = AGGRO_MAX;
                C_aggro_before = AGGRO_MAX;
            }
            else { // MAX�� �̻� �ƴ� �� ���������� ��׷� �� ������ �ϱ�
                C_aggro++;
            }
            printf("�ù� : %d -> %d (aggro : %d -> %d)\n", location_C, C, C_aggro_before, C_aggro); // ��׷� �����ؾ� ��
            location_C--;
            if (C_aggro >= AGGRO_MAX) {
                C_aggro = AGGRO_MAX;
                C_aggro_before = AGGRO_MAX;
            }
            else {
                C_aggro_before++;
            }
        }
        // �ù� ���� ��� �Ϸ�
        if (!pullSuccess)
        {
            if (judge_Z == 0) {
                printf("���� : stay %d\n", location_Z);
            }
            else {
                printf("���� : %d -> %d\n", location_Z, Z);
                location_Z--;
            }
        }
        // ���� ���� ��� �Ϸ�
        // 
        // �������� �ൿ �Է� �ޱ�
        if (M == Z + 1) { // M�� Z�� �ٷ� �����ʿ� ���� ��
            printf("�������� ���� ���� �ֽ��ϴ�. (�޽�:0, ����:1, �����:2) >> ");
            scanf_s("%d", &dongsukAction);
            if (dongsukAction == 0)
            {
                if (C_aggro >= AGGRO_MAX) { // MAX�� �ʰ����� �ʰ� �ϴ� ���ǹ�
                    C_aggro = AGGRO_MAX;
                    C_aggro_before = AGGRO_MAX;
                }
                else { // MAX�� �̻� �ƴ� �� ���������� ��׷� �� ������ �ϱ�
                    C_aggro++;
                }
                printf("������ : %d -> %d (aggro : %d -> %d)\n", location_M, M, M_aggro_before, M_aggro); // ��׷� �����ؾ� ��
                location_C--;
                if (C_aggro >= AGGRO_MAX) {
                    C_aggro = AGGRO_MAX;
                    C_aggro_before = AGGRO_MAX;
                }
                else {
                    C_aggro_before++;
                }
                M_aggro++;
            }
            else if (dongsukAction == 1)
            {
                M_aggro = AGGRO_MAX;
                printf("�������� �����Ͽ� ��׷� ��ġ�� 5�Ǿ����ϴ�\n");
            }
            else
            {
                random_M = rand() % 100;
                if (random_M >= prob) {
                    pullSuccess = 1;
                    printf("����⿡ �����Ͽ����ϴ�. �����Ͽ� ���� �������� ���մϴ�.\n");
                }
                else {
                    printf("����� ����!\n");
                }
            }
        }
        else { // M�� Z�� �ٷ� �����ʿ� ���� ��
            printf("�������� ����� �������� �ʽ��ϴ�. (���:0, �̵�:1) >> ");
            scanf_s("%d", &dongsukAction);
            if (dongsukAction == 0)
            {
                M;
            }
            else
            {
                M--;
            }
        }
        check(C, Z);
        Sleep(1000);
    }
    return 0;
}

