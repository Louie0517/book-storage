#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_RECORDS 100
#define MAX_INPUT_LENGTH 128
#define DAYS_IN_WEEK 7
#define MAX_HOURS 23
#define MAX_MINUTES 59


const char *weekDays[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
const char *months[] = { "January", "February", "March", "April", "May", "June",
                         "July", "August", "September", "October", "November", "December" };
int currentScreen = 0;
static int x = 1200;
static float imageYy = -600;
static float targetYy = 0;

typedef struct {
    char name[50];
    char id[20];
    int age;
    int day;
    int month;
    int year;
    int hour;
    int minute;
    char bookId[20];
    char author[50];
    bool returned;
    bool isAM;

} Record;

// Record array / count
Record records[MAX_RECORDS];
int recordCount = 0;
bool isAM = true;
int editingRecordIndex = -1;

void drawMainMenu();
void AddRecord(Font addrecFont, Texture2D addRec, Texture2D p12, int *selectedDay, int *selectedMonth, int *selectedYear, int *selectedHour, int *selectedMinute, int *currentScreen, bool *isAM, int *taasScreen);
void DisplayRecords(int *currentScreen, Texture2D displayRec, Texture2D p14, int *selectedDay, int *selectedMonth, int *selectedYear, int *selectedHour, int *selectedMinute, bool *isAM);
void SearchRecord();
void EditRecord();
void DeleteRecord();
void DatePicker(int queenA, int queenB, Texture2D calendar, Texture2D calendar2,int *selectedDay, int *selectedMonth, int *selectedYear, int *selectedHour, int *selectedMinute, bool *isAM, int *currentScreen);
int GetDaysInYear2025();
int CountLeapYears(int year);
int GetDaysInMonth(int month, int year);
int GetFirstDayOfWeek(int month, int year);
int ClampInt(int value, int min, int max);
void rounders(int roundX, int roundY, int orig_w, int orig_h, int orig_radius, int new_w, int new_h);
bool kinakabahanAko(Color color, int roundX, int roundY, int orig_radius, int new_w, int new_h);

extern Record records[];
extern int recordCount;

void rounders(int roundX, int roundY, int orig_w, int orig_h, int orig_radius, int new_w, int new_h){

    float scale_w = (float)new_w / orig_w;
    float scale_h = (float)new_h / orig_h;

    int new_radius = orig_radius * (scale_w < scale_h ? scale_w : scale_h);
    Color transparent = (Color){255, 255, 255, 128};
    DrawRectangleRounded((Rectangle){roundX, roundY, new_w, new_h}, (float)new_radius / new_w, 16, transparent);

}

bool kinakabahanAko( Color color, int roundX, int roundY, int orig_radius, int new_w, int new_h) {
    float scale = (float)new_w / new_h;
    int new_radius = orig_radius * (scale < 1.0f ? scale : 1.0f);

    DrawRectangleRounded((Rectangle){roundX, roundY, new_w, new_h}, (float)new_radius / new_w, 16, color);
}

void updateAddRecordTrans(float *imageYy, float speed) {
    if (*imageYy < targetYy) {
        *imageYy += speed;
        if (*imageYy > targetYy) *imageYy = targetYy;
    }
}

void AddRecord(Font addrecFont, Texture2D addRec, Texture2D p12, int *selectedDay, int *selectedMonth, int *selectedYear, int *selectedHour, int *selectedMinute, int *currentScreen, bool *isAM, int *taasScreen) {
    static char name[50] = "";
    static char id[20] = "";
    static char ageInput[5] = "";
    static char bookId[50] = "";
    static char author[50] = "";
    static int nameIndex = 0, idIndex = 0, ageIndex = 0, bookIDIndex = 0, authorIndex = 0;
    static bool nameActive = true, idActive = false, ageActive = false, bookIDActive = false, authorActive = false, dateActive = false;
    static bool showWarning = false;
    static char warnigMessage[100] = "";
    bool saveC = false;
    bool nahiramNaBaYungLibro = false;
    bool idNakahiramNa = false;
    bool fieldsNeedSagutan = false;
    int x = 1200;
    float speed = 15.0f;
    updateAddRecordTrans(&imageYy, speed);


    DrawTexture(addRec, x - 419, imageYy, WHITE);
    DrawTexture(p12, x - 1200, 0, WHITE);

    rounders(185, 110, 485, 450, 10, 500, 420);

    DrawText("Add Record", 310, 120, 50, GOLD);
    DrawText("Name:", 215, 190, 20, BLACK);
    DrawRectangle(300, 180, 300, 30, nameActive ? LIGHTGRAY : WHITE);
    DrawRectangleLines(300, 180, 300, 30, BLACK); // Border
    DrawText(name, 310, 185, 20, BLACK);

    DrawText("ID:", 215, 235, 20, BLACK);
    DrawRectangle(300, 225, 300, 30, idActive ? LIGHTGRAY : WHITE);
    DrawRectangleLines(300, 225, 300, 30, BLACK); // Border
    DrawText(id, 310, 230, 20, BLACK);

    DrawText("Age:", 215, 280, 20, BLACK);
    DrawRectangle(300, 270, 300, 30, ageActive ? LIGHTGRAY : WHITE);
    DrawRectangleLines(300, 270, 300, 30, BLACK); // Border
    DrawText(ageInput, 310, 275, 20, BLACK);

    DrawText("Book ID:", 215, 325, 20, BLACK);
    DrawRectangle(300, 315, 300, 30, bookIDActive ? LIGHTGRAY : WHITE);
    DrawRectangleLines(300, 315, 300, 30, BLACK); // Border
    DrawText(bookId, 310, 320, 20, BLACK);

    DrawText("Author:", 215, 370, 20, BLACK);
    DrawRectangle(300, 360, 300, 30, authorActive ? LIGHTGRAY : WHITE);
    DrawRectangleLines(300, 360, 300, 30, BLACK); // Border
    DrawText(author, 310, 365, 20, BLACK);

    DrawText("Date:", 215, 415, 20, BLACK);
    DrawRectangle(300, 405, 300, 25, dateActive ? LIGHTGRAY : WHITE);
    DrawRectangleLines(300, 405, 300, 25, BLACK); // Border
    DrawText(TextFormat("%s %d, %d %02d:%02d %s", months[*selectedMonth], *selectedDay, *selectedYear, *selectedHour, *selectedMinute, *isAM ? "AM" : "PM"), 310, 410, 20, BLACK);


    Rectangle pasukona = {300, 460, 100, 50};
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, pasukona)) {
        saveC = true;
    } else {
        saveC = false;
    }
    Color normalState = (Color){139, 0, 0, 255};
    Color hoverState = (Color){139, 0, 0, 192};
    kinakabahanAko(saveC ? hoverState : normalState, 300, 460, 10, 100, 50);
    DrawText("Save", 315, 470, 20, GOLD);

    bool kahitTreslang_okayna = false;

    Rectangle gustoKonaMagShift = {490, 460, 100, 50};
    Vector2 kahitTreslangPopls = GetMousePosition();
    if (CheckCollisionPointRec(kahitTreslangPopls, gustoKonaMagShift)) {
        kahitTreslang_okayna = true;
    } else {
        kahitTreslang_okayna = false;
    }
    DrawRectangle(490, 460, 100, 50, kahitTreslang_okayna ? hoverState : normalState);
    DrawText("Back", 505, 470, 20, GOLD);


    if (IsKeyPressed(KEY_TAB)) {
        if (nameActive) {
            nameActive = false;
            idActive = true;
        } else if (idActive) {
            idActive = false;
            ageActive = true;
        } else if (ageActive) {
            ageActive = false;
            bookIDActive = true;
        } else if (bookIDActive) {
            bookIDActive = false;
            authorActive = true;
        } else if (authorActive) {
            authorActive = false;
            dateActive = true;
        } else if (dateActive) {
            dateActive = false;
            nameActive = true;
        }
    }


    if (nameActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (nameIndex < sizeof(name) - 1)) {
                name[nameIndex++] = (char)key;
                name[nameIndex] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && nameIndex > 0) {
            name[--nameIndex] = '\0';
        }
    } else if (idActive) {
        int key = GetCharPressed();
        while (key > 0) {
                // if it still in the range every char that user input
            if ((key >= 32) && (key <= 125) && (idIndex < sizeof(id) - 1)) {
                // increament the indx for the next chrtr
                id[idIndex++] = (char)key;
                // to end properly the str
                id[idIndex] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && idIndex > 0) {
            id[--idIndex] = '\0';
        }
    } else if (ageActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (ageIndex < sizeof(ageInput) - 1)) {
                ageInput[ageIndex++] = (char)key;
                ageInput[ageIndex] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && ageIndex > 0) {
            ageInput[--ageIndex] = '\0';
        }
    } else if (bookIDActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (bookIDIndex < sizeof(bookId) - 1)) {
                bookId[bookIDIndex++] = (char)key;
                bookId[bookIDIndex] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && bookIDIndex > 0) {
            bookId[--bookIDIndex] = '\0';
        }
    } else if (authorActive) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (authorIndex < sizeof(author) - 1)) {
                author[authorIndex++] = (char)key;
                author[authorIndex] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && authorIndex > 0) {
            author[--authorIndex] = '\0';
        }
    } else if (dateActive) {
        if (IsKeyPressed(KEY_SPACE)) {
            *currentScreen = 9;
        }
    }

   if (IsKeyPressed(KEY_ENTER)) {
    if (strlen(name) == 0 || strlen(id) == 0 || strlen(ageInput) == 0 || strlen(bookId) == 0 || strlen(author) == 0) {
        fieldsNeedSagutan = true;
        showWarning = true;
        strcpy(warnigMessage, "All fields are required!");
    } else {
        fieldsNeedSagutan = false;
        nahiramNaBaYungLibro = false;
        idNakahiramNa = false;
        for (int i = 0; i < recordCount; i++) {
            if (strcmp(records[i].bookId, bookId) == 0) {
                nahiramNaBaYungLibro = true;
                showWarning = true;
                strcpy(warnigMessage, "Book is Borrowed!");

            }
            if(strcmp(records[i].id, id) == 0){
                idNakahiramNa = true;
                showWarning = true;
                strcpy(warnigMessage, "Student is already borrowing a book");
            }
        }
        if (!nahiramNaBaYungLibro && !idNakahiramNa) {
            if (recordCount < MAX_RECORDS) {
                strcpy(records[recordCount].name, name);
                strcpy(records[recordCount].id, id);
                strcpy(records[recordCount].bookId, bookId);
                strcpy(records[recordCount].author, author);
                records[recordCount].age = atoi(ageInput);
                records[recordCount].day = *selectedDay;
                records[recordCount].month = *selectedMonth;
                records[recordCount].year = *selectedYear;
                records[recordCount].hour = *selectedHour;
                records[recordCount].minute = *selectedMinute;
                records[recordCount].isAM = *isAM;
                recordCount++;
                *currentScreen = 4;
                memset(name, 0, sizeof(name));
                memset(id, 0, sizeof(id));
                memset(ageInput, 0, sizeof(ageInput));
                memset(bookId, 0, sizeof(bookId));
                memset(author, 0, sizeof(author));
                nameIndex = idIndex = ageIndex = bookIDIndex = authorIndex = 0;
                nameActive = true;
                idActive = ageActive = bookIDActive = authorActive = dateActive = false;

                *selectedDay = 1;
                *selectedMonth = 0;
                *selectedYear = 2025;
                *selectedHour = 12;
                *selectedMinute = 0;
                *isAM = true;
        }
    }
}
       }
    if(fieldsNeedSagutan){
        DrawText("All fields are required!", 310, 440, 20, RED);
    } else if(nahiramNaBaYungLibro){
        DrawText("Book is Borrowed", 310, 440, 20, RED);
    } else if(idNakahiramNa){
        DrawText("Student is already borrowing a book", 310, 440, 20, RED);
    }

   if(CheckCollisionPointRec(kahitTreslangPopls, gustoKonaMagShift) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    *currentScreen = 3;
   memset(name, 0, sizeof(name));
   memset(id, 0, sizeof(id));
   memset(ageInput, 0, sizeof(ageInput));
   memset(bookId, 0, sizeof(bookId));
   memset(author, 0, sizeof(author));
   nameIndex = idIndex = ageIndex = bookIDIndex = authorIndex = 0; nameActive = true; idActive = ageActive = bookIDActive = authorActive = dateActive = false;

   *selectedDay = 1;
    *selectedMonth = 0;
    *selectedYear = 2025;
    *selectedHour = 12;
    *selectedMinute = 0;
    *isAM = true;

    DrawText("Date:", 215, 415, 20, BLACK);
    DrawRectangle(300, 405, 300, 25, dateActive ? LIGHTGRAY : WHITE);
    DrawText(TextFormat("%s %d, %d %02d:%02d %s", months[*selectedMonth], *selectedDay, *selectedYear, *selectedHour, *selectedMinute, *isAM ? "AM" : "PM"), 310, 410, 20, BLACK);

   }
}

