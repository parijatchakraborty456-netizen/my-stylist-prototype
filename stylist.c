#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 50
#define MAX_LOOKS 500

enum { TOP = 0, BOTTOM = 1, DRESS = 2 };

typedef struct {
    char name[40];
    int category;   /* TOP, BOTTOM or DRESS */
    int formality;  /* 1 = casual, 2 = smart, 3 = party */
} Item;

typedef struct {
    char desc[120];
    int score;
} Look;

static const char *occasion_names[] = {"", "Casual outing", "Office / meeting", "Party"};

static const char *hairstyles[4][2] = {
    {"", ""},
    {"Loose natural waves", "Simple ponytail"},
    {"Sleek low bun", "Neat straight hair"},
    {"Soft curls", "High ponytail with face-framing strands"}
};

static const char *jewelry[4][2] = {
    {"", ""},
    {"Small studs and a thin chain", "Simple bracelet"},
    {"Pearl studs and a watch", "Delicate pendant"},
    {"Statement earrings", "Layered necklace and a clutch"}
};

int compare_looks(const void *a, const void *b) {
    return ((const Look *)b)->score - ((const Look *)a)->score;
}

int main(void) {
    Item wardrobe[MAX_ITEMS];
    int n = 0;

    /* Sample wardrobe. Replace with your own clothes. */
    strcpy(wardrobe[n].name, "Black long bodycon dress"); wardrobe[n].category = DRESS;  wardrobe[n++].formality = 3;
    strcpy(wardrobe[n].name, "Red short bodycon dress");  wardrobe[n].category = DRESS;  wardrobe[n++].formality = 3;
    strcpy(wardrobe[n].name, "White fitted top");         wardrobe[n].category = TOP;    wardrobe[n++].formality = 2;
    strcpy(wardrobe[n].name, "Printed casual top");       wardrobe[n].category = TOP;    wardrobe[n++].formality = 1;
    strcpy(wardrobe[n].name, "Blue jeans");               wardrobe[n].category = BOTTOM; wardrobe[n++].formality = 1;
    strcpy(wardrobe[n].name, "Long satin skirt");         wardrobe[n].category = BOTTOM; wardrobe[n++].formality = 3;
    strcpy(wardrobe[n].name, "Short black skirt");        wardrobe[n].category = BOTTOM; wardrobe[n++].formality = 3;
    strcpy(wardrobe[n].name, "Formal trousers");          wardrobe[n].category = BOTTOM; wardrobe[n++].formality = 2;

    int occasion = 0;
    printf("Where are you going?\n1) Casual outing\n2) Office / meeting\n3) Party\nChoice: ");
    if (scanf("%d", &occasion) != 1 || occasion < 1 || occasion > 3) {
        printf("Please enter 1, 2 or 3.\n");
        return 1;
    }

    Look looks[MAX_LOOKS];
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (wardrobe[i].category == DRESS) {
            int diff = abs(occasion - wardrobe[i].formality);
            looks[count].score = 10 - 2 * diff;
            snprintf(looks[count].desc, sizeof looks[count].desc, "%s", wardrobe[i].name);
            count++;
        } else if (wardrobe[i].category == TOP) {
            for (int j = 0; j < n; j++) {
                if (wardrobe[j].category != BOTTOM) continue;
                int sum = wardrobe[i].formality + wardrobe[j].formality;
                int diff = abs(2 * occasion - sum);
                int gap = abs(wardrobe[i].formality - wardrobe[j].formality);
                looks[count].score = 10 - 2 * diff - gap;
                snprintf(looks[count].desc, sizeof looks[count].desc, "%s + %s",
                         wardrobe[i].name, wardrobe[j].name);
                count++;
            }
        }
    }

    qsort(looks, count, sizeof(Look), compare_looks);

    printf("\nTop 3 looks for: %s\n", occasion_names[occasion]);
    for (int k = 0; k < 3 && k < count; k++) {
        printf("\nLook %d: %s\n", k + 1, looks[k].desc);
        printf("  Hairstyle: %s\n", hairstyles[occasion][k % 2]);
        printf("  Accessories: %s\n", jewelry[occasion][k % 2]);
    }
    return 0;
}