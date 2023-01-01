#include <stdio.h>
#define prt(m, g)                                                 \
    printf("百分制成绩 %d 对应五分制 %s，GPA=%s\n", score, m, g); \
    break
#define prtd(m, g) printf("百分制成绩 %.6f 对应五分制 %s，GPA=%s\n", score_double, m, g)
int main() {
    /* for(int i=100;i>=60;i--){ */
    /*     printf("case %d:\n",i); */
    /* } */

    int score;
    printf("输入一个整数的百分制成绩：");
    scanf("%d", &score);
    if (score < 0 || score > 100)
        printf("非法输入");
    else {
        switch (score) {
            case 100:
            case 99:
            case 98:
            case 97:
            case 96:
            case 95: prt("A+", "4.3");
            case 94:
            case 93:
            case 92:
            case 91:
            case 90: prt("A", "4.0");
            case 89:
            case 88:
            case 87:
            case 86:
            case 85: prt("A-", "3.7");
            case 84:
            case 83:
            case 82: prt("B+", "3.3");
            case 81:
            case 80:
            case 79:
            case 78: prt("B", "3.0");
            case 77:
            case 76:
            case 75: prt("B-", "2.7");
            case 74:
            case 73:
            case 72: prt("C+", "2.3");
            case 71:
            case 70:
            case 69:
            case 68: prt("C", "2.0");
            case 67:
            case 66:
            case 65: prt("C-", "1.7");
            case 64: prt("D+", "1.5");
            case 63:
            case 62:
            case 61: prt("D", "1.3");
            case 60: prt("D", "1.0");
            default: prt("F", "0");
        };
    }

    double score_double;
    printf("输入一个实数的百分制成绩：");
    scanf("%lf", &score_double);
    if (score_double < 0 || score_double > 100)
        printf("非法输入");
    else {
        if (score_double >= 95)
            prtd("A+", "4.3");
        else if (score_double >= 90)
            prtd("A", "4.0");
        else if (score_double >= 85)
            prtd("A-", "3.7");
        else if (score_double >= 82)
            prtd("B+", "3.3");
        else if (score_double >= 78)
            prtd("B", "3.0");
        else if (score_double >= 75)
            prtd("B-", "2.7");
        else if (score_double >= 72)
            prtd("C+", "2.3");
        else if (score_double >= 68)
            prtd("C", "2.0");
        else if (score_double >= 65)
            prtd("C-", "1.7");
        else if (score_double >= 64)
            prtd("D+", "1.5");
        else if (score_double >= 61)
            prtd("D", "1.3");
        else if (score_double >= 60)
            prtd("D", "1.0");
        else
            prtd("F", "0");
    }

    return 0;
}
