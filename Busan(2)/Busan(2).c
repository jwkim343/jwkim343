// 2-4까지 전부 다 하기는 했는데 빵꾸난 부분들이 많습니다.. 중간에 파일이 한번 날아가서 급하게 만드느라 죄송합니다.
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Len_Min 15
#define Len_Max 50
#define PROB_Min 10
#define PROB_Max 90
#define Stm_Min 0 // 마동석 체력
#define Stm_Max 5
#define AGGRO_MIN 0 // 시민, 마동석 어그로
#define AGGRO_MAX 5

// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0
// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2
// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int length, prob, madongsukStamina;

void intro() { // 인트로 함수
    printf("################\n");
    printf("# Escape Train #\n");
    printf("################\n");
    printf("\n");
}

void trainInfo() {
    // length == 기차길이, prob == probability
    printf("범위 내 숫자를 입력 해주세요.\n");
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
    // 기차 정보 올바름 확인 완료

    printf("입력한 기차 길이 : %d\n", length);
    printf("입력한 확률 : %d\n", prob);
    printf("입력한 확률값에 따라 시민이 왼쪽으로 1칸 이동하는 확률은 %d%%\n", 100 - prob);
    printf("좀비가 왼쪽으로 1칸 이동하는 확률은 %d%%입니다\n", prob);
    // 입력한 기차 정보 출력 완료
}

void firstTrainDraw(int C, int Z, int M) {
    // 기차 윗부분 출력 시작
    for (int i = 0; i < length; i++) {
        printf("#");
    }
    printf("\n");

    // 기차 중간 부분
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

    // 기차 아랫부분
    for (int i = 0; i < length; i++) {
        printf("#");
    }
    printf("\n");
    printf("입력한 값에 따른 첫 기차의 상태입니다.\n");
    printf("게임을 시작하겠습니다.\n");
    Sleep(1000);
    // 기차 초기 상태 완성
}

void check(int C, int Z) {
    if (C == 1) {
        printf("\n");
        printf("축하합니다!\n시민이 1번째 칸으로 탈출에 성공했습니다! 게임을 종료합니다.\n");
        printf("###############\n");
        printf("#   Success   #\n");
        printf("###############\n");
        Sleep(1000);
        exit(0);
    }
    else if (C == Z - 1) {
        printf("\n");
        printf("시민이 좀비에게 붙잡혔습니다..\n탈출에 실패하였습니다. 게임을 종료합니다\n");
        printf("###############\n");
        printf("#     Fail    #\n");
        printf("###############\n");
        Sleep(1000);
        exit(0);
    }
}
int main(void) {
    srand((unsigned int)time(NULL));
    // 인트로 시작
    intro();
    // 인트로 끝

    trainInfo();
    int madongsukStamin_before = madongsukStamina;
    int C = length - 6;
    int Z = length - 3;
    int M = length - 2;
    firstTrainDraw(C, Z, M);

    int location_C, location_Z, location_M; // 시민, 좀비, 마동석 위치 저장 변수
    location_C = length - 6;
    location_Z = length - 3;
    location_M = length - 2;

    int judge_C, judge_Z; // 시민, 좀비 움직임 판단
    int C_aggro = 1;
    int C_aggro_before = 1;
    int dongsukAction = 0;
    int M_aggro = 1;
    int M_aggro_before = 1;
    int pullSuccess = 0; // 붙잡기 판단
    while (1) {
        int random_C = rand() % 100 + 1; // 시민에 대한 난수

        if (random_C >= prob) {
            C--;
            judge_C = 1; // 1이면 move
        }
        else {
            judge_C = 0; // 0이면 stay
        }

        int random_Z = rand() % 100 + 1; // 좀비에 대한 난수
        if (random_Z >= prob) {
            judge_Z = 0;
        }
        else {
            Z--;
            judge_Z = 1;
        }

        int random_M = rand() % 100 + 1; // 마동석에 대한 난수, 붙들기 때 사용 (100-p)%로 붙들기 성공

        printf("\n\n");
        for (int i = 0; i < length; i++) { // 기차 상태 출력
            printf("#");
        }

        printf("\n");

        // 기차 중간 부분
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

        // 기차 아랫부분
        for (int i = 0; i < length; i++) {
            printf("#");
        } // 기차 출력 완료

        // 시민, 좀비 상태 출력 시작
        printf("\n");
        if (judge_C == 0) {
            if (C_aggro <= AGGRO_MIN) {
                C_aggro = AGGRO_MIN;
                C_aggro_before = AGGRO_MIN;
            }
            else {
                C_aggro--;
            }
            printf("시민 : stay %d (aggro : %d -> %d)\n", location_C, C_aggro_before, C_aggro); // 어그로 감소 해야 함
            if (C_aggro <= AGGRO_MIN) {
                C_aggro = AGGRO_MIN;
                C_aggro_before = AGGRO_MIN;
            }
            else {
                C_aggro_before--;
            }
        }
        else {
            if (C_aggro >= AGGRO_MAX) { // MAX값 초과하지 않게 하는 조건문
                C_aggro = AGGRO_MAX;
                C_aggro_before = AGGRO_MAX;
            }
            else { // MAX값 이상 아닐 시 정상적으로 어그로 값 오르게 하기
                C_aggro++;
            }
            printf("시민 : %d -> %d (aggro : %d -> %d)\n", location_C, C, C_aggro_before, C_aggro); // 어그로 증가해야 함
            location_C--;
            if (C_aggro >= AGGRO_MAX) {
                C_aggro = AGGRO_MAX;
                C_aggro_before = AGGRO_MAX;
            }
            else {
                C_aggro_before++;
            }
        }
        // 시민 상태 출력 완료
        if (!pullSuccess)
        {
            if (judge_Z == 0) {
                printf("좀비 : stay %d\n", location_Z);
            }
            else {
                printf("좀비 : %d -> %d\n", location_Z, Z);
                location_Z--;
            }
        }
        // 좀비 상태 출력 완료
        // 
        // 마동석의 행동 입력 받기
        if (M == Z + 1) { // M이 Z의 바로 오른쪽에 있을 때
            printf("마동석이 좀비 옆에 있습니다. (휴식:0, 도발:1, 붙잡기:2) >> ");
            scanf_s("%d", &dongsukAction);
            if (dongsukAction == 0)
            {
                if (C_aggro >= AGGRO_MAX) { // MAX값 초과하지 않게 하는 조건문
                    C_aggro = AGGRO_MAX;
                    C_aggro_before = AGGRO_MAX;
                }
                else { // MAX값 이상 아닐 시 정상적으로 어그로 값 오르게 하기
                    C_aggro++;
                }
                printf("마동석 : %d -> %d (aggro : %d -> %d)\n", location_M, M, M_aggro_before, M_aggro); // 어그로 증가해야 함
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
                printf("마동석이 도발하여 어그로 수치가 5되었습니다\n");
            }
            else
            {
                random_M = rand() % 100;
                if (random_M >= prob) {
                    pullSuccess = 1;
                    printf("붙잡기에 성공하였습니다. 다음턴에 좀비가 움직이지 못합니다.\n");
                }
                else {
                    printf("붙잡기 실패!\n");
                }
            }
        }
        else { // M이 Z의 바로 오른쪽에 없을 때
            printf("마동석이 좀비와 인접하지 않습니다. (대기:0, 이동:1) >> ");
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

