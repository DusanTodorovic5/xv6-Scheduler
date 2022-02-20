#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define N  1000

uint64 seed = 0x5bd1e995;

int random() {
    uint64 a = 16807;
    uint64 m = 2147483647L;
    seed = (a * seed) % m;
    uint64 t = seed * 10;
    while (t < m) {
        t *= 10;
    }
    return t / m;
}

int do_work(int length) {
    int ret = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            ret += (j % 2) ? +1 : -1;
        }
    }
    return ret;
}

void p1(int id, int length) {
    for (int i = 0; i < length; i++) {
        sleep(1);

        do_work(length);
        printf("P%d iteration=%d\n", id, i);
    }
    printf("P%d FINISHED!\n", id);
}

void p2(int id, int length) {
    for (int i = 0; i < length; i++) {
        sleep(random());

        do_work(length / 10);
        printf("P%d iteration=%d\n", id, i);
    }
    printf("P%d FINISHED!\n", id);
}

int
main(int argc, char *argv[])
{
    int sched = 0;
    int proc_num = 8;
    int length = 500;



    for (int i = 1; i < argc; i++) {
        switch (i) {
            case 1:
                proc_num = atoi(argv[i]);
                break;
            case 2:
                length = atoi(argv[i]);
                break;
            case 3:
                sched = atoi(argv[i]);
                break;
            default:
                break;
        }
    }
    chsched(sched);
    int res = uptime();

    printf("proc_num=%d length=%d\n", proc_num, length);

    for (int i = 0; i < proc_num; i++) {
        int pid = fork();
        if(pid < 0)
            break;
        if(pid == 0) {
            if (i < proc_num / 3) {
                p1(i, length);
            } else {
                p2(i, length / 4);
            }
            exit(0);
        }
    }

    for (int i = 0; i < proc_num; i++) {
        wait(0);
    }

    printf("%d\n",uptime() - res);
    exit(0);
}