void EditRecord(Texture2D editRec, Texture2D p13, Font editFont, bool *backClick, int *currentScreen) {
    int x = 1200;
    static int selectedRecordIndex = -1;
    static char name[50] = "";
    static char id[20] = "";
    static char ageInput[5] = "";
    static char bookId[50] = "";
    static char author[50] = "";
    static int nameIndex = 0, idIndex = 0, ageIndex = 0, bookIdIndex = 0, authorIndex = 0;
    static bool nameActive = true, ageActive = false, bookIdActive = false, authorAcctive = false, activeBasiDate = false;
    static bool nameHolder = true, idHolder = true, ageHolder = true, bookIdHolder = true, authorHolder = true, dateHolder = true;
    float speed = 15.0f;

    bool idhov = false;
    updateAddRecordTrans(&imageYy, speed);
    DrawTexture(editRec, x - 425, imageYy, WHITE);
    DrawTexture(p13, x - 1200, 0, WHITE);
    rounders(150, 65, 485, 495, 10, 520, 440);
    Rectangle kinemelars = {235, 275, 325, 30};
    Vector2 idkels = GetMousePosition();
    if(CheckCollisionPointRec(idkels, kinemelars)){
        idhov = true;
    } else{
        idhov = false;
    }

    if (selectedRecordIndex == -1) {
        Color unitedState = (Color){139, 0, 0, 255};
        DrawRectangle(150, 75, 520, 100, GOLD);
        DrawRectangle(150, 65, 520, 100, unitedState);
        DrawTextEx(editFont, "Edit Record", (Vector2){205, 65}, 100, 3.0f, GOLD);
        DrawRectangleLines(235, 275, 325, 50, BLACK);
        DrawRectangle(235, 275, 325, 50, idhov ? LIGHTGRAY : WHITE);
        if(idIndex == 0){
                DrawText("Enter ID:", 245, 285, 20, BLACK);
                } else {
                    // user input na po
                    DrawText(id, 245, 285, 20, BLACK);
            }
        bool searchActive = false;
        Rectangle mamaMoh = {235, 370, 120, 50};
        Vector2 naTouch = GetMousePosition();

    if(CheckCollisionPointRec(naTouch, mamaMoh)){
        searchActive = true;
    } else {
        searchActive = false;
    }
        Color normalState = (Color){139, 0, 0, 255};
        Color hoverState = (Color){139, 0, 0, 192};
        kinakabahanAko(searchActive ? hoverState : normalState,  235, 370, 20, 120, 50 );
        DrawText("Search", 240, 380, 20, GOLD);

        bool Lubot = false;
        Rectangle papaNiyoh = {435, 370, 120, 50};
        Vector2 plskahit3langwaglangbagsak = GetMousePosition();
    if(CheckCollisionPointRec(plskahit3langwaglangbagsak, papaNiyoh)){
        Lubot = true;
    } else {
        Lubot = false;
    }

    *backClick = kinakabahanAko(Lubot ? hoverState : normalState, 435, 370, 20, 120, 50);
    DrawText("Back", 450, 380, 20, GOLD);

    if(CheckCollisionPointRec(plskahit3langwaglangbagsak, papaNiyoh) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        *currentScreen = 3;
    }
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (idIndex < sizeof(id) - 1)) {
                id[idIndex++] = (char)key;
                // properly end the string
                id[idIndex] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && idIndex > 0) {
            id[--idIndex] = '\0';
        }
        // find da id
        if (IsKeyPressed(KEY_ENTER)) {
            for (int i = 0; i < recordCount; i++) {
                if (strcmp(records[i].id, id) == 0) {
                    selectedRecordIndex = i;
                    strcpy(name, records[i].name);
                    strcpy(ageInput, TextFormat("%d", records[i].age));
                    strcpy(bookId, records[i].bookId);
                    strcpy(author, records[i].author);
                    nameIndex = strlen(name);
                    idIndex = strlen(id);
                    ageIndex = strlen(ageInput);
                    bookIdIndex = strlen(bookId);
                    authorIndex = strlen(author);
                    // indicate na this record is being edited
                    editingRecordIndex = i;
                    break;
                }
            }
        }
            }   else {
            DrawText("EDIT RECORD", 250, 90, 50, GOLD);
            DrawText("Name:", 255, 145, 20, BLACK);
            DrawRectangle(255, 165, 300, 30, nameActive ? LIGHTGRAY : WHITE);
            DrawRectangleLines(255, 165, 300, 30, BLACK); // Border
            DrawText(name, 260, 170, 20, BLACK);

            DrawText("Age:", 255, 200, 20, BLACK);
            DrawRectangle(255, 220, 300, 30, ageActive ? LIGHTGRAY : WHITE);
            DrawRectangleLines(255, 220, 300, 30, BLACK);
            DrawText(ageInput, 260, 225, 20, BLACK);

            DrawText("Book ID:", 255, 255, 20, BLACK);
            DrawRectangle(255, 275, 300, 30, bookIdActive ? LIGHTGRAY : WHITE);
            DrawRectangleLines(255, 275, 300, 30, BLACK);
            DrawText(bookId, 260, 280, 20, BLACK);

            DrawText("Author:", 255, 310, 20, BLACK);
            DrawRectangle(255, 330, 300, 30, authorAcctive ? LIGHTGRAY : WHITE);
            DrawRectangleLines(255, 330, 300, 30, BLACK);
            DrawText(author, 260, 335, 20, BLACK);

            DrawText("Date & Time:", 255, 365, 20, BLACK);
            DrawRectangle(255, 385, 300, 30, activeBasiDate ? LIGHTGRAY : WHITE);
            DrawRectangleLines(255, 385, 300, 30, BLACK);
            DrawText(TextFormat("%s %d, %d %02d:%02d %s",
            months[records[selectedRecordIndex].month], records[selectedRecordIndex].day,
            records[selectedRecordIndex].year,
            records[selectedRecordIndex].hour,
            records[selectedRecordIndex].minute,
            records[selectedRecordIndex].isAM ? "AM" : "PM"), 265, 390, 20, BLACK);


        Color orgyState = (Color){139, 0, 0, 255};
        Color hovery = (Color){139, 0, 0, 192};
        bool save = false;
        Vector2 getNaSiposhehe = GetMousePosition();
        Rectangle sigenapoplease = {255, 425, 120, 50};
        if(CheckCollisionPointRec(getNaSiposhehe, sigenapoplease)){
            save = true;
        } else {
            save = false;
    }
        kinakabahanAko(save ? hovery : orgyState, 255, 425, 15 ,120, 50);
        DrawText("Save", 285, 435, 20, GOLD);

        bool backTol = false;
        Vector2 Tback = GetMousePosition();
        Rectangle recBack = {430, 425, 120, 50};

        if(CheckCollisionPointRec(Tback, recBack)){
            backTol = true;
        } else {
            backTol = false;
        }

        kinakabahanAko(backTol ? hovery : orgyState, 430, 425, 15, 120, 50);
        DrawText("Back", 465, 435, 20, GOLD);

        if(IsKeyPressed(KEY_DELETE)){
            *currentScreen = 4;
        }

        if (IsKeyPressed(KEY_TAB)) {
            if (nameActive) {
                nameActive = false;
                ageActive = true;
            } else if(ageActive){
                ageActive = false;
                bookIdActive = true;
            }else if (bookIdActive) {
                bookIdActive = false;
                authorAcctive = true;
            } else if(authorAcctive){
                authorAcctive = false;
                activeBasiDate = true;
            } else if(activeBasiDate){
                activeBasiDate = false;
                nameActive = true;
            }
        }

        if (nameActive) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (nameIndex < sizeof(name) - 1)) {
                    name[nameIndex++] = (char)key;
                    name[nameIndex] = '\0';
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && nameIndex > 0) {
                name[--nameIndex] = '\0';
            }
        } else if (ageActive) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (ageIndex < sizeof(ageInput) - 1)) {
                    ageInput[ageIndex++] = (char)key;
                    ageInput[ageIndex] = '\0';
                }
                key = GetCharPressed();
            }
                    if (IsKeyPressed(KEY_BACKSPACE) && ageIndex > 0) {
            ageInput[--ageIndex] = '\0';
                    }
        } else if(bookIdActive) {
            int key = GetCharPressed();
            while(key > 0){
                if((key >= 32) && (key <= 125) && (bookIdIndex < sizeof(bookId) - 1)){
                    bookId[bookIdIndex++] = (char)key;
                    bookId[bookIdIndex] = '\0';
                }
                key = GetCharPressed();
            }
             if(IsKeyPressed(KEY_BACKSPACE) && bookIdIndex > 0){
                bookId[--bookIdIndex] = '\0';
             }
        } else if(authorAcctive) {
            int key = GetCharPressed();
            while(key > 0){
                if((key >= 32) && (key <= 125) && (authorIndex < sizeof(author) - 1)){
                    author[authorIndex++] = (char)key;
                    author[authorIndex] = '\0';
                }

                key = GetCharPressed();
            }
            if(IsKeyPressed(KEY_BACKSPACE) && authorIndex > 0){
                author[--authorIndex] = '\0';
            }
        }
        // yung inedit na eto yung indicator
        if(IsKeyPressed(KEY_ENTER)) {
                strcpy(records[editingRecordIndex].name, name);
                records[editingRecordIndex].age = atoi(ageInput);
                strcpy(records[editingRecordIndex].bookId, bookId);
                strcpy(records[editingRecordIndex].author, author);
                currentScreen = 0;
                memset(name, 0, sizeof(name));
                memset(id, 0, sizeof(id));
                memset(ageInput, 0, sizeof(ageInput));
                memset(bookId, 0, sizeof(bookId));
                memset(author, 0, sizeof(author));
                nameIndex = idIndex = ageIndex = bookIdIndex = authorIndex = 0;
                nameActive = true;
                ageActive = bookIdActive = authorAcctive = false;
                selectedRecordIndex = -1;
            }
        }


    if (IsKeyPressed(KEY_ESCAPE)) {
        currentScreen = 0;
        selectedRecordIndex = -1;
    }
}

