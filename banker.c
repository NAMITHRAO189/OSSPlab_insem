
#include <stdio.h>

int n, m, a[10][10], mx[10][10], need[10][10];
int avail[10], finish[10], seq[10], count = 0;

void safe(int work[], int len)
{
    if (len == n) {
        count++;
        printf("Safe sequence %d: ", count);
        for (int i = 0; i < n; i++)
            printf("T%d ", seq[i]);
        printf("\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            int ok = 1;
            for (int j = 0; j < m; j++)
                if (need[i][j] > work[j]) ok = 0;

            if (ok) {
                int w[10];
                for (int j = 0; j < m; j++)
                    w[j] = work[j] + a[i][j];

                finish[i] = 1;
                seq[len] = i;
                safe(w, len + 1);
                finish[i] = 0;
            }
        }
    }
}

int main()
{
    printf("Enter tenants and resources: ");
    scanf("%d%d", &n, &m);

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);

    printf("Enter Maximum matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &mx[i][j]);
            need[i][j] = mx[i][j] - a[i][j];
        }

    printf("Enter Available resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    safe(avail, 0);

    if (count)
        printf("System is SAFE. Total sequences: %d\n", count);
    else
        printf("System is UNSAFE. No safe sequence exists.\n");

    return 0;
}