void DisplayRecords(int *currentScreen, Texture2D displayRec, Texture2D p14, int *selectedDay, int *selectedMonth, int *selectedYear, int *selectedHour, int *selectedMinute, bool *isAM) {
    int x = 1200;
    static int currentRecordIndex = -1;

    if (IsKeyPressed(KEY_BACKSPACE)) {
        *currentScreen = 3;
    }
    DrawTexture(displayRec, x - 1200, 0, WHITE);
    DrawTexture(p14, x - 1200, 0, WHITE);

    DrawText("Display Records", 400, 50, 30, GOLD);
    int yOffset = 120;

    if (recordCount == 0) {
        DrawText("No records available.", 412, yOffset, 20, YELLOW);
    } else {
        for (int i = 0; i < recordCount; i++) {
            char buffer[300];
            bool calendaryy = false;
            Vector2 vecky = GetMousePosition();
            Rectangle recky = {300, 120, 600, 45};
            if (CheckCollisionPointRec(vecky, recky)) {
                calendaryy = true;
            } else {
                calendaryy = false;
        }
            Color glassyTransparent = (Color){255, 255, 255, 128};
            Color hoverEffect = (Color){255, 255, 255, 160};
            DrawText("Date:", 315, 130, 20, WHITE);
            kinakabahanAko(calendaryy ? hoverEffect : glassyTransparent, 300, 120, 90, 600, 45);
            DrawText(TextFormat("%s %d, %d %02d:%02d %s", months[*selectedMonth], *selectedDay, *selectedYear, *selectedHour, *selectedMinute, *isAM ? "AM" : "PM"), 375, 130, 20, WHITE);

            // record information
            snprintf(buffer, sizeof(buffer), "%d. Name: %s, ID: %s, Age: %d\nBook ID: %s, Author: %s\nDate Borrowed: %s %d, %d Time: %02d:%02d %s",
                     i + 1, records[i].name, records[i].id, records[i].age,
                     records[i].bookId, records[i].author,
                     months[records[i].month], records[i].day, records[i].year,
                     records[i].hour, records[i].minute, records[i].isAM ? "AM" : "PM");
            DrawText(buffer, 100, yOffset + 60, 20, YELLOW);


            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), (Rectangle){300, 120, 600, 55})) {
                currentRecordIndex = i;
                *currentScreen = 9;
                }
            yOffset += 80;
        }
    }

}
void saAneksaSearch(int roundX, int roundY, int orig_w, int orig_h, int orig_radius, int new_w, int new_h){
    float scale_w = (float)new_w / orig_w;
    float scale_h = (float)new_h / orig_h;
    int new_radius = orig_radius * (scale_w < scale_h ? scale_w : scale_h);

    Color slightlyDarkerGlass = (Color){220, 220, 220, 128};
    DrawRectangleRounded((Rectangle){roundX, roundY, new_w, new_h}, (float)new_radius / new_w, 16, slightlyDarkerGlass);
}

void SearchRecord(Texture2D searchIMG, int *currentScreen, int *selectedDay, int *selectedMonth, int *selectedYear, int *selectedHour, int *selectedMinute) {
    int x = 1200;
    static char searchId[20] = "";
    static int idIndex = 0;
    static bool recordFound = false;
    static Record foundRecord;

    DrawTexture(searchIMG, x - 1200, 0, WHITE);

    if (!recordFound) {
        Color normalState = (Color){139, 0, 0, 255};
        Color hoverState = (Color){139, 0, 0, 192};
        rounders(430, 110, 500, 420, 40, 500, 420 );
        DrawText("Search Record", 530, 140, 45, GOLD);

        bool napindotbah = false;

        Rectangle yungRect = {520, 210, 300, 60};
        Vector2 huy = GetMousePosition();

        if(CheckCollisionPointRec(huy, yungRect)){
            napindotbah = true;
        } else { napindotbah = false;
        }
        DrawRectangle(520, 210, 300, 60, napindotbah ? GRAY : WHITE);
        DrawRectangleLines(520, 210, 300, 60, BLACK);

        bool enteryyy = false;
        Rectangle rectulitbes = {520, 285, 300, 60};
        Vector2 plscomerescueme = GetMousePosition();

        if(CheckCollisionPointRec(plscomerescueme, rectulitbes)){
            enteryyy = true;
        } else{
            enteryyy = false;
        }
        kinakabahanAko(enteryyy ? hoverState : normalState, 520, 285, 30, 300, 60);
        DrawText("Enter", 610, 295, 30, GOLD);

        bool isaraAngBaso = false;
        Rectangle godIfthisCourseforMeSanaKahitTresLangPo = {520, 360, 300, 60};
        Vector2 plsGod = GetMousePosition();

        if(CheckCollisionPointRec(plsGod, godIfthisCourseforMeSanaKahitTresLangPo)){
            isaraAngBaso = true;
        } else {
            isaraAngBaso = false;
        }
        kinakabahanAko(isaraAngBaso ? hoverState : normalState, 520, 360, 30, 300, 60);
        DrawText("Back", 610, 370, 30, GOLD);

        if(CheckCollisionPointRec(plsGod, godIfthisCourseforMeSanaKahitTresLangPo) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            *currentScreen = 3;
        }

        if(idIndex == 0){
            DrawText("Student ID:", 525, 225, 20, BLACK);
        } else {
            DrawText(searchId, 525, 225, 20, BLACK);
    }

        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (idIndex < sizeof(searchId) - 1)) {
                searchId[idIndex++] = (char)key;
                searchId[idIndex] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && idIndex > 0) {
            searchId[--idIndex] = '\0';
        } else if (CheckCollisionPointRec(plscomerescueme, rectulitbes) && IsKeyPressed(KEY_ENTER)) {
            for (int i = 0; i < recordCount; i++) {
                if (strcmp(records[i].id, searchId) == 0) {
                    foundRecord = records[i];
                    recordFound = true;
                    break;
                }
            }
        }
    }

    if (recordFound) {

        rounders( 200, 100, 800, 410, 15, 800, 410);
        saAneksaSearch(200, 100, 800, 110, 15, 800, 110);

        DrawText("Record List", 395, 110, 75, ORANGE);


        char buffer[300];
        snprintf(buffer, sizeof(buffer), "Student ID: %s\nBook ID: %s\nAuthor: %s\nDate Borrowed: %d-%d-%d",
                 foundRecord.id, foundRecord.bookId, foundRecord.author,
                 foundRecord.day, foundRecord.month + 1, foundRecord.year);
        DrawText(buffer, 240, 250, 20, GOLD);

        int dueDateDays = foundRecord.year * 365 + foundRecord.month * 30 + foundRecord.day;
        int currentDateDays = *selectedYear * 365 + *selectedMonth * 30 + *selectedDay;

        int daysLate = currentDateDays - dueDateDays;
        if (daysLate > 2) {
            int fine = (daysLate - 2) * 5;
            snprintf(buffer, sizeof(buffer), "Book is late by %d days. Fine: %d pesos", daysLate - 2, fine);
            DrawText(buffer, 240, 335, 20, RED);
        }

        bool imBack = false;
        Color normalState = (Color){139, 0, 0, 255};
        Color hoverState = (Color){139, 0, 0, 192};
        Vector2 BackyKang = GetMousePosition();
        Rectangle back  = {300, 410, 330, 65};

        if(CheckCollisionPointRec(BackyKang, back)){
            imBack = true;
        } else {
            imBack = false;
        }

        kinakabahanAko(imBack ? hoverState : normalState, 415, 410, 30, 330, 65);
        DrawRectangleLines(415, 410, 330, 65, BLACK);
        DrawText("Back", 550, 435, 20, GOLD);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();
            Rectangle backButton = {415, 410, 330, 65};
            if (CheckCollisionPointRec(mousePoint, backButton)) {
                *currentScreen = 7;
                recordFound = false;
                // Reset the search ID index
                idIndex = 0;
                // Clear the search ID
                memset(searchId, 0, sizeof(searchId));
            }
        }
    } else if (!recordFound && strlen(searchId) > 0) {
        DrawText("Record not found.", 580, 475, 20, RED);
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        *currentScreen = 0;
        recordFound = false;
        idIndex = 0;
        memset(searchId, 0, sizeof(searchId));
    }
}

void DeleteRecord(int *currentScreen, Texture2D plssimage, Texture2D del2) {
    static char id[20] = "";
    static int idIndex = 0;
    static bool recordFound = false;
    static Record foundRecord = {0};
    int x = 1200;
    DrawTexture(plssimage, x - 1200, 0, WHITE);
    DrawTexture(del2, x  - 1200, 435, WHITE);
    rounders(305, 45, 585, 360, 15, 585, 360);

    DrawText("Delete Record", 395, 70, 50, DARKGRAY);

    if(!recordFound){
    static bool boxentry = false;

    Color orgyState = (Color){139, 0, 0, 255};
    Color hovery = (Color){139, 0, 0, 192};
    Vector2 yuhh = GetMousePosition();
    Rectangle natatakotakohuhu = {400, 145, 360, 50};
    Color transparentGray = (Color){128, 128, 128, 128};
    if(CheckCollisionPointRec(yuhh, natatakotakohuhu) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        boxentry = !boxentry;
    }
    DrawRectangle(400, 145, 360, 50, boxentry ? transparentGray : WHITE);
    DrawRectangleLines(400, 145, 360, 50, BLACK);

    if(idIndex == 0){
        DrawText("Enter ID to Delete:", 425, 155, 20, BLACK);
    }
    else{
            // nag input na si user
            DrawText(id, 425, 155, 20, BLACK);
    }

    bool ikat = false;
    Rectangle kahittresplatlangpookayna = {400, 280, 360, 50};
    Vector2 tresplatcutie = GetMousePosition();
    if(CheckCollisionPointRec(tresplatcutie, kahittresplatlangpookayna)){
        ikat = true;
    } else {
        ikat = false;
    }
    if(CheckCollisionPointRec(tresplatcutie, kahittresplatlangpookayna) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        *currentScreen = 3;
    }

    kinakabahanAko(ikat ? hovery : orgyState, 400, 280, 20, 360, 50);
    DrawText("Back", 535, 295, 20, ORANGE);

    bool enter = false;
    Vector2 enterpos = GetMousePosition();
    Rectangle enterRec = {400, 215, 360, 50};

    if(CheckCollisionPointRec(enterpos, enterRec)){
        enter = true;
    }
    else {
            enter = false;
    }

 kinakabahanAko(enter ? hovery : orgyState, 400, 215, 20, 360, 50);
 DrawText("Enter", 535, 225, 20, ORANGE);

    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (idIndex < sizeof(id) - 1)) {
            id[idIndex++] = (char)key;
            id[idIndex] = '\0';
            recordFound = false;
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && idIndex > 0) {
        id[--idIndex] = '\0';
        recordFound = false;
    } else if (IsKeyPressed(KEY_ENTER)) {
        for (int i = 0; i < recordCount; i++) {
            if (strcmp(records[i].id, id) == 0) {
                foundRecord = records[i];
                recordFound = true;
                break;
            }
        }
    }
}
    if (recordFound) {
        char buffer[200];
        snprintf(buffer, sizeof(buffer), "Name: %s, ID: %s, Age: %d, \nDate: %s %d, %d Time: %02d:%02d",
                 foundRecord.name, foundRecord.id, foundRecord.age,
                 months[foundRecord.month], foundRecord.day, foundRecord.year,
                 foundRecord.hour, foundRecord.minute);
        DrawText(buffer, 400, 125, 20, GOLD);

        bool deletenaba = false;
        Vector2 del = GetMousePosition();
        Rectangle delrec = {475, 300, 200, 50};

        if(CheckCollisionPointRec(del, delrec)){
            deletenaba = true;
        } else {
            deletenaba = false;
        }
        Color orgyState = (Color){139, 0, 0, 255};
        Color hovery = (Color){139, 0, 0, 192};
        DrawRectangleLines(475, 300, 200, 50, BLACK);
        DrawRectangle(475, 300, 200, 50, deletenaba ? hovery : orgyState );
        DrawText("Confirm Delete", 495, 315, 20, deletenaba ? ORANGE : WHITE);

        if (IsKeyPressed(KEY_ENTER)) {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, (Rectangle){475, 300, 200, 50})) {
                for (int i = 0; i < recordCount; i++) {
                    if (strcmp(records[i].id, id) == 0) {
                            // simula dun sa pos nung index na nakita tu second to the last
                        for (int j = i; j < recordCount - 1; j++) {
                            // overwrite the index of matchy matchy recky
                            records[j] = records[j + 1];
                        }
                        // indctr para sa deletion of recs
                        recordCount--;
                        break;
                    }
                }
                *currentScreen = 8;
                memset(id, 0, sizeof(id));
                idIndex = 0;
                recordFound = false;
            }
        }

    }   bool buttonEnter = false;
        Vector2 vec = GetMousePosition();
        Rectangle enterrss = {400, 215, 360, 50};
        if(CheckCollisionPointRec(vec, enterrss) && IsKeyPressed(KEY_ENTER)){
            buttonEnter = true;
        }
          if (buttonEnter &&  !recordFound) {
        DrawText("Record not found.", 490, 335, 20, RED);
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        *currentScreen = 0;
        memset(id, 0, sizeof(id));
        idIndex = 0;
        recordFound = false;
    }
}
void DatePicker(int queenA, int queenB, Texture2D calendar, Texture2D calendar2, int *selectedDay, int *selectedMonth, int *selectedYear, int *selectedHour, int *selectedMinute, bool *isAM, int *currentScreen) {
    static int currentYPos = -600;
    int targetYPos = queenB - 460;


    int startDaysOfWeek2025[12] = {3, 6, 0, 3, 4, 0, 2, 5, 1, 3, 6, 1};
    DrawTexture(calendar2, queenA - 1200, queenB - 200, WHITE);
    DrawTexture(calendar, queenA - 1200, queenB - 590, WHITE);

    if (currentYPos < targetYPos) {
        currentYPos += 15;
        if (currentYPos > targetYPos) {
            currentYPos = targetYPos;
        }
    }
    DrawText(TextFormat("Year: %d", *selectedYear), 100, 30, 20, DARKBLUE);
    DrawText(TextFormat("Month: %s", months[*selectedMonth]), 260, 30, 20, DARKBLUE);
    // Year
    if (IsKeyPressed(KEY_Q)) (*selectedYear)--;
    if (IsKeyPressed(KEY_E)) (*selectedYear)++;
    // Month
    if (IsKeyPressed(KEY_A)) *selectedMonth = ClampInt(*selectedMonth - 1, 0, 11);
    if (IsKeyPressed(KEY_D)) *selectedMonth = ClampInt(*selectedMonth + 1, 0, 11);
    // Calculate start day of the week for the selected month and year
    int daysInYear2025 = GetDaysInYear2025();
    int daysOffset = ((*selectedYear - 2025) * 365 + CountLeapYears(*selectedYear) - CountLeapYears(2025)) % 7;

    int firstDayOfWeek = (startDaysOfWeek2025[*selectedMonth] + daysOffset) % 7;
    if (firstDayOfWeek < 0) firstDayOfWeek += 7;

    // Get the number of days in the month
    int daysInMonth = GetDaysInMonth(*selectedMonth, *selectedYear);

    int xOffset = 175;
    int boxWidth = 110;
    int boxHeight = 50;
    int boxSpacing = 10;
    float roundness = 0.3f;

    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        int weekdayX = xOffset + i * (boxWidth + boxSpacing);
        DrawText(weekDays[i], weekdayX + 40, 75, 20, GOLD);
    }

    int x = xOffset + firstDayOfWeek * (boxWidth + boxSpacing), y = currentYPos;
    for (int day = 1; day <= daysInMonth; day++) {
        Rectangle dayBounds = { x, y, boxWidth, boxHeight };
        Color dayColor = (*selectedDay == day) ? DARKBLUE : LIGHTGRAY;
        DrawRectangleRounded(dayBounds, roundness, 12, dayColor);
        DrawText(TextFormat("%d", day), x + 40, y + 10, 30, (*selectedDay == day) ? WHITE : BLACK);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), dayBounds)) {
            *selectedDay = day;
        }
        x += boxWidth + boxSpacing;
        if ((x - xOffset) / (boxWidth + boxSpacing) % DAYS_IN_WEEK == 0) {
            x = xOffset;
            y += boxHeight + boxSpacing;
        }
    }

    // Time display and controls
    if (IsKeyPressed(KEY_UP)) *selectedHour = ClampInt(*selectedHour + 1, 1, 12);
    if (IsKeyPressed(KEY_DOWN)) *selectedHour = ClampInt(*selectedHour - 1, 1, 12);
    if (IsKeyPressed(KEY_RIGHT)) *selectedMinute = ClampInt(*selectedMinute + 1, 0, 59);
    if (IsKeyPressed(KEY_LEFT)) *selectedMinute = ClampInt(*selectedMinute - 1, 0, 59);

    // AM/PM
    if (IsKeyPressed(KEY_TAB)) *isAM = !(*isAM);

    const char* amPmText = *isAM ? "AM" : "PM";

    DrawText("Use UP/DOWN for Hours, LEFT/RIGHT for Minutes, TAB to toggle AM/PM", 450, 520, 15, GOLD);
    DrawText("Q/E to change Year, A/D to change Month", 450, 540, 15, GOLD);

    // Selected date summary
    DrawText(TextFormat("Selected Date: %s %d, %d", months[*selectedMonth], *selectedDay, *selectedYear), 50, 520, 20, ORANGE);
    DrawText(TextFormat("Selected Time: %02d:%02d %s", *selectedHour, *selectedMinute, amPmText), 50, 500, 20, ORANGE);

    if (IsKeyPressed(KEY_ENTER)) {
        *currentScreen = 4;
        currentYPos = -600;
    }
     if (IsKeyPressed(KEY_SPACE)) {
        *currentScreen = 6;
        currentYPos = -600;
    }
}

int GetDaysInMonth(int month, int year) {
    if (month == 1) {
        // look kung leap year
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            return 29;
        } else {
            return 28;
        }
        // April, June, September, November
    } else if (month == 3 || month == 5 || month == 8 || month == 10) {
        return 30;
    } else {
        return 31;
    }
}

int CountLeapYears(int year) {
    return (year / 4) - (year / 100) + (year / 400);
}
int GetDaysInYear2025() {
    return 365 + 1;
}
int GetFirstDayOfWeek(int month, int year) {
    int day = 1;
    if (month < 2) {
        month += 12;
        year--;
    }
    return (day + 2 * month + (3 * (month + 1)) / 5 + year + (year / 4) - (year / 100) + (year / 400)) % 7;
}
int ClampInt(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
